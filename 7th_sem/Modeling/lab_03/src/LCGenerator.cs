using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RandomNumbers
{
    internal class LCGenerator
    {
        long curElem = 1;
        long a, c, m;

        public LCGenerator(long a, long c, long m) 
        {
            this.a = a;
            this.c = c;
            this.m = m;
        }

        public long Seed
        {
            get => curElem;
            set => curElem = value;
        }

        public IEnumerable<int> GetRandomSequence(int count, int requiredDigits)
        {
            List<int> res = new List<int>();

            int requiredDigitsDivider = (int)Math.Pow(10, requiredDigits);
            int minAppendValue = requiredDigitsDivider / 10 - 1;

            for (int addedElements = 0; addedElements < count; addedElements++)
            {
                curElem = (curElem * a + c) % m;

                long elem = curElem % requiredDigitsDivider;
                if (elem >= minAppendValue)
                    res.Add((int)elem);
                else
                    addedElements--;
            }

            return res;
        }
    }
}
