using System;
using System.IO;

namespace lab4_RSA
{
    class Program
    {

        static void Main(string[] args)
        {
            RSA rsaMachine = new RSA();

            string filename = "test", ext = ".jpg";

            string filenameIN = filename + ext;
            string filenameEncr = filename + "_encr" + ext;
            string filenameOUT = filename + "_descr" + ext;

            ProcessFileToBinary(filenameIN, filenameEncr, rsaMachine.Encrypt);
            ProcessBinaryToNormal(filenameEncr, filenameOUT, rsaMachine.Decrypt);
        }

        /// <summary>
        /// Побайтная обработка файла
        /// </summary>
        /// <param name="src">Исходный файл</param>
        /// <param name="dst">Результирующий файл</param>
        public static void ProcessFileToBinary(string src, string dst, Func<int, int> ProcessOneInt)
        {
            FileStream fsSrc = new FileStream(src, FileMode.Open);
            FileStream fsDst = new FileStream(dst, FileMode.Create);
            BinaryWriter binWriter = new BinaryWriter(fsDst);

            int cur;
            while (fsSrc.CanRead)
            {
                cur = fsSrc.ReadByte();
                if (cur == -1)
                    break;
                int res = ProcessOneInt(cur);
                binWriter.Write(res);
            }

            binWriter.Write(-1);
            binWriter.Close();
            fsDst.Close();
            fsSrc.Close();
        }

        public static void ProcessBinaryToNormal(string src, string dst, Func<int, int> ProcessOneInt)
        {
            FileStream fsSrc = new FileStream(src, FileMode.Open);
            FileStream fsDst = new FileStream(dst, FileMode.Create);
            BinaryReader binReader = new BinaryReader(fsSrc);

            int cur;
            while (fsSrc.CanRead)
            {
                cur = binReader.ReadInt32();
                if (cur == -1)
                    break;
                int res = ProcessOneInt(cur);
                fsDst.WriteByte((byte)res);
            }
            
            binReader.Close();
            fsDst.Close();
            fsSrc.Close();
        }


    }
}
