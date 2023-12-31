using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace QueueModeling
{
    internal class Simulator
    {
        Processor processor;
        RequestsGenerator requestGenerator;

        public Simulator(Processor processor, RequestsGenerator requestGenerator) 
        {
            this.processor = processor;
            this.requestGenerator = requestGenerator;
        }

        public (double, double) SimulateUsingDeltaTMethod(int requestsCount)
        {
            double timeOfGeneration = requestGenerator.GetNextTimeOfRequestGenerated();
            double timeOfProcessing = timeOfGeneration + processor.GetNextTimeOfRequestProcessed();

            int numberOfSentRequests = 0;
            for (double currentTime = 0; numberOfSentRequests < requestsCount; currentTime += 1e-3)
            {
                while (timeOfGeneration <= currentTime)
                {
                    numberOfSentRequests++;
                    processor.GetRequest();

                    timeOfGeneration += requestGenerator.GetNextTimeOfRequestGenerated();
                }

                while (timeOfProcessing <= currentTime)
                {
                    processor.ProcessRequest();

                    if (processor.CurrentNumberOfRequestsInQueue > 0)
                        timeOfProcessing += processor.GetNextTimeOfRequestProcessed();
                    else
                        timeOfProcessing = timeOfGeneration + processor.GetNextTimeOfRequestProcessed();
                }
            }

            while (processor.CurrentNumberOfRequestsInQueue > 0)
                processor.ProcessRequest();

            return (processor.NumberOfReturnedRequests, processor.DetectedMaxOfRequestsInQueue);
        }

        public (double, double) SimulateUsingEventMethod(int requestsCount) 
        {
            double timeOfGeneration = requestGenerator.GetNextTimeOfRequestGenerated();
            double timeOfProcessing = timeOfGeneration + processor.GetNextTimeOfRequestProcessed();

            int numberOfSentRequests = 0;
            while (numberOfSentRequests < requestsCount)
            {
                while (timeOfGeneration <= timeOfProcessing)
                {
                    numberOfSentRequests++;
                    processor.GetRequest();

                    timeOfGeneration += requestGenerator.GetNextTimeOfRequestGenerated();
                }

                while (timeOfGeneration >= timeOfProcessing)
                {
                    processor.ProcessRequest();

                    if (processor.CurrentNumberOfRequestsInQueue > 0)
                        timeOfProcessing += processor.GetNextTimeOfRequestProcessed();
                    else
                        timeOfProcessing = timeOfGeneration + processor.GetNextTimeOfRequestProcessed();
                }
            }

            while (processor.CurrentNumberOfRequestsInQueue > 0)
                processor.ProcessRequest();

            return (processor.NumberOfReturnedRequests, processor.DetectedMaxOfRequestsInQueue);
        }
    }
}
