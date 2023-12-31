using System;
using System.IO;

namespace lab6_LZW
{
    class Program
    {
        static void Main(string[] args)
        {
            string fType = ".png";
            LZWAlgo.Compress("test" + fType, "tmp" + fType);
            Console.WriteLine();
            LZWAlgo.Decompress("tmp" + fType, "res" + fType);
        }
    }
}
