using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_1
{
    internal class RequestProcessor
    {
        IGenerator _generator;
        int _currQueueSize, _maxQueue, _processedRequests, _reenteredRequests, _lenQueue, _numLostRequests;
        double _reenterProbability;
        List<double> _timePeriods;

        public RequestProcessor(IGenerator generator, int lenQueue = 0, double reenterProbability = 0)
        {
            _generator = generator;
            _lenQueue = lenQueue;
            _reenterProbability = reenterProbability;
            _timePeriods = new List<double>();
        }

        public int ProcessedRequests => _processedRequests;
        public int MaxQueue => _maxQueue;
        public int CurrentQueueSize => _currQueueSize;
        public int LostRequests => _numLostRequests;
        public int ReenteredRequests => _reenteredRequests;
        public List<double> TimePeriods => _timePeriods;

        public void Process()
        {
            if (_currQueueSize > 0)
            {
                Modeller.s_timeProcessedRequest.Add(Modeller.s_currentTime);
                _processedRequests += 1;
                _currQueueSize -= 1;
            }
        }

        public void ReceiveRequest()
        {
            _currQueueSize += 1;
            if (_currQueueSize > _maxQueue)
                _maxQueue += 1;
        }

        public double NextTimePeriod()
        {
            double time = _generator.GenerationTime();
            _timePeriods.Add(time);
            return time;
        }

        public void Clear()
        {
            _timePeriods.Clear();
            _currQueueSize = 0;
            _maxQueue = 0;
            _processedRequests = 0;
            _reenteredRequests = 0;
            _numLostRequests = 0;
        }
    }
}
