using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace RandomNumbers
{
    internal static class Criteria
    {
        public static double TestCriteria(IEnumerable<int> sequence)
        {
            List<int> s = new List<int>();

            for (int i = 0; i < sequence.Count() - 1; i++) 
            {
                var elem = sequence.ElementAt(i + 1) - sequence.ElementAt(i);
                
                if (!s.Contains(elem))
                    s.Add(elem);
            }

            int sCount = s.Count();

            int[] references = new int[sCount];

            for (int i = 0; i < sCount; i++)
                for (int j = 0; j < sequence.Count() - 1; j++)
                {
                    var elem = sequence.ElementAt(j + 1) - sequence.ElementAt(j);

                    if (s[i] == elem)
                        references[i] += 1;
                }

            double res = references.Select(x => x / (double)(sequence.Count() - 1)).Sum() / sCount; ;
            return res;
        }
    }
}
