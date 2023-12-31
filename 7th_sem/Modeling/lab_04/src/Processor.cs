using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using MathNet.Numerics.Distributions;

namespace QueueModeling
{
    internal class Processor
    {
        double lambda;

        public Processor(double lambda, double probabilityOfReturnToQueue)
        {
            this.lambda = lambda;
            ProbabilityOfReturnToQueue = probabilityOfReturnToQueue;
        }

        public void GetRequest()
        {
            CurrentNumberOfRequestsInQueue++;

            if (CurrentNumberOfRequestsInQueue > DetectedMaxOfRequestsInQueue) 
                DetectedMaxOfRequestsInQueue = CurrentNumberOfRequestsInQueue;
        }

        public void ProcessRequest()
        {
            if (CurrentNumberOfRequestsInQueue == 0)
                return;

            CurrentNumberOfRequestsInQueue--;
            if (ContinuousUniform.Sample(0, 1) < ProbabilityOfReturnToQueue)
            {
                NumberOfReturnedRequests++;
                GetRequest();
            }
        }

        public double GetNextTimeOfRequestProcessed()
        {
            return Poisson.Sample(lambda);
        }

        public int DetectedMaxOfRequestsInQueue { get; set; }
        public int CurrentNumberOfRequestsInQueue { get; set; }
        public int NumberOfReturnedRequests { get; set; }
        public double ProbabilityOfReturnToQueue { get; set; }
    }
}
