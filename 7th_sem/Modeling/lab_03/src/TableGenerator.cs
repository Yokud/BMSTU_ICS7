using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace RandomNumbers
{
    internal class TableGenerator
    {
        const string filename = "D:\\Repos\\GitHub\\7_sem_SE\\Modeling\\lab_03\\src\\table.txt";
        List<int> numbers = new List<int>();

        public TableGenerator() 
        {
            using (StreamReader reader = new StreamReader(new FileStream(filename, FileMode.Open)))
            {
                while (!reader.EndOfStream)
                    numbers.Add(int.Parse(reader.ReadLine()));
            }
        }

        public IEnumerable<int> GetRandomSequence(int count, int requiredDigits)
        {
            List<int> res = new List<int>();

            int requiredDigitsDivider = (int)Math.Pow(10, requiredDigits);
            int minAppendValue = requiredDigitsDivider / 10 - 1;
            int addedElements = 0;

            for (int i = 0 ; i < numbers.Count && addedElements < count; i++) 
            {
                int elem = numbers[i] % requiredDigitsDivider;
                if (elem >= minAppendValue)
                {
                    res.Add(elem);
                    addedElements++;
                }  
                else
                    addedElements--;
            }

            return res;
        }
    }
}
