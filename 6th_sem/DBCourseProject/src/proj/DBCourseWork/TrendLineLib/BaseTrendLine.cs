using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TrendLineLib
{
    public abstract class BaseTrendLine
    {
        protected List<double> coefs = null!;

        protected List<double> Gauss(double[,] matrix, int power)
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

        protected List<double> LeastSquares(List<Point> points, int power)
        {
            int n = points.Count;
            double[,] matrix = new double[power + 1, power + 2];

            for (int k = 0; k <= power; k++)
            {
                double sum = 0;
                for (int i = 0; i < n; i++)
                    sum += points[i].P * Math.Pow(points[i].X, k) * points[i].Y;
                matrix[k, power + 1] = sum;

                for (int m = 0; m <= power; m++)
                {
                    sum = 0;
                    for (int i = 0; i < n; i++)
                        sum += points[i].P * Math.Pow(points[i].X, k + m);
                    matrix[k, m] = sum;
                }
            }

            return Gauss(matrix, power + 1);
        }

        public List<double> GetCoefs(IEnumerable<Point> points)
        {
            if (points == null || points.ToList().Count == 0)
                return null;

            if (points.ToList().Count() == 1)
            {
                coefs = new List<double>() { points.ToList()[0].Y };
                return coefs;
            }

            int extremums = GetExtremumsCount(points.ToList());

            coefs = LeastSquares(points.ToList(), Math.Min(6, extremums + 1));

            return coefs;
        }



        protected int GetExtremumsCount(List<Point> points)
        {
            int extremums = 0;

            for (int i = 1; i < points.Count - 1; i++)
                if (points[i].Y > points[i + 1].Y && points[i].Y > points[i - 1].Y || points[i].Y < points[i + 1].Y && points[i].Y < points[i - 1].Y)
                    extremums++;

            return extremums;
        }

        public abstract List<Point> GetLinePoints(IEnumerable<Point> points);
        public abstract double F(double x);
    }
}
