using System;
using System.Collections.Generic;
using System.Threading;
using System.Diagnostics;

namespace GeneralizedMeanParallel
{
    class Matrix
    {
        int n, m;
        double[,] matrix;

        public int N
        {
            get { return n; }
            set
            {
                if (value >= 0)
                    n = value;
            }
        }

        public int M
        {
            get { return m; }
            set
            {
                if (value >= 0)
                    m = value;
            }
        }

        public Matrix(int n, int m)
        {
            N = n;
            M = m;
            matrix = new double[n, m];
        }

        public Matrix(int n, int m, List<double> nums)
        {
            N = n;
            M = m;
            matrix = new double[n, m];

            if (nums.Count != n * m)
                throw new Exception("Число элементов не соответсвует размеру матриц");

            int count = 0;
            foreach (double elem in nums)
            {
                matrix[count / m, count % m] = elem;
                count++;
            }
        }

        public double this[int i, int j]
        {
            get { return matrix[i, j]; }
            set { matrix[i, j] = value; }
        }

        public void Print()
        {
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                    Console.Write(matrix[i, j].ToString() + " ");
                Console.WriteLine();
            }
        }

        public static Matrix GetRandom(int n, int m)
        {
            Matrix a = new Matrix(n, m);
            Random rnd = new Random();

            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    a[i, j] = rnd.NextDouble() * 200 - 100;

            return a;
        }

        // Среднее степенное строк матрицы
        public double[] RowsGenMean(double power)
        {
            double[] gen_means = new double[n];

            for (int i = 0; i < n; i++)
            {
                double sum = 0;
                for (int j = 0; j < m; j++)
                    sum += Math.Pow(matrix[i, j], power);

                gen_means[i] = Math.Pow(sum / m, 1.0 / power);
            }

            return gen_means;
        }

        public double[] RowsGenMeanParallel(double power, int num_threads = 1)
        {
            Thread[] threads = new Thread[num_threads];
            double[] gen_means = new double[n];

            int parts = n / num_threads + (n % num_threads != 0 ? 1 : 0);

            for (int i = 0; i < num_threads; i++)
            {
                threads[i] = new Thread(GenMeanThread);

                Args args = new Args(i * parts, (i + 1) * parts > n ? n : (i + 1) * parts, power);

                threads[i].Start(args);
            }

            foreach (Thread t in threads)
                t.Join();

            return gen_means;

            void GenMeanThread(object obj)
            {
                Args args = (Args)obj;
                var (start, end) = (args.row_indx_start, args.row_indx_end);
                double pow = args.power;

                for (int i = start; i < end; i++)
                {
                    double sum = 0;
                    for (int j = 0; j < m; j++)
                        sum += Math.Pow(matrix[i, j], pow);

                    gen_means[i] = Math.Pow(sum / m, 1.0 / pow);
                }
            }
        }

        private struct Args
        {
            public int row_indx_start, row_indx_end;
            public double power;

            public Args(int start, int end, double p)
            {
                row_indx_start = start;
                row_indx_end = end;
                power = p;
            }
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            int command = -1;

            while (command != 0)
            {
                Console.Write("\nВычисление среднего степенного по строкам матрицы.\nКоманды:\n" +
                    "\t1 - Ввод матрицы и степени, получение и сравнение результатов однопоточной и многопоточной реализации алгоритма\n" +
                    "\t2 - Сравнение по времени однопоточной и многопоточной реализации алгоритма\n" +
                    "\t0 - Выход из программы\n\nВвод: ");
                command = int.Parse(Console.ReadLine());
                switch (command)
                {
                    case 0:
                        Console.WriteLine("Завершение работы.");
                        break;

                    case 1:
                        int n, m;
                        Console.Write("Введите размер матрицы: ");
                        string[] s = Console.ReadLine().Split(' ');
                        n = int.Parse(s[0]);
                        m = int.Parse(s[1]);

                        if (n <= 0 || m <= 0)
                        {
                            Console.WriteLine("Ошибка ввода размера матрицы!");
                            break;
                        }

                        Console.Write("Введите элементы матрицы: ");
                        List<double> nums = new List<double>();
                        string[] snums = Console.ReadLine().Split(' ');
                        foreach (string sn in snums)
                            nums.Add(double.Parse(sn, System.Globalization.NumberFormatInfo.InvariantInfo));

                        Matrix matr = new Matrix(n, m, nums);
                        matr.Print();

                        Console.Write("\nВведите степень: ");
                        double pow = double.Parse(Console.ReadLine(), System.Globalization.NumberFormatInfo.InvariantInfo);

                        double[] means = matr.RowsGenMean(pow);
                        Console.Write("Результат (обычный алгоритм): ");
                        foreach (double d in means)
                            Console.Write(string.Format("{0, 7:g5} ", d));
                        Console.WriteLine();

                        Console.Write("\nВведите число потоков: ");
                        int threads = int.Parse(Console.ReadLine());

                        if (threads <= 0)
                        {
                            Console.WriteLine("Невозможное число потоков!");
                            break;
                        }

                        means = matr.RowsGenMeanParallel(pow, threads);
                        Console.Write("Результат(параллельный алгоритм): ");
                        foreach (double d in means)
                            Console.Write(string.Format("{0, 7:g5} ", d));
                        Console.WriteLine();
                        break;

                    case 2:

                        Matrix a = Matrix.GetRandom(1024, 1024);
                        int count = 100;
                        Console.WriteLine("Размер матрицы: " + a.N.ToString() + " на " + a.M.ToString());

                        Stopwatch sw = Stopwatch.StartNew();

                        for (int j = 0; j < count; j++)
                            a.RowsGenMean(2);

                        sw.Stop();

                        Console.WriteLine("Однопоток: " + (sw.ElapsedTicks / count).ToString() + '\n');

                        for (int i = 1; i <= 32; i *= 2)
                        {
                            sw = Stopwatch.StartNew();

                            for (int j = 0; j < count; j++)
                                a.RowsGenMeanParallel(2, i);

                            sw.Stop();

                            Console.WriteLine(i.ToString() + ": " + (sw.ElapsedTicks / (count * i)).ToString());
                        }

                        break;

                    default:
                        Console.WriteLine("Неизвестная команда");
                        break;
                }
            }
        }
    }
}
