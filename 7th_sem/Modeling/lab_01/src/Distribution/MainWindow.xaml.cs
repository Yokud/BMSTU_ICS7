using ScottPlot;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Distribution
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        IDistribution distr;
        const double step = 1e-3;

        public MainWindow()
        {
            InitializeComponent();

            CDFPlot.Plot.Title("Функция распределения");
            PMFPlot.Plot.Title("Функция плотности распределения");
        }

        private void DistributionChoise_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            if (FirstParam is null || SecondParam is null)
                return;

            switch (DistributionChoise.SelectedIndex)
            {
                case 0:
                    SecondParam.IsEnabled = true;
                    SecondParam.Visibility = Visibility.Visible;
                    FirstParamText.Text = "a = ";
                    FirstParamValue.Text = "";

                    break;

                case 1:
                    SecondParam.IsEnabled = false;
                    SecondParam.Visibility = Visibility.Hidden;
                    FirstParamText.Text = "λ = ";
                    FirstParamValue.Text = "";

                    break;
            }
        }

        private void DrawButton_Click(object sender, RoutedEventArgs e)
        {
            switch (DistributionChoise.SelectedIndex)
            {
                case 0:
                    try
                    {
                        double a = double.Parse(FirstParamValue.Text, System.Globalization.NumberStyles.AllowDecimalPoint | System.Globalization.NumberStyles.AllowLeadingSign);
                        double b = double.Parse(SecondParamValue.Text, System.Globalization.NumberStyles.AllowDecimalPoint | System.Globalization.NumberStyles.AllowLeadingSign);
                        distr = new UniformDistribution(a, b);

                        int count = (int)(((b + 1) - (a - 1)) / step);
                        double[] xs = new double[count];
                        double[] cdf = new double[count];
                        double[] pmf = new double[count];

                        double xstart = a - 1;
                        for (int i = 0; i < count; i++)
                        {
                            xs[i] = xstart;
                            cdf[i] = distr.CDF(xs[i]);
                            pmf[i] = distr.PMF(xs[i]);
                            xstart += step;
                        }

                        CDFPlot.Plot.Clear();
                        PMFPlot.Plot.Clear();
                        CDFPlot.Plot.AddScatterLines(xs, cdf);
                        PMFPlot.Plot.AddScatterLines(xs, pmf);
                        CDFPlot.Refresh();
                        PMFPlot.Refresh();
                    }
                    catch (Exception exc)
                    {
                        MessageBox.Show(exc.Message);
                    }

                    break;

                case 1:
                    try
                    {
                        double lambda = double.Parse(FirstParamValue.Text, System.Globalization.NumberStyles.AllowDecimalPoint);
                        distr = new PoissonDistribution(lambda);

                        int count = lambda < 10 ? 20 : (int)(lambda * 2.5);
                        double[] xs = new double[count];
                        double[] cdf = new double[count];
                        double[] pmf = new double[count];

                        for (int i = 0; i < count; i++)
                        {
                            xs[i] = i;
                            cdf[i] = distr.CDF(i);
                            pmf[i] = distr.PMF(i);
                        }

                        CDFPlot.Plot.Clear();
                        PMFPlot.Plot.Clear();
                        CDFPlot.Plot.AddScatterLines(xs, cdf);
                        PMFPlot.Plot.AddScatterLines(xs, pmf);
                        CDFPlot.Refresh();
                        PMFPlot.Refresh();
                    }
                    catch (Exception exc)
                    {
                        MessageBox.Show(exc.Message);
                    }

                    break;
            }
        }
    }
}
