using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace InformationCentre
{
    using Generator = Func<double>;

    internal interface Processor
    {
        bool GetRequest();
    }

    static class ModelTimer
    {
        public static double CurrentTime { get; set; } = 0;
    }

    class RequestGenerator
    {
        Generator generator;
        public int numberOfGeneratedRequests;
        public double timeOfNextEvent;
        List<Processor> receivers;

        public RequestGenerator(Generator generator)
        {
            this.generator = generator;
            numberOfGeneratedRequests = 0;
            receivers = new List<Processor>();
            timeOfNextEvent = 0;
        }

        public void SubscribeReceiver(Processor receiver) 
        {
            receivers.Add(receiver);
        }

        public double GetNextTime() => generator();

        public Processor SendRequest()
        {
            numberOfGeneratedRequests++;
            foreach (var receiver in receivers)
            {
                if (receiver.GetRequest())
                    return receiver;
            }

            return null;
        }
    }

    class RequestProcessor: RequestGenerator, Processor
    {
        public int numberOfRequestsInQueue, numberOfProcessedRequests;
        int maxOfQueue;

        public RequestProcessor(Generator generator, int maxOfQueue = 0) : base(generator)
        {
            numberOfRequestsInQueue = 0;
            numberOfProcessedRequests = 0;
            this.maxOfQueue = maxOfQueue;
        }

        public void Process()
        {
            if (numberOfRequestsInQueue > 0)
            {
                numberOfProcessedRequests++;
                numberOfRequestsInQueue--;
                SendRequest();
            }

            timeOfNextEvent = numberOfRequestsInQueue > 0 ? ModelTimer.CurrentTime + GetNextTime() : 0.0;
        }

        public bool GetRequest()
        {
            if (maxOfQueue == 0 || numberOfRequestsInQueue < maxOfQueue)
            {
                numberOfRequestsInQueue++;
                if (timeOfNextEvent == 0)
                    timeOfNextEvent = ModelTimer.CurrentTime + GetNextTime();

                return true;
            }
            else
                return false;
        }
    }
}
