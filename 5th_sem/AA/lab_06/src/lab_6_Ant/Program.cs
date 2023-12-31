using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;

namespace lab_6_Ant
{
    class Program
    {
        static void Main(string[] args)
        {
            //Map m = new Map(4);
            //var a = BruteForce.GetShortestPath(m);
            //var b = AntAlgorithm.GetShortestPath(m, 30, 0.7, 0.3, 4, 0.1);
            //AnalyseTime(10, 2, 11);
            GetCoeffs();
        }

        public static T[][] InitMatr<T>(int n, T val)
        {
            T[][] matr = new T[n][];
            for (int i = 0; i < n; i++)
            {
                matr[i] = new T[n];
                for (int j = 0; j < n; j++)
                    matr[i][j] = val;
            }
            return matr;
        }

        public static void AnalyseTime(int nIter, int mapSizeFrom = 2, int mapSizeTo = 10)
        {
            Stopwatch stopWatch = new Stopwatch();

            for (int mapSizeCurr = mapSizeFrom; mapSizeCurr <= mapSizeTo; mapSizeCurr++)
            {
                Map m = new Map(mapSizeCurr);
                long ts = 0;
                for (int i = 0; i < nIter; i++)
                {
                    stopWatch.Start();
                    //BruteForce.GetShortestPath(m);
                    AntAlgorithm.GetShortestPath(m, 30, 0.7, 0.3, 4, 0.1);
                    stopWatch.Stop();

                    ts += stopWatch.Elapsed.Ticks;
                }
                File.AppendAllText("Ant.txt", mapSizeCurr.ToString() + " " + (ts / nIter).ToString() + "\n");
            }
        }

        public static void GetCoeffs()
        {
            int days = 100;
            double sumab = 1;
            Map m = new Map(10);
            var shortestPath = BruteForce.GetShortestPath(m);

            double alpha, pho;
            for (alpha = 0; alpha <= sumab; alpha += 0.1)
            {
                for (pho = 0; pho <= sumab; pho += 0.1)
                {
                    var cv = AntAlgorithm.GetShortestPath(m, days, alpha, sumab - alpha, 5, pho);

                    if (cv.distance != shortestPath.distance)
                    {
                        Console.WriteLine("- " + days + " " + cv.distance + " " + shortestPath.distance + " " + alpha + " " + pho);
                    }
                    else
                        Console.WriteLine("+ " + days + " " + cv.distance + " " + shortestPath.distance + " " + alpha + " " + pho);
                }
                Console.WriteLine();
            }
            Console.Read();
        }
                
    }
}
