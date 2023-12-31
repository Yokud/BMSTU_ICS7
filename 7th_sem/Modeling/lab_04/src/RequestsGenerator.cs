using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MathNet.Numerics.Distributions;

namespace QueueModeling
{
    internal class RequestsGenerator
    {
        double a, b;

        public RequestsGenerator(double a, double b)
        {
            this.a = a;
            this.b = b;
        }

        public double GetNextTimeOfRequestGenerated()
        {
            return ContinuousUniform.Sample(a, b);
        }
    }
}
