using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MathNet.Numerics.Distributions;

namespace Lab_1
{
    internal interface IGenerator
    {
        double GenerationTime();
    }

    public class RayleighGenerator : IGenerator
    {
        double _scale;

        public RayleighGenerator(double scale)
        {
            if (scale < 0) 
                throw new ArgumentOutOfRangeException(nameof(scale));

            _scale = scale;
        }

        public double GenerationTime()
        {
            return Rayleigh.Sample(_scale);
        }
    }

    public class UniformGenerator : IGenerator
    {
        double _a, _b;

        public UniformGenerator(double intensity, double range) 
        {
            _a = intensity - Math.Sqrt(range) / 2;
            _b = intensity + Math.Sqrt(range) / 2;

            if (_a < 0)
            {
                _b -= _a;
                _a = 0;
            }
        }

        public double GenerationTime() 
        {
            return ContinuousUniform.Sample(_a, _b);
        }
    }

    public class NormalGenerator : IGenerator
    {
        double _mx, _dx;

        public NormalGenerator(double mx, double dx) 
        {
            _mx = mx;
            _dx = dx;
        }

        public double GenerationTime()
        {
            return Normal.Sample(_mx, _dx);
        }
    }
}
