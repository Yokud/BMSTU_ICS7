using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MathNet.Numerics.Distributions;

namespace InformationCentre
{
    static class UniformDistributions
    {
        public static double GetUniformReal(double aParameter, double bParameter)
        {
            return ContinuousUniform.Sample(aParameter, bParameter);
        }

        public static int GetUniformInt(int aParameter, int bParameter) 
        {
            return (int)Math.Round(ContinuousUniform.Sample(aParameter, bParameter));
        }
    }
}
