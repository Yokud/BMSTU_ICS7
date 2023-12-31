using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TrendLineLib
{
    public class PolynomialTrendLine : BaseTrendLine
    {
        public override List<Point> GetLinePoints(IEnumerable<Point> points)
        {
            if (points.ToList().Count == 0 || points == null)
                return null;

            double x_min = points.Min(p => p.X);
            double x_max = points.Max(p => p.X);

            double step = Math.Abs(x_max - x_min) / 100;
            List<Point> polypts = new List<Point>();
            for (double curr = x_min; curr <= x_max; curr += step)
                polypts.Add(new Point(curr, F(curr)));

            return polypts;
        }

        public override double F(double x)
        {
            double sum = 0;

            for (int i = 0; i < coefs.Count; i++)
                sum += coefs[i] * Math.Pow(x, i);

            return sum;
        }
    }
}
