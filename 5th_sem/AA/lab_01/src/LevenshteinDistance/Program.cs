using System;
using System.Diagnostics;

namespace LevenshteinDistance
{
    class Program
    {
        delegate int Func(string s1, string s2);

        static string[,] words = { { "gfg", "ounc", "pcwri", "cympwd", "waauhui", "vvobdddd", "ujyybxkuw", "jtrezzaulu", "msrdvubnofh", "mfnttwkaprtq", "zlzqhxmjtvyvs" }, 
                            { "tjc", "dhja", "gdmlp", "akytjq", "tefnach", "bbbpjoou", "yyqgxmsbr", "ewyqeztwbe", "eszhuwhejxv", "dgjntyrlburj", "juctsnhhvcnny" } };

        static int Minimum(int a, int b, int c) => (a = a < b ? a : b) < c ? a : c;

        static int _LevDist(string source, int srclen, string target, int trglen)
        {
            if (srclen * trglen == 0)
                return Math.Max(srclen, trglen);

            int substitutionCost = 0;
            if (source[srclen - 1] != target[trglen - 1])
                substitutionCost = 1;

            int deletion = _LevDist(source, srclen - 1, target, trglen) + 1;
            int insertion = _LevDist(source, srclen, target, trglen - 1) + 1;
            int substitution = _LevDist(source, srclen - 1, target, trglen - 1) + substitutionCost;

            return Minimum(deletion, insertion, substitution);
        }

        static int LevDistRec(string source, string target) =>
            _LevDist(source, source.Length, target, target.Length);


        static int LevDistMatr(string source, string target)
        {
            if (source.Length * target.Length == 0)
                return Math.Max(target.Length, source.Length);

            int n = source.Length + 1;
            int m = target.Length + 1;
            int[,] matrixD = new int[n, m];

            const int deletionCost = 1;
            const int insertionCost = 1;

            for (int i = 0; i < n; i++)
                matrixD[i, 0] = i;

            for (int j = 0; j < m; j++)
                matrixD[0, j] = j;

            for (int i = 1; i < n; i++)
            {
                for (int j = 1; j < m; j++)
                {
                    int substitutionCost = source[i - 1] == target[j - 1] ? 0 : 1;

                    matrixD[i, j] = Minimum(matrixD[i - 1, j] + deletionCost,          
                                            matrixD[i, j - 1] + insertionCost,         
                                            matrixD[i - 1, j - 1] + substitutionCost); 
                }
            }

            return matrixD[n - 1, m - 1];
        }


        static int LevDistTwoRows(string source, string target)
        {
            if (source.Length * target.Length == 0)
                return Math.Max(target.Length, source.Length);

            int m = target.Length;
            int n = source.Length;
            int[,] distance = new int[2, m + 1];

            for (int j = 1; j <= m; j++) 
                distance[0, j] = j;

            int currentRow = 0;
            for (int i = 1; i <= n; ++i)
            {
                currentRow = i % 2;
                distance[currentRow, 0] = i;
                int previousRow = (currentRow + 1) % 2;
                for (int j = 1; j <= m; j++)
                {
                    int cost = target[j - 1] == source[i - 1] ? 0 : 1;
                    distance[currentRow, j] = Minimum(distance[previousRow, j] + 1,
                                                      distance[currentRow, j - 1] + 1,
                                                      distance[previousRow, j - 1] + cost);
                }
            }
            return distance[currentRow, m];
        }


        static int _DamLevDist(string source, int srclen, string target, int trglen)
        {
            if (srclen * trglen == 0)
                return Math.Max(srclen, trglen);

            int deletion = _DamLevDist(source, srclen - 1, target, trglen) + 1;
            int insertion = _DamLevDist(source, srclen, target, trglen - 1) + 1;
            int substitution = _DamLevDist(source, srclen - 1, target, trglen - 1) + (source[srclen - 1] != target[trglen - 1] ? 1 : 0);

            int min = Minimum(deletion, insertion, substitution);

            if (srclen > 1 && trglen > 1 && source[srclen - 1] == target[trglen - 2] && source[srclen - 2] == target[trglen - 1])
                min = Math.Min(min, _DamLevDist(source, srclen - 2, target, trglen - 2) + 1);

            return min;
        }
        static int DamLevDistRec(string source, string target) =>
            _DamLevDist(source, source.Length, target, target.Length);


