using System;
using System.Collections.Generic;
using System.IO;

namespace CA_Lab_02
{
    // Структура, хранящая информацию о точке
    struct PointInfo
    {
        public double x;
        public double y;

        public PointInfo(double x, double y)
        {
            this.x = x;
            this.y = y;
        }

        // Получение информации о точке из строки
        public static double[] GetNumbers(string s)
        {
            string[] s_splited = s.Split(' ');

            double[] numbers = new double[s_splited.Length];

            for (int i = 0; i < s_splited.Length; i++)
                numbers[i] = Convert.ToDouble(s_splited[i], System.Globalization.CultureInfo.InvariantCulture);

            return numbers;
        }

        public static List<PointInfo> FormPointsArr(double[] x_arr, double[] y_arr)
        {
            List<PointInfo> points = new();

            for (int i = 0; i < Math.Min(x_arr.Length, y_arr.Length); i++)
                points.Add(new PointInfo(x_arr[i], y_arr[i]));

            return points;
        }
    }

    class Program
    {
        static void PrintError(string s)
        {
            Console.Write(s);
            Console.Read();
            Environment.Exit(1);
        }


        static double GetDividedDiff(double x0, double xn, double y0, double yn) => (y0 - yn) / (x0 - xn);


        // Вычисление участка данных, где будет происходить интерполяция
        static (int start, int end) GetDataInterval(double x, int n, List<PointInfo> data)
        {
            int index = 0;
            double min_diff = Math.Abs(x - data[0].x);

            for (int i = 1; i < data.Count; i++)
                if (min_diff > Math.Abs(x - data[i].x))
                {
                    index = i;
                    min_diff = Math.Abs(x - data[i].x);
                }

            (int start, int end) interval = (index, index);

            if (n % 2 != 0 && interval.start - 1 >= 0 && interval.end + 1 < data.Count)
            {
                if (Math.Abs(x - data[interval.start - 1].x) < Math.Abs(x - data[interval.end + 1].x))
                    interval.start -= 1;
                else
                    interval.end += 1;
            }

            interval.start = interval.start - n / 2 < 0 ? interval.start : interval.start - n / 2;
            interval.end = interval.end + n / 2 >= data.Count ? interval.end : interval.end + n / 2;

            return interval;
        }

        static double NewtonPolynome(int n, double x, List<PointInfo> data)
        {
            var (start, end) = GetDataInterval(x, n, data);
            int nodes_count = end - start + 1;

            double[,] div_diff_table = new double[nodes_count, n + 2];

            for (int i = 0; i < nodes_count; i++)
            {
                div_diff_table[i, 0] = data[start + i].x;
                div_diff_table[i, 1] = data[start + i].y;
            }

            for (int j = 2, step = 1; j < n + 2; j++, step++)
                for (int i = 0; i < nodes_count + 1 - j; i++)
                    div_diff_table[i, j] = GetDividedDiff(div_diff_table[i, 0], div_diff_table[i + step, 0],
                                                          div_diff_table[i, j - 1], div_diff_table[i + 1, j - 1]);

            double res = div_diff_table[0, 1];
            double temp = 1;
            for (int i = 0; i < nodes_count - 1; i++)
            {
                temp *= x - div_diff_table[i, 0];

                res += temp * div_diff_table[0, i + 2];
            }

            return res;
        }

        static double InterTwoDimFunc(double[] x_arr, double[] y_arr, double[][] z_matr, int nx, int ny, double x, double y)
        {
            List<PointInfo> points;
            double[] x_inter_res = new double[ny + 1];

            for (int i = 0; i < ny + 1; i++)
            {
                points = PointInfo.FormPointsArr(x_arr, z_matr[i]);
                x_inter_res[i] = NewtonPolynome(nx, x, points);
            }

            points = PointInfo.FormPointsArr(y_arr, x_inter_res);

            double res = NewtonPolynome(ny, y, points);

            return res;
        }

        static void PrintTable(double[] x_arr, double[] y_arr, double[][] z_matr, double x, double y)
        {
            Console.WriteLine("x---------x---------x---------x---------x");
            Console.WriteLine("|         |  nx = 1 |  nx = 2 |  nx = 3 |");
            Console.WriteLine("x---------x---------x---------x---------x");
            Console.Write("| ny = 1  |");

            for (int nx = 1; nx < 4; nx++)
            {
                double res = InterTwoDimFunc(x_arr, y_arr, z_matr, nx, 1, x, y);
                Console.Write("{0,9:f6}|", res);
            }
            Console.WriteLine();

            Console.Write("| ny = 2  |");
            for (int nx = 1; nx < 4; nx++)
            {
                double res = InterTwoDimFunc(x_arr, y_arr, z_matr, nx, 2, x, y);
                Console.Write("{0,9:f6}|", res);
            }
            Console.WriteLine();

            Console.Write("| ny = 3  |");
            for (int nx = 1; nx < 4; nx++)
            {
                double res = InterTwoDimFunc(x_arr, y_arr, z_matr, nx, 3, x, y);
                Console.Write("{0,9:f6}|", res);
            }
            Console.WriteLine();

            Console.WriteLine("x---------x---------x---------x---------x");
        }

        static void Main(string[] args)
        {
            string s = @"..\..\..\..\data.txt";

            if (!File.Exists(s))
                PrintError("Такого файла с данными не существует!");

            StreamReader Table = File.OpenText(s);

            double[] x_arr = PointInfo.GetNumbers(Table.ReadLine());
            double[] y_arr = PointInfo.GetNumbers(Table.ReadLine());

            double[][] z_matr = new double[y_arr.Length][];

            for (int i = 0; i < y_arr.Length; i++)
                z_matr[i] = PointInfo.GetNumbers(Table.ReadLine());

            Table.Close();

            double x = 1.5, y = 1.5;
            PrintTable(x_arr, y_arr, z_matr, x, y);
        }
    }
}
