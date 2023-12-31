using System;
using System.Diagnostics;

namespace SortingAlgs
{
    class Program
    {
        delegate void SortFunc(int[] arr);

        static void Swap(ref int a, ref int b)
        {
            int tmp = a;
            a = b;
            b = tmp;
        }
        static void BubleFlagSort(int[] arr)
        {
            bool flag;

            for (int i = 1; i < arr.Length; i++)
            {
                flag = false;

                for (int j = 0; j < arr.Length - i; j++)
                {
                    if (arr[j] > arr[j + 1])
                    {
                        Swap(ref arr[j], ref arr[j + 1]);
                        flag = true;
                    }
                }

                if (!flag)
                    break;
            }
        }

        static void SelectionSort(int[] arr)
        {
            int min;

            for (int i = 0; i < arr.Length - 1; i++)
            {
                min = i;
                for (int j = i + 1; j < arr.Length; j++)
                    if (arr[j] < arr[min])
                        min = j;

                if (min != i)
                    Swap(ref arr[i], ref arr[min]);
            }
        }

        static int _Partition(int[] arr, int start, int end)
        {
            int p = arr[(end - start) / 2 + start];
            int i = start - 1;
            int j = end + 1;

            while (true)
            {
                do i++; while (arr[i] < p);
                do j--; while (arr[j] > p);

                if (i >= j) return j;

                Swap(ref arr[i], ref arr[j]);
            }
        }

        static void _QuickSort(int[] arr, int start, int end)
        {
            int i;
            if (start < end)
            {
                i = _Partition(arr, start, end);

                _QuickSort(arr, start, i);
                _QuickSort(arr, i + 1, end);
            }
        }

        static void QuickSort(int[] array)
        {
            _QuickSort(array, 0, array.Length - 1);
        }

        static int[] GenOrderedArr(int n)
        {
            if (n <= 0)
                throw new Exception("Bad length!");

            int[] arr = new int[n];

            for (int i = 0; i < n; i++)
                arr[i] = i;

            return arr;
        }

        static int[] GenReversedArr(int n)
        {
            if (n <= 0)
                throw new Exception("Bad length!");

            int[] arr = new int[n];

            for (int i = 0; i < n; i++)
                arr[i] = n - i - 1;

            return arr;
        }

        static int[] GenRandomArr(int n)
        {
            if (n <= 0)
                throw new Exception("Bad length!");

            int[] arr = new int[n];
            Random rd = new Random();

            for (int i = 0; i < n; i++)
                arr[i] = rd.Next(n);

            return arr;
        }

        static double CheckTime(SortFunc sort, int[] arr, int n)
        {
            Stopwatch sw = new Stopwatch();

            for (int i = 0; i < n; i++)
            {
                var temp = (int[])arr.Clone();

                sw.Start();
                sort(temp);
                sw.Stop();
            }

            return sw.Elapsed.TotalMilliseconds / n * 1000;
        }

        static void Main(string[] args)
        {
            int[] example = { 3, 5, -1, 2, -10, -5, 7, 6, 9, 10 };

            Console.Write("Unsorted: ");
            foreach (int n in example)
                Console.Write(n + " ");
            Console.WriteLine();

            int[] example1 = (int[])example.Clone();
            int[] example2 = (int[])example.Clone();
            int[] example3 = (int[])example.Clone();

            BubleFlagSort(example1);
            SelectionSort(example2);
            QuickSort(example3);

            Console.Write("Sorted (Buble): ");
            foreach (int n in example1)
                Console.Write(n + " ");
            Console.WriteLine();
            Console.Write("Sorted (Selection): ");
            foreach (int n in example2)
                Console.Write(n + " ");
            Console.WriteLine();
            Console.Write("Sorted (Quick): ");
            foreach (int n in example3)
                Console.Write(n + " ");
            Console.WriteLine("\n");


            //Console.Write("Buble\nOrdered:  ");
            //for (int i = 1; i < 11; i++)
            //    Console.Write(string.Format("{0,8:f2} ", CheckTime(BubleFlagSort, GenOrderedArr(100 * i), 1000)));
            //Console.WriteLine();
            //Console.Write("Reversed: ");
            //for (int i = 1; i < 11; i++)
            //    Console.Write(string.Format("{0,8:f2} ", CheckTime(BubleFlagSort, GenReversedArr(100 * i), 1000)));
            //Console.WriteLine();
            //Console.Write("Random:   ");
            //for (int i = 1; i < 11; i++)
            //    Console.Write(string.Format("{0,8:f2} ", CheckTime(BubleFlagSort, GenRandomArr(100 * i), 1000)));
            //Console.WriteLine();

            //Console.Write("\nSelection\nOrdered:  ");
            //for (int i = 1; i < 11; i++)
            //    Console.Write(string.Format("{0,8:f2} ", CheckTime(SelectionSort, GenOrderedArr(100 * i), 1000)));
            //Console.WriteLine();
            //Console.Write("Reversed: ");
            //for (int i = 1; i < 11; i++)
            //    Console.Write(string.Format("{0,8:f2} ", CheckTime(SelectionSort, GenReversedArr(100 * i), 1000)));
            //Console.WriteLine();
            //Console.Write("Random:   ");
            //for (int i = 1; i < 11; i++)
            //    Console.Write(string.Format("{0,8:f2} ", CheckTime(SelectionSort, GenRandomArr(100 * i), 1000)));
            //Console.WriteLine();

            //Console.Write("\nQuick\nOrdered:  ");
            //for (int i = 1; i < 11; i++)
            //    Console.Write(string.Format("{0,8:f2} ", CheckTime(QuickSort, GenOrderedArr(100 * i), 1000)));
            //Console.WriteLine();
            //Console.Write("Reversed: ");
            //for (int i = 1; i < 11; i++)
            //    Console.Write(string.Format("{0,8:f2} ", CheckTime(QuickSort, GenReversedArr(100 * i), 1000)));
            //Console.WriteLine();
            //Console.Write("Random:   ");
            //for (int i = 1; i < 11; i++)
            //    Console.Write(string.Format("{0,8:f2} ", CheckTime(QuickSort, GenRandomArr(100 * i), 1000)));
            //Console.WriteLine();
        }
    }
}
