using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace Lab_04
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        public struct Point
        {
            public double x, y, p;

            public Point(double x, double y, double p)
            {
                this.x = x;
                this.y = y;
                this.p = p;
            }
            public static List<Point> ReadFromGrid(DataGridView data)
            {
                List<Point> points = new List<Point>();

                foreach (DataGridViewRow row in data.Rows)
                    try
                    {
                        if (!row.IsNewRow)
                            points.Add(new Point(double.Parse(row.Cells[0].Value.ToString(), System.Globalization.CultureInfo.InvariantCulture), 
                                                 double.Parse(row.Cells[1].Value.ToString(), System.Globalization.CultureInfo.InvariantCulture), 
                                                 double.Parse(row.Cells[2].Value.ToString(), System.Globalization.CultureInfo.InvariantCulture)
                                                 ));
                    }
                    catch (Exception Ee)
                    {
                        MessageBox.Show(Ee.ToString(), "Ошибка чтения таблицы");
                        break;
                    }

                return points;
            }
        }

        public static List<double> Gauss(double[,] matrix, int power)
        {
            double[] a = new double[power];

            for (int k = 1; k < power; k++)
                for (int j = k; j < power; j++)
                {
                    double m = matrix[j, k - 1] / matrix[k - 1, k - 1];

                    for (int i = 0; i < power + 1; i++)
                        matrix[j, i] -= m * matrix[k - 1, i];
                }

            for (int i = power - 1; i >= 0; i--)
            {
                a[i] = matrix[i, power] / matrix[i, i];

                for (int c = power - 1; c > i; c--)
                    a[i] -= matrix[i, c] * a[c] / matrix[i, i];
            }

            return a.ToList();
        }

        public static List<double> LeastSquares(List<Point> points, int power)
        {
            int n = points.Count;
            double[,] matrix = new double[power + 1, power + 2];
            
            for (int k = 0; k <= power; k++)
            {
                double sum = 0;
                for (int i = 0; i < n; i++)
                    sum += points[i].p * Math.Pow(points[i].x, k) * points[i].y;
                matrix[k, power + 1] = sum;

                for (int m = 0; m <= power; m++)
                {
                    sum = 0;
                    for (int i = 0; i < n; i++)
                        sum += points[i].p * Math.Pow(points[i].x, k + m);
                    matrix[k, m] = sum;
                }
            }

            return Gauss(matrix, power + 1);
        }

        public static List<(double, double)> GenPolynome(List<Point> points, List<double> coefs)
        {
            double CanonPolynome(double x)
            {
                double sum = 0;

                for (int i = 0; i < coefs.Count; i++)
                    sum += coefs[i] * Math.Pow(x, i);

                return sum;
            }

            double x_min = points[0].x;
            double x_max = points[0].x;
            foreach (Point p in points)
            {
                x_min = Math.Min(x_min, p.x);
                x_max = Math.Max(x_max, p.x);
            } 

            double step = Math.Abs(x_max - x_min) / 100;
            List<(double, double)> polypts = new List<(double, double)>();
            for (double curr = x_min; curr <= x_max; curr += step)
                polypts.Add((curr, CanonPolynome(curr)));

            return polypts;
        }

        private void buttonAction_Click(object sender, EventArgs e)
        {
            foreach (var p in chart1.Series)
                p.Points.Clear();

            List<Point> points = Point.ReadFromGrid(dataGridView);

            foreach (Point p in points)
                chart1.Series[0].Points.AddXY(p.x, p.y);

            for (int n = 1; n < 4; n++)
            {
                List<double> a = LeastSquares(points, n);

                List<(double, double)> polynome_points = GenPolynome(points, a);

                foreach (var p in polynome_points)
                    chart1.Series[n].Points.AddXY(p.Item1, p.Item2);
            }

            chart1.Show();
        }
    }
}
