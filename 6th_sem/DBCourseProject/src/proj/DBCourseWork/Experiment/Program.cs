using System;
using TrendLineLib;

namespace Experiment
{
    internal class Program
    {
        static void Main(string[] args)
        {
            List<int> costs = new List<int>() { 
                                                18299,
                                                17599,
                                                16399,
                                                18090,
                                                18090,
                                                18090,
                                                19590,
                                                17999,
                                                18299,
                                                18699,
                                                19999,
                                                27790,
                                                31599,
                                                29799,
                                                34299,
                                                24990,
                                                29390,
                                                28399
                                                 };
            List<Point> points = new List<Point>();

            for (int i = 0; i < costs.Count(); i++)
                points.Add(new Point(i + 1, costs[i]));

            PolynomialTrendLine line = new PolynomialTrendLine();

            int MinWindow = 2;
            int MaxWindow = 10;
            int N = points.Count - MaxWindow + 1;

            for (int i = MinWindow; i <= MaxWindow; i++)
            {
                List<double> errs = new List<double>();
                for (int j = MaxWindow; j < points.Count; j++)
                {
                    var lst = points.GetRange(j - i, i);
                    line.GetCoefs(lst);

                    double val = line.F(j + 1);
                    double real_val = points[j].Y;

                    errs.Add(Math.Abs(real_val - val) / real_val);
                }

                Console.WriteLine("{0} {2:f3} {3:f3} {1:f3}\n", i, errs.Sum() / N * 100, errs.Min() * 100, errs.Max() * 100);
            }
        }
    }
}