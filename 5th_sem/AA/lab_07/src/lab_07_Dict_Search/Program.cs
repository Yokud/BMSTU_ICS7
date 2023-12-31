using System;
using System.Collections.Generic;
using System.IO;

namespace lab_07_Dict_Search
{
    class Program
    {
        static string path = @"D:\Repos\GitHub\5_sem_SE\AA\lab_07\src\src_data\";

        static void Main(string[] args)
        {
            MyDict temp = new MyDict(path + "data.txt");
            int cmps;

            using (StreamWriter f = new StreamWriter(path + "lin_search.txt"))
            {
                int i = 0;
                foreach (var key in temp.Keys)
                {
                    temp.LinearSearch(key, out cmps);
                    f.WriteLine("{0} {1}", i, cmps);
                    i++;
                }
            }

            using (StreamWriter f = new StreamWriter(path + "bin_search.txt"))
            {
                temp.Sort();

                int i = 0;
                foreach (var key in temp.Keys)
                {
                    temp.BinarySearch(key, 0, temp.Count, out cmps);
                    f.WriteLine("{0} {1}", i, cmps);
                    i++;
                }
            }

            using (StreamWriter f = new StreamWriter(path + "clust_search.txt"))
            {
                temp.Clusterize();

                int i = 0;
                foreach (var key in temp.Keys)
                {
                    temp.ClusterSearch(key, out cmps);
                    f.WriteLine("{0} {1}", i, cmps);
                    i++;
                }
            }
        }
    }
}
