using System;
using System.Collections.Generic;
using System.Diagnostics.CodeAnalysis;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Distribution
{
    public interface IDistribution
    {
        /// <summary>
        /// Функция распределения
        /// </summary>
        double CDF(double x);

        /// <summary>
        /// Функция плотности распределения
        /// </summary>
        double PMF(double x);
    }

    public class UniformDistribution : IDistribution
    {
        double a, b;

        public UniformDistribution(double a, double b)
        {
            if (b > a)
            {
                this.a = a;
                this.b = b;
            }
            else throw new ArgumentException("a >= b");
        }

        public double CDF(double x)
        {
            if (x >= b)
                return 1.0;
            else if (x < a)
                return 0.0;
            else
                return (x - a) / (b - a);
        }

        public double PMF(double x)
        {
            if (x > a && x < b)
                return 1.0 / (b - a);
            else
                return 0.0;
        }
    }

    public class PoissonDistribution : IDistribution
    {
        double lambda;

        public PoissonDistribution(double lambda)
        {
            if (lambda > 0.0)
                this.lambda = lambda;
            else
                throw new ArgumentException("Lambda <= 0");
        }

        public double CDF(double x)
        {
            double sum = 0;
            int k = (int)Math.Floor(x);

            for (int i = 0; i <= k; i++)
                sum += Math.Pow(lambda, i) / Factorial(i);

            return Math.Exp(-lambda) * sum;
        }

        public double PMF(double x)
        {
            int k = (int)Math.Floor(x);
            return (Math.Exp(-lambda) * Math.Pow(lambda, k)) / Factorial(k);
        }

        double Factorial(int n)
        {
            double mul = 1;
            for (int i = 1; i <= n; i++)
                mul *= i;

            return mul;
        }
    }
}
