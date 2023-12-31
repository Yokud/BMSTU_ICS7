using System;
using System.Collections.Generic;
using System.Linq;
using System.Management;
using System.Text;
using System.Threading.Tasks;

namespace App
{
    internal class Program
    {
        static void Main(string[] args)
        {
            string serialKey = GetSerialKey();

            AppLib.App.Func(serialKey);

            Console.Read();
        }

        private static string GetSerialKey()
        {
            // ManagementObjectSearcher - обёртка над WMI (инструментарий управления Windows)
            ManagementObjectSearcher moSearcher = new ManagementObjectSearcher("SELECT * FROM Win32_DiskDrive");

            var moObjs = moSearcher.Get().GetEnumerator();
            moObjs.MoveNext();
            string serialKey = moObjs.Current["SerialNumber"].ToString().Trim();
            return serialKey;
        }
    }
}
