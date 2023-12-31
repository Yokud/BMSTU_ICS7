using System;
using System.Windows;
using System.Windows.Media;
using LiveCharts;
using LiveCharts;
using LiveCharts.Wpf;
using COCOMO.Attributes;
using System.Collections.Generic;

namespace COCOMO_var1
{
    /// <summary>
    /// Логика взаимодействия для Graphs.xaml
    /// </summary>
    public partial class Graphs : Window
    {
        // Данные для графиков
        public SeriesCollection NormalWork { get; set; }
        public SeriesCollection NormalTime { get; set; }

        public SeriesCollection InterWork { get; set; }
        public SeriesCollection InterTime { get; set; }

        public SeriesCollection InbuiltWork { get; set; }
        public SeriesCollection InbuiltTime { get; set; }

        // Данные для подписей графиков
        public string[] SeriesLabels = new[] { "ACAP", "AEXP", "PCAP", "LEXP" };
        public string[] LevelLabels { get; set; }
        public Func<double, string> YFormatter { get; set; }


        // Исследуем влияние ACAP, AEXP, PCAP, LEXP
        private readonly int kloc = 100;
        private double c1, c2, p1, p2;

        public Graphs()
        {
            InitializeComponent();

            LevelLabels = new[] { "Очень низкий", "Низкий", "Номинальный", "Высокий", "Очень высокий" };
            YFormatter = value => value.ToString();

            NormalWork = GetDefaultGraph();
            NormalTime = GetDefaultGraph();
            InbuiltWork = GetDefaultGraph();
            InbuiltTime = GetDefaultGraph();
            InterWork = GetDefaultGraph();
            InterTime = GetDefaultGraph();

            FillGraph(Mode.Normal, NormalWork, NormalTime);
            FillGraph(Mode.Inbuilt, InbuiltWork, InbuiltTime);
            FillGraph(Mode.Inner, InterWork, InterTime);

            DataContext = this;
        }

        private void FillGraph(Mode mode, SeriesCollection work, SeriesCollection time)
        {
            SetConst(mode);

            for (int paramN = 0; paramN < 4; paramN++)
            {
                var levels = new int[4]; // acap, aexp, pcap, lexp

                for (int value = -2; value <= 1; value++) // от очень низкого до высокого
                {
                    levels[paramN] = value; // Варьируем значение текущего параметра

                    double EAF =
                        Personnel.ACAP(levels[0]) *
                        Personnel.AEXP(levels[1]) *
                        Personnel.PCAP(levels[2]) *
                        Personnel.LEXP(levels[3]);

                    var workVal = c1 * EAF * Math.Pow(kloc, p1);
                    var timeVal = c2 * Math.Pow(workVal, p2);

                    work[paramN].Values.Add(workVal);
                    time[paramN].Values.Add(timeVal);
                }
            }
        }

        void SetConst(Mode mode)
        {
            switch (mode)
			{
                case Mode.Normal:
                    c1 = 3.2;
                    p1 = 1.05;
                    c2 = 2.5;
                    p2 = 0.38;
                    break;

                case Mode.Inner:
                    c1 = 3;
                    p1 = 1.12;
                    c2 = 2.5;
                    p2 = 0.35;
                    break;

                case Mode.Inbuilt:
                    c1 = 2.8;
                    p1 = 1.2;
                    c2 = 2.5;
                    p2 = 0.32;
                    break;
            }

        }

        private SeriesCollection GetDefaultGraph()
        {
            return new SeriesCollection
                {
                    new LineSeries
                    {
                        Title = SeriesLabels[0],
                        Values = new ChartValues<double>(),
                    },
                    new LineSeries
                    {
                        Title = SeriesLabels[1],
                        Values = new ChartValues<double>(),
                    },
                    new LineSeries
                    {
                        Title = SeriesLabels[2],
                        Values = new ChartValues<double>(),
                        PointGeometry = DefaultGeometries.Square,
                    },
                    new LineSeries
                    {
                        Title = SeriesLabels[3],
                        Values = new ChartValues<double>()
                    }
                };
        }
    }

    enum Mode
	{
        Normal, // обычный
        Inbuilt,// встроенный
        Inner   // промежуточный
	}
}