        static int DamLevDistMatr(string source, string target)
        {
            if (source.Length * target.Length == 0)
                return Math.Max(target.Length, source.Length);

            int n = source.Length + 1;
            int m = target.Length + 1;
            int[,] arrayD = new int[n, m];

            for (int i = 0; i < n; i++)
                arrayD[i, 0] = i;

            for (int j = 0; j < m; j++)
                arrayD[0, j] = j;

            for (int i = 1; i < n; i++)
            {
                for (int j = 1; j < m; j++)
                {
                    int cost = source[i - 1] == target[j - 1] ? 0 : 1;

                    arrayD[i, j] = Minimum(arrayD[i - 1, j] + 1,
                                           arrayD[i, j - 1] + 1,
                                           arrayD[i - 1, j - 1] + cost);

                    if (i > 1 && j > 1 && source[i - 1] == target[j - 2] && source[i - 2] == target[j - 1])
                        arrayD[i, j] = Math.Min(arrayD[i, j], arrayD[i - 2, j - 2] + cost);
                }
            }

            return arrayD[n - 1, m - 1];
        }

        static double[] CheckTicks(Func f, int count, int len = -1)
        {
            int n = len == -1 ? words.Length / 2 : len;
            double[] numbers = new double[n];

            Stopwatch sw = new Stopwatch();
            for (int i = 0; i < n; i++)
            {
                sw.Start();
                for (int j = 0; j < count; j++)
                    f(words[0, i], words[1, i]);
                sw.Stop();
                numbers[i] = sw.Elapsed.TotalMilliseconds * 1000 / count;
                sw.Reset();
            }

            return numbers;
        }

        static void Main(string[] args)
        {
            string s1 = Console.ReadLine();
            string s2 = Console.ReadLine();

            Console.WriteLine("Result LevDistRec: {0}", LevDistRec(s1, s2));
            Console.WriteLine("Result LevDistMatr: {0}", LevDistMatr(s1, s2));
            Console.WriteLine("Result LevDistTwoRows: {0}", LevDistTwoRows(s1, s2));
            Console.WriteLine("Result DamLevDistRec: {0}", DamLevDistRec(s1, s2));
            Console.WriteLine("Result DamLevDistMatr: {0}", DamLevDistMatr(s1, s2));

            Console.Write("\nTimes(microseconds) LevDistRec: ");
            double[] times1 = CheckTicks(LevDistRec, 1000, 7);
            for (int i = 0; i < times1.Length; i++)
                Console.Write(times1[i].ToString() + " ");
            Console.WriteLine();

            Console.Write("Times(microseconds) LevDistMatr: ");
            double[] times2 = CheckTicks(LevDistMatr, 1000, 7);
            for (int i = 0; i < times2.Length; i++)
                Console.Write(times2[i].ToString() + " ");
            Console.WriteLine();

            Console.Write("Times(microseconds) LevDistTwoRows: ");
            double[] times3 = CheckTicks(LevDistTwoRows, 1000, 7);
            for (int i = 0; i < times3.Length; i++)
                Console.Write(times3[i].ToString() + " ");
            Console.WriteLine();

            Console.Write("Times(microseconds) DamLevDistRec: ");
            double[] times4 = CheckTicks(DamLevDistRec, 1000, 7);
            for (int i = 0; i < times4.Length; i++)
                Console.Write(times4[i].ToString() + " ");
            Console.WriteLine();

            Console.Write("Times(microseconds) DamLevDistMatr: ");
            double[] times5 = CheckTicks(DamLevDistMatr, 1000, 7);
            for (int i = 0; i < times5.Length; i++)
                Console.Write(times5[i].ToString() + " ");
            Console.WriteLine();
        }
    }
}
