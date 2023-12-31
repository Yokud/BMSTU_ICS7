using System;

namespace AppLib
{
    public static partial class App
    {
        static string key;

        static void PrintGreeting()
        {
            Console.WriteLine("Hello, world!");
        }

        static bool CheckKey(string serialKey)
        {
            return key == serialKey;
        }

        public static void Func(string serialKey)
        {
            if (CheckKey(serialKey))
                PrintGreeting();
            else
                Console.WriteLine("Try installer first");
        }
    }
}
