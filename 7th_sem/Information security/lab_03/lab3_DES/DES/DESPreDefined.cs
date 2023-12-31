﻿using System;
using System.IO;

namespace lab3_DES
{
    /// <summary>
    /// Класс заданных перестановок
    /// </summary>
    static class DESPreDefined
    {
        private static string _rootDirectory = @"D:\Repos\GitHub\7_sem_SE\IS\lab_03\permutations\";

        public static int[] IPnormal;
        public static int[] IPconverse;
        public static int[] expansion;
        public static int[] finishP;
        public static int[][][] sBlocks;

        public static int[] keyC0;
        public static int[] keyD0;
        public static int[] keyShift;
        public static int[] keyCP;

        static DESPreDefined()
        {
            IPnormal = ReadIntArrayFromFile(_rootDirectory + "encoding.txt");
            IPconverse = ReadIntArrayFromFile(_rootDirectory + "decoding.txt");
            expansion = ReadIntArrayFromFile(_rootDirectory + "Expansion.txt");
            finishP = ReadIntArrayFromFile(_rootDirectory + "finishP.txt");

            ReadSBlocks(_rootDirectory + "SBlocks.txt");

            keyC0 = ReadIntArrayFromFile(_rootDirectory + "keyC0.txt");
            keyD0 = ReadIntArrayFromFile(_rootDirectory + "keyD0.txt");
            keyCP = ReadIntArrayFromFile(_rootDirectory + "keyCP.txt");
            keyShift = ReadIntArrayFromFile(_rootDirectory + "keyShift.txt");
        }

        /// <summary>
        /// Считывает массив чисел из файла, где числа разделены пробелом
        /// </summary>
        private static int[] ReadIntArrayFromFile(string filename)
        {
            string text = File.ReadAllText(filename);
            string[] splitedText = text.Split(' ');

            int[] res = new int[splitedText.Length];
            for (int i = 0; i < res.Length; i++)
                res[i] = Convert.ToInt32(splitedText[i]);

            return res;
        }

        /// <summary>
        /// Считывает таблицу для S блоков
        /// </summary>
        private static void ReadSBlocks(string filename)
        {
            int nBlocks = 8;
            int nLines = 4;
            int nNums = 16;

            sBlocks = new int[nBlocks][][];
            string text = File.ReadAllText(filename);
            string[] splittedByBlocks = text.Split('-');

            for (int iBlock = 0; iBlock < nBlocks; iBlock++)
            {
                int[][] curBlock = new int[nLines][];
                string[] splittedBlockByLine = splittedByBlocks[iBlock].Trim().Split('\n');

                for (int iLine = 0; iLine < nLines; iLine++)
                {
                    string[] splittedLine = splittedBlockByLine[iLine].Trim().Split(' ');
                    int[] curLine = new int[nNums];
                    for (int iNum = 0; iNum < nNums; iNum++)
                        curLine[iNum] = Convert.ToInt32(splittedLine[iNum]);
                    curBlock[iLine] = curLine;
                }
                sBlocks[iBlock] = curBlock;
            }
        }
    }
}
