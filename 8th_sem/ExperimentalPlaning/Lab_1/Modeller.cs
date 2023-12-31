using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_1
{
    public struct ModelingResults
    {
        public double WorkloadFact, AvgTimeSMO;
        
        public ModelingResults(double lambdaFact, double muFact, double avgTimeSMO)
        {
            WorkloadFact = lambdaFact / muFact;
            AvgTimeSMO = avgTimeSMO;
        }
    }

    internal class Modeller
    {
        public static double s_currentTime = 0;
        public static List<double> s_timeProcessedRequest = new List<double>();

        RequestGenerator _generator;
        RequestProcessor _processor;

        public Modeller(RequestGenerator generator, RequestProcessor processor)
        {
            _generator = generator;
            _processor = processor;
            _generator.AddReceiver(_processor);
        }

        public ModelingResults RunTimeBasedModeling(double dt, double timeModeling) 
        {
            s_timeProcessedRequest.Clear();
            s_currentTime = 0;
            _generator.Clear();
            _processor.Clear();
            List<int> queueSize = new List<int>() { 0 };
            List<int> numRequests = new List<int>() { 0 };
            List<double> timeGeneratedRequest = new List<double>();

            double genPeriod = _generator.NextTimePeriod();
            double procPeriod = genPeriod + _processor.NextTimePeriod();

            while (s_currentTime < timeModeling) 
            {
                var num = numRequests[numRequests.Count - 1];
                if (genPeriod <= s_currentTime)
                {
                    timeGeneratedRequest.Add(s_currentTime);
                    _generator.EmitRequest();
                    num++;
                    genPeriod += _generator.NextTimePeriod();
                }

                if (procPeriod <= s_currentTime)
                {
                    if (_processor.CurrentQueueSize > 0)
                        num--;
                    _processor.Process();

                    if (_processor.CurrentQueueSize > 0)
                        procPeriod += _processor.NextTimePeriod();
                    else
                        procPeriod = genPeriod + _processor.NextTimePeriod();
                }

                queueSize.Add(_processor.CurrentQueueSize);

                numRequests.Add(num);
                s_currentTime += dt;
            }

            double lambdaFact = _generator.TimePeriods.Count / _generator.TimePeriods.Sum();
            double muFact = _processor.TimePeriods.Count / _processor.TimePeriods.Sum();
            double p = lambdaFact / muFact;
            double numReportsTeor = p / (1 - p);
            double numReportsFact = (double)queueSize.Sum() / queueSize.Count;
            double k = numReportsFact / numReportsTeor;

            if (Form1.s_pTeor >= 1 || Form1.s_pTeor <= 0 || k == 0)
                k = 1;

            double avgTimeSMO = 0;
            if (s_timeProcessedRequest.Count > 0)
            {
                List<double> masTimeRequestInSMO = new List<double>();
                for (int i = 0; i < s_timeProcessedRequest.Count; i++)
                    masTimeRequestInSMO.Add(s_timeProcessedRequest[i] - timeGeneratedRequest[i]);
                avgTimeSMO = masTimeRequestInSMO.Sum() / masTimeRequestInSMO.Count / k;
            }

            var res = new ModelingResults(lambdaFact, 
                                          muFact, 
                                          avgTimeSMO);

            return res;
        }

        public static void CreateGraph(out List<double> mas, out List<double> res)
        {
            double i = 0.001;
            mas = new List<double>();
            res = new List<double>();
            while (i < 1.01)
            {
                List<double> masI = new List<double>();
                for (int j = 0; j < 100; j++)
                {
                    double step = 0.1;
                    double timeModeling = 10000;
                    double intensivityGen = i;
                    double intensivityProc = 1;
                    double rangeProc = 2;
                    var generator = new RequestGenerator(new RayleighGenerator(1 / intensivityGen));
                    var processor = new RequestProcessor(new UniformGenerator(1 / intensivityProc, 1 / rangeProc));
                    var model = new Modeller(generator, processor);
                    var result = model.RunTimeBasedModeling(step, timeModeling);
                    masI.Add(result.AvgTimeSMO);
                }
                mas.Add(i);
                res.Add(masI.Sum() / (masI.Count + 1));
                masI.Clear();

                if (i < 0.1)
                    i += 0.01;
                else
                    i += 0.1;
            }
        }
    }
}
