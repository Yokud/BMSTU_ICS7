using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_1
{
    internal class RequestGenerator
    {
        IGenerator _generator;
        HashSet<RequestProcessor> _receivers;
        List<double> _timePeriods;

        public RequestGenerator(IGenerator generator) 
        {
            _generator = generator;
            _receivers = new HashSet<RequestProcessor>();
            _timePeriods = new List<double>();
        }

        public List<double> TimePeriods => _timePeriods;

        public void AddReceiver(RequestProcessor processor) 
        {
            _receivers.Add(processor);
        }

        public void RemoveReceiver(RequestProcessor processor) 
        { 
            _receivers.Remove(processor);
        }

        public double NextTimePeriod()
        {
            double time = _generator.GenerationTime();
            _timePeriods.Add(time);
            return time;
        }

        public void EmitRequest()
        {
            foreach (var receiver in _receivers) 
                receiver.ReceiveRequest();
        }

        public void Clear()
        {
            _timePeriods.Clear();
        }
    }
}
