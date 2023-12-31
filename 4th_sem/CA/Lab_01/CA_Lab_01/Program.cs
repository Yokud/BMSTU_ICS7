using System;
using System.IO;
using System.Collections.Generic;


namespace CA_Lab_01
{
    // Структура, хранящая информацию о точке
    struct PointInfo
    {
        public double x;
        public double y;
        public double der_y; // первая производная в точке x

        public PointInfo(double x, double y, double der_y)
        {
            this.x = x;
            this.y = y;
            this.der_y = der_y;
        }

        public static List<PointInfo> ReadPointsFromFile(string s)
        {
            if (!File.Exists(s))
                return null;

            StreamReader Table = File.OpenText(s);
            List<PointInfo> ListOfPoints = new List<PointInfo>();

            while (!Table.EndOfStream)
            {
                double[] p_inf = GetNumbers(Table.ReadLine());

                ListOfPoints.Add(new PointInfo(p_inf[0], p_inf[1], p_inf[2]));
            }

            return ListOfPoints;
        }

        // Получение информации о точке из строки
        private static double[] GetNumbers(string s)
        {
            string[] s_splited = s.Split(' ');

            double[] numbers = new double[s_splited.Length];

            for (int i = 0; i < s_splited.Length; i++)
                numbers[i] = Convert.ToDouble(s_splited[i], System.Globalization.CultureInfo.InvariantCulture);

            return numbers;
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


        static double HermitePolynome(int n, double x, List<PointInfo> data)
        {
            var (start, end) = GetDataInterval(x, n, data);
            int nodes_count = end - start + 1;

            if (n > 2)
            {
                if (nodes_count == n + 1)
                {
                    start += 1;
                    end -= 1;
                }
                else
                {
                    end = start == 0 ? end - 1 : end;
                    start = end == data.Count - 1 ? start + 1 : start;
                }
            }
            
            double[,] div_diff_table = new double[nodes_count, n + 2];
            double[] deriatives = new double[nodes_count]; // Массив производных во взятых точках

            for (int i = 0, j = start; i < nodes_count; i++, j += (i + 1) % 2)
            {
                div_diff_table[i, 0] = data[j].x;
                div_diff_table[i, 1] = data[j].y;
                deriatives[i] = data[j].der_y;
            }

            for (int j = 2, step = 1; j < n + 2; j++, step++)
                for (int i = 0; i < nodes_count + 1 - j; i++)
                    if (div_diff_table[i, 0] != div_diff_table[i + step, 0])
                        div_diff_table[i, j] = GetDividedDiff(div_diff_table[i, 0], div_diff_table[i + step, 0],
                                                                div_diff_table[i, j - 1], div_diff_table[i + 1, j - 1]);
                    else
                        div_diff_table[i, j] = deriatives[i];

            double res = div_diff_table[0, 1];
            double temp = 1;
            for (int i = 0; i < nodes_count - 1; i++)
            {
                temp *= x - div_diff_table[i, 0];

                res += temp * div_diff_table[0, i + 2];
            }

            return res;
        }


        static double GetRoot(int n, List<PointInfo> data)
        {
            bool root_is_not_exist = true;

            for (int i = 0; i < data.Count - 1 && root_is_not_exist; i++)
                root_is_not_exist = data[i].y * data[i + 1].y > 0;

            if (root_is_not_exist)
                return double.NaN;

            List<PointInfo> inverted_data = new List<PointInfo>();

            for (int i = 0; i < data.Count; i++)
                inverted_data.Add(new PointInfo(data[i].y, data[i].x, 0));

            return NewtonPolynome(n, 0, inverted_data);
        }


        static void Main(string[] args)
        {
            List<PointInfo> Points = PointInfo.ReadPointsFromFile(@"..\..\data.txt");
            double x;
            int n_max = 4;

            if (Points == null)
                PrintError("Такого файла с данными не существует!");

            Console.Write("Введите значение аргумента x: ");
            x = double.Parse(Console.ReadLine(), System.Globalization.CultureInfo.InvariantCulture);

            if (x < Points[0].x || x > Points[Points.Count - 1].x)
                PrintError("Значение аргумента находится за пределами данных!");


            double[,] res = new double[n_max, 2];

            for (int i = 0; i < n_max; i++)
            {
                res[i, 0] = NewtonPolynome(i + 1, x, Points);
                res[i, 1] = HermitePolynome(i + 1, x, Points);
            }

            Console.WriteLine("Таблица сравнения полиномов Ньютона и Эрмита при x = " + x.ToString());
            Console.WriteLine("Степень    Ньютон      Эрмит");
            Console.WriteLine("полинома");
            for (int i = 0; i < n_max; i++)
                Console.WriteLine(string.Format("{0,5:d}    {1,9:f6}   {2,9:f6}", i + 1, res[i, 0], res[i, 1]));

            double root = GetRoot(n_max, Points);

            if (root == double.NaN)
                Console.WriteLine("\nУ этой табличной функции нет корня.");
            else
                Console.WriteLine("\nКорень это табличной функции: {0:f6}", root);

            Console.Read();
        }
    }
}
