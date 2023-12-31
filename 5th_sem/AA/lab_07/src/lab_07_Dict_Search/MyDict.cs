using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace lab_07_Dict_Search
{
    class MyDict
    {
        List<KeyValuePair<string, string>> dict;
        Dictionary<string, KeyValuePair<int, int>> clusters;
        static int temp = 0;

        public MyDict()
        {
            dict = new List<KeyValuePair<string, string>>();
            clusters = new();
        }

        public MyDict(string filepath) 
        {
            dict = new List<KeyValuePair<string, string>>();
            clusters = new();
            LoadDict(filepath);
        }

        public void LoadDict(string filepath)
        {
            if (!File.Exists(filepath))
                throw new Exception("file not found!");

            string[] data = File.ReadAllLines(filepath);

            foreach (string s in data)
            {
                int colon_index = s.IndexOf(':');

                if (colon_index != -1)
                {
                    string key = s.Substring(0, colon_index);
                    string value = s.Substring(colon_index + 2);

                    Add(key, value);
                }
            }
        }

        public int Count => dict.Count;
        public string[] Keys
        {
            get
            {
                string[] keys = new string[dict.Count];

                for (int i = 0; i < dict.Count; i++)
                    keys[i] = dict[i].Key;

                return keys;
            }
        }

        public void Add(string key, string value)
        {
            if (!ContainsKey(key))
                dict.Add(new KeyValuePair<string, string>(key, value));
        }

        public bool ContainsKey(string key)
        {
            foreach (var d in dict)
                if (d.Key == key)
                    return true;

            return false;
        }

        public void Clear()
        {
            dict.Clear();
        }

        public void PrintDict()
        {
            if (dict.Count == 0)
                return;

            foreach (var d in dict)
            {
                Console.WriteLine($"Key = {d.Key} | Value = {d.Value}");
            }
            Console.WriteLine($"Length: {dict.Count}");
        }

        public void Sort()
        {
            dict.Sort(new MyDictComp());
        }

        public string LinearSearch(string key, out int cmp_cnt)
        {
            cmp_cnt = 0;
            foreach (var d in dict)
            {
                cmp_cnt++;
                if (d.Key == key)
                    return d.Value;
            }

            return null;
        }

        public string BinarySearch(string key, int left, int right, out int cmp_cnt)
        {
            int cmp, mid;
            cmp_cnt = 0;
            
            while (left <= right)
            {
                mid = left + (right - left) / 2;

                cmp_cnt++;
                if ((cmp = key.CompareTo(this[mid].Key)) > 0)
                    left = mid + 1;
                else if (cmp < 0)
                    right = mid - 1;
                else
                    return dict[mid].Value;
            }

            return null;
        }

        public string ClusterSearch(string key, out int cmp_cnt)
        {
            string cluster_key = key[0].ToString();

            if (clusters.ContainsKey(cluster_key))
                return BinarySearch(key, clusters[cluster_key].Key, clusters[cluster_key].Value, out cmp_cnt);
            else
            {
                cmp_cnt = 0;
                return null;
            }
        }

        public KeyValuePair<string, string> this[int index]
        {
            get => dict[index];
            set => dict[index] = value;
        }

        public string this[string key]
        {
            get => LinearSearch(key, out temp);
        }

        public void Clusterize()
        {
            for (int i = 0; i < dict.Count; i++)
            {
                string key = dict[i].Key[0].ToString();
                if (clusters.ContainsKey(key))
                    clusters[key] = new KeyValuePair<int, int>(Math.Min(clusters[key].Key, i), Math.Max(clusters[key].Value, i));
                else
                    clusters.Add(key, new KeyValuePair<int, int>(i, i));
            }
        }

        class MyDictComp : IComparer<KeyValuePair<string, string>>
        {
            public int Compare(KeyValuePair<string, string> x, KeyValuePair<string, string> y)
            {
                return x.Key.CompareTo(y.Key);
            }
        }
    }
}
