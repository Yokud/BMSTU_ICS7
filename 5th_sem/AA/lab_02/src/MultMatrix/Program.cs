using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace MultMatrix
{
    public class Matrix
    {
        private double[,] data;
        private int m, n;

        public int M { get => m; }
        public int N { get => n; }

        public Matrix(int n, int m)
        {
            this.m = m;
            this.n = n;
            data = new double[n, m];
        }

        public Matrix(List<List<double>> lst)
        {
            n = lst.Count;
            m = lst[0].Count;
            data = new double[n, m];

            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    data[i, j] = lst[i][j];
        }

        public double this[int x, int y]
        {
            get => data[x, y];
            set => data[x, y] = value;
        }

        public void GenMatrix()
        {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    data[i, j] = i + j;
        }

        public void PrintMatrix()
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                    Console.Write(this[i, j].ToString() + ' ');
                Console.WriteLine();
            }
        }

        public Matrix MultiplyStandart(Matrix matr)
        {
            Matrix result = new Matrix(n, matr.M);

            for (int i = 0; i < n; i++)
            {
                for (int k = 0; k < matr.M; k++)
                {
                    result[i, k] = 0;
                    for (int j = 0; j < m; j++)
                        result[i, k] += data[i, j] * matr[j, k];
                }
            }

            return result;
        }

        public Matrix MultiplyVinograd(Matrix matr)
        {
            Matrix result = new Matrix(n, matr.M);
            double[] rowFactor = new double[n];
            double[] colFactor = new double[matr.M];

            int d = m / 2;
            for (int i = 0; i < n; i++)
            {
                rowFactor[i] = data[i, 0] * data[i, 1];
                for (int j = 1; j < d; j++)
                    rowFactor[i] = rowFactor[i] + data[i, 2 * j] * data[i, 2 * j + 1];
            }

            for (int i = 0; i < matr.M; i++)
            {
                colFactor[i] = matr[0, i] * matr[1, i];
                for (int j = 1; j < d; j++)
                    colFactor[i] = colFactor[i] + matr[2 * j, i] * matr[2 * j + 1, i];
            }

            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < matr.M; j++)
                {
                    result[i, j] = -rowFactor[i] - colFactor[j];
                    for (int k = 0; k < d; k++)
                        result[i, j] = result[i, j] + (data[i, 2 * k] + matr[2 * k + 1, j]) * (data[i, 2 * k + 1] + matr[2 * k, j]);
                }
            }

            if (m % 2 == 1)
            {
                for (int i = 0; i < n; i++)
                    for (int j = 0; j < matr.M; j++)
                        result[i, j] = result[i, j] + data[i, n - 1] * matr[n - 1, j];
            }

            return result;
        }

        public Matrix MultiplyVinogradOptimised(Matrix matr)
        {
            Matrix result = new Matrix(n, matr.M);
            double[] rowFactor = new double[n];
            double[] colFactor = new double[matr.M];

            for (int i = 0; i < n; i++)
            {
                rowFactor[i] = colFactor[i] = 0;
                for (int j = 0; j < m - 1; j += 2)
                {
                    rowFactor[i] += data[i, j] * data[i, j + 1];
                    colFactor[i] += matr[j, i] * matr[j + 1, i];
                }
            }

            for (int i = 0; i < n; i++)
                for (int j = 0; j < matr.M; j++)
                {
                    double res = -rowFactor[i] - colFactor[j];
                    for (int k = 0; k < m - 1; k += 2)
                        res += (data[i, k] + matr[k + 1, j]) * (data[i, k + 1] + matr[k, j]);

                    result[i, j] = res;
                }

            if (m % 2 != 0)
                for (int i = 0; i < n; i++)
                    for (int j = 0; j < matr.M; j++)
                        result[i, j] += data[i, m - 1] * matr[matr.N - 1, j];

            return result;
        }
    }

    class Program
    {
        static double CheckTime(int multf_num, int len, int n)
        {
            Stopwatch sw = new Stopwatch();

            Matrix a = new Matrix(len, len);
            Matrix b = new Matrix(len, len);

            a.GenMatrix();
            b.GenMatrix();

            for (int i = 0; i < n; i++)
            {
                switch (multf_num)
                {
                    case 0:
                        sw.Start();
                        a.MultiplyStandart(b);
                        sw.Stop();
                        break;
                    case 1:
                        sw.Start();
                        a.MultiplyVinograd(b);
                        sw.Stop();
                        break;
                    case 2:
                        sw.Start();
                        a.MultiplyVinogradOptimised(b);
                        sw.Stop();
                        break;
                    default:
                        return 0;
                }
            }

            return sw.Elapsed.TotalSeconds / n;
        }


        static void Main(string[] args)
        {
            Matrix a = new Matrix(2, 2);
            Matrix b = new Matrix(2, 3);

            a[0, 0] = 1;
            a[0, 1] = 2;
            a[1, 0] = 3;
            a[1, 1] = 4;

            b[0, 0] = 2;
            b[0, 1] = 3;
            b[0, 2] = 7;
            b[1, 0] = 5;
            b[1, 1] = 1;
            b[1, 2] = 10;

            Matrix c = a.MultiplyStandart(b);

            a.PrintMatrix();
            Console.WriteLine();

            b.PrintMatrix();
            Console.WriteLine();

            c.PrintMatrix();

            //int times = 10;

            //for (int i = 100; i <= 1000; i += 100)
            //    Console.WriteLine(string.Format("{0}\t{1,10:f3}\t{2,10:f3}\t{3,10:f3}", i, CheckTime(0, i, times), CheckTime(1, i, times), CheckTime(2, i, times)));
            //Console.WriteLine();
            //for (int i = 101; i <= 1001; i += 100)
            //    Console.WriteLine(string.Format("{0}\t{1,10:f3}\t{2,10:f3}\t{3,10:f3}", i, CheckTime(0, i, times), CheckTime(1, i, times), CheckTime(2, i, times)));
            //Console.WriteLine();
        }
    }
}
