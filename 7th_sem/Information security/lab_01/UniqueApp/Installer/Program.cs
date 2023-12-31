using Microsoft.CSharp;
using System;
using System.CodeDom.Compiler;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Threading.Tasks;
using System.Management;
using System.Text;
using System.Runtime.CompilerServices;

namespace Installer
{
    internal class Program
    {
        static void Main(string[] args)
        {
            string SourceFileString = "../../AppLib/App.cs";
            string Output = "AppLib.dll";

            var lines = File.ReadAllLines(SourceFileString).ToList();

            // ManagementObjectSearcher - обёртка над WMI (инструментарий управления Windows)
            ManagementObjectSearcher moSearcher = new ManagementObjectSearcher("SELECT * FROM Win32_DiskDrive");

            var moObjs = moSearcher.Get().GetEnumerator();
            moObjs.MoveNext();
            string serialKey = moObjs.Current["SerialNumber"].ToString().Trim();

            string extraCode = $"static App() {{ key = \"{serialKey}\"; }}";

            lines.Insert(lines.Count - 2, extraCode);

            StringBuilder sourceCode = new StringBuilder();

            foreach (var line in lines)
                sourceCode.AppendLine(line);

            CSharpCodeProvider codeProvider = new CSharpCodeProvider();
            ICodeCompiler icc = codeProvider.CreateCompiler();

            CompilerParameters parameters = new CompilerParameters();
            parameters.GenerateExecutable = false;
            parameters.OutputAssembly = Output;
            CompilerResults results = icc.CompileAssemblyFromSource(parameters, sourceCode.ToString());

            if (results.Errors.Count > 0)
            {
                foreach (CompilerError CompErr in results.Errors)
                {
                    Console.WriteLine(
                        "Line number " + CompErr.Line +
                        ", Error Number: " + CompErr.ErrorNumber +
                        ", '" + CompErr.ErrorText + ";\n");
                }
            }
            else
                Console.WriteLine("Compile success");
            Console.ReadLine();
        }
    }
}
