using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace InformationCentre
{
    struct SimulationParameters
    {
        public Client client;
        public Operator operator1, operator2, operator3;
        public Computer computer1, computer2;

        public SimulationParameters(Client client, Operator operator1, Operator operator2, Operator operator3, Computer computer1, Computer computer2)
        {
            this.client = client;
            this.operator1 = operator1;
            this.operator2 = operator2;
            this.operator3 = operator3;
            this.computer1 = computer1;
            this.computer2 = computer2;
        }
    }

    struct Client
    {
        public int timeOfCome, timeDelta, amountOfProccessedNeeded;

        public Client(int timeOfCome, int timeDelta, int amountOfProccessedNeeded)
        {
            this.timeDelta = timeDelta;
            this.timeOfCome = timeOfCome;
            this.amountOfProccessedNeeded = amountOfProccessedNeeded;
        }
    }

    struct Operator
    {
        public int timeOfService, timeDelta;

        public Operator(int timeOfService, int timeDelta)
        {
            this.timeOfService = timeOfService;
            this.timeDelta = timeDelta;
        }
    }

    struct Computer
    {
        public int timeOfService;

        public Computer(int timeOfService) 
        {
            this.timeOfService = timeOfService;
        }
    }

    struct Results
    {
        public int numberOfDenials;
        public double probabilityOfDenial;

        public Results(int numberOfDenials, double probabilityOfDenial)
        {
            this.numberOfDenials = numberOfDenials;
            this.probabilityOfDenial = probabilityOfDenial;
        }

        public static Results DoSimulate(SimulationParameters parameters)
        {
            RequestGenerator generatorOfClients = new RequestGenerator(() => 
                UniformDistributions.GetUniformReal(
                    parameters.client.timeOfCome - parameters.client.timeDelta,
                    parameters.client.timeOfCome + parameters.client.timeDelta));

            RequestProcessor operator1 = new RequestProcessor(() => 
                UniformDistributions.GetUniformReal(
                    parameters.operator1.timeOfService - parameters.operator1.timeDelta,
                    parameters.operator1.timeOfService + parameters.operator1.timeDelta), 1);

            RequestProcessor operator2 = new RequestProcessor(() =>  
                UniformDistributions.GetUniformReal(
                    parameters.operator2.timeOfService - parameters.operator2.timeDelta,
                    parameters.operator2.timeOfService + parameters.operator2.timeDelta), 1);

            RequestProcessor operator3 = new RequestProcessor(() => 
                UniformDistributions.GetUniformReal(
                    parameters.operator3.timeOfService - parameters.operator3.timeDelta,
                    parameters.operator3.timeOfService + parameters.operator3.timeDelta), 1);

            RequestProcessor computer1 = new RequestProcessor(() => parameters.computer1.timeOfService);
            RequestProcessor computer2 = new RequestProcessor(() => parameters.computer2.timeOfService);

            generatorOfClients.SubscribeReceiver(operator1);
            generatorOfClients.SubscribeReceiver(operator2);
            generatorOfClients.SubscribeReceiver(operator3);

            operator1.SubscribeReceiver(computer1);
            operator2.SubscribeReceiver(computer1);
            operator3.SubscribeReceiver(computer2);

            RequestGenerator[] schemeElements = new RequestGenerator[]{
                generatorOfClients, operator1, operator2, operator3, computer1, computer2};

            int numberOfDenials = 0;
            generatorOfClients.timeOfNextEvent = generatorOfClients.GetNextTime();

            while (computer1.numberOfProcessedRequests + computer2.numberOfProcessedRequests <
                   parameters.client.amountOfProccessedNeeded)
            {
                ModelTimer.CurrentTime = generatorOfClients.timeOfNextEvent;
                foreach (var element in schemeElements)
                {
                    if (element.timeOfNextEvent != 0 && element.timeOfNextEvent < ModelTimer.CurrentTime)
                    {
                        ModelTimer.CurrentTime = element.timeOfNextEvent;
                    }
                }

                foreach (var element in schemeElements)
                {
                    if (ModelTimer.CurrentTime == element.timeOfNextEvent)
                    {
                        RequestProcessor processor = element as RequestProcessor;
                        if (processor is not null)
                            processor.Process();
                        else
                        {
                            Processor catchProcessor = generatorOfClients.SendRequest();
                            if (catchProcessor is null)
                                numberOfDenials++;

                            generatorOfClients.timeOfNextEvent = ModelTimer.CurrentTime + generatorOfClients.GetNextTime();
                        }
                    }
                }
            }

            return new Results(numberOfDenials, numberOfDenials / ((double)numberOfDenials + operator1.numberOfProcessedRequests +
                operator2.numberOfProcessedRequests +
                operator3.numberOfProcessedRequests));
        }
    }
}
