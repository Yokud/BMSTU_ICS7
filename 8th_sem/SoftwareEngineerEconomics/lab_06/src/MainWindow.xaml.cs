using System;
using System.Windows;
using System.Windows.Controls;
using COCOMO.Attributes;
using LiveCharts;
using LiveCharts.Wpf;

namespace COCOMO_var1
{
	/// <summary>
	/// Interaction logic for MainWindow.xaml
	/// </summary>
	public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        public double c1, c2, p1, p2;
        private const double Money = 60; // ЗП кило рублей

        /// <summary>
        /// Режимы модели
        /// </summary>
        void SetConst(int kloc)
        {
            // Обычный
            if (kloc < 50)
            {
                c1 = 3.2;
                p1 = 1.05;
                c2 = 2.5;
                p2 = 0.38;
            }
            // Промежуточный
            else if (kloc <= 500)
            {
                c1 = 3;
                p1 = 1.12;
                c2 = 2.5;
                p2 = 0.35;
            }
            // Встроенный
            else
            {
                c1 = 2.8;
                p1 = 1.2;
                c2 = 2.5;
                p2 = 0.32;
            }
        }

		/// <summary>
		/// Результат учета 15 уточняющих факторов
		/// </summary>
		/// <returns>EAF</returns>
		private double CountEAF()
		{
            var kloc = int.Parse(KLOC.Text);

            var rely = Product.RELY(int.Parse(RELY.Text));
            var data = Product.DATA(int.Parse(DATA.Text));
            var cplx = Product.CPLX(int.Parse(CPLX.Text));

            var time = Hardware.TIME(int.Parse(TIME.Text));
            var stor = Hardware.STOR(int.Parse(STOR.Text));
            var virt = Hardware.VIRT(int.Parse(VIRT.Text));
            var turn = Hardware.TURN(int.Parse(TURN.Text));

            var acap = Personnel.ACAP(int.Parse(ACAP.Text));
            var aexp = Personnel.AEXP(int.Parse(AEXP.Text));
            var pcap = Personnel.PCAP(int.Parse(PCAP.Text));
            var vexp = Personnel.VEXP(int.Parse(VEXP.Text));
            var lexp = Personnel.LEXP(int.Parse(LEXP.Text));

            var modp = Project.MODP(int.Parse(MODP.Text));
            var tool = Project.TOOL(int.Parse(TOOL.Text));
            var sced = Project.SCED(int.Parse(SCED.Text));

            SetConst(kloc);

            return rely * data * cplx * time * stor * virt * turn * acap * aexp * pcap * vexp * lexp * modp * tool * sced;
        }
        
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            var kloc = int.Parse(KLOC.Text);

            var eaf = CountEAF();

            var work = c1 * eaf * Math.Pow(kloc, p1);
            var time = c2 * Math.Pow(work, p2);

            // Планирование и определение требований 
            var overWork = work * .08;
            var overTime = time * .36;
            var overPeople = Math.Ceiling(overWork / overTime);

            // Проектирование продукта 
            var projWork = work * .18;
            var projTime = time * .36;
            var proPeople = Math.Ceiling(projWork / projTime);

            // Детальное проектирование 
            var detProjWork = work * .25;
            var detProjTime = time * .18;
            var detProPeople = Math.Ceiling(detProjWork / detProjTime);

            // Кодирование и тестирование отдельных модулей
            var codeWork = work * .25;
            var codeTime = time * .18;
            var codePeople = Math.Ceiling(codeWork / codeTime);

            // Интеграция и тестирование
            var testWork = work * .31;
            var testTime = time * .28;
            var testPeople = Math.Ceiling(testWork / testTime);



            LiCyPlannig.Text = overWork.ToString("n2");
            LiCyPlannigTime.Text = overTime.ToString("n2");

            LiCyProjecting.Text = projWork.ToString("n2");
            LiCyProjectingTime.Text = time.ToString("n2");

            LiCyDetailedProjecting.Text = detProjWork.ToString("n2");
            LiCyDetailedProjectingTime.Text = detProjTime.ToString("n2");

            LiCyCoding.Text = codeWork.ToString("n2");
            LiCyCodingTime.Text = codeTime.ToString("n2");

            LiCyIntegration.Text = testWork.ToString("n2");
            LiCyIntegrationTime.Text = testTime.ToString("n2");

            LiCyTotal.Text = work.ToString("n2");
            LiCyTotalTime.Text = time.ToString("n2");

            LiCyAll.Text = (work + overWork).ToString("n2");
            LiCyAllTime.Text = (time + overTime).ToString("n2");

            // Декомпозиция работ по созданию ПО
            var decompose = new Decompose(work);

            DecAnalysisWork.Text = decompose.AnalysisWork.ToString("n2");
            DecProjectingWork.Text = decompose.ProjectingWork.ToString("n2");
            DecProgrammingWork.Text = decompose.ProgrammingWork.ToString("n2");
            DecTestingWork.Text = decompose.TestingWork.ToString("n2");
            DecVerificationWork.Text = decompose.VerificationWork.ToString("n2");
            DecChancelleryWork.Text = decompose.ChancelleryWork.ToString("n2");
            DecQaWork.Text = decompose.QaWork.ToString("n2");
            DecManualWork.Text = decompose.ManualWork.ToString("n2");
            DecTotalWork.Text = work.ToString("n2");

            // Заполняем деньги
            DecAnalysisMoney.Text = (decompose.AnalysisWork * Money).ToString("n2");
            DecProjectingMoney.Text = (decompose.ProjectingWork * Money).ToString("n2");
            DecProgrammingMoney.Text = (decompose.ProgrammingWork * Money).ToString("n2");
            DecTestingMoney.Text = (decompose.TestingWork * Money).ToString("n2");
            DecVerificationMoney.Text = (decompose.VerificationWork * Money).ToString("n2");
            DecChancelleryMoney.Text = (decompose.ChancelleryWork * Money).ToString("n2");
            DecQaMoney.Text = (decompose.QaWork * Money).ToString("n2");
            DecManualMoney.Text = (decompose.ManualWork * Money).ToString("n2");
            DecTotalMoney.Text = (work * Money).ToString("n2");


            // График
            var workersData = new ColumnSeries
            {
                Title = "1",
                Values = new ChartValues<double> { overPeople, proPeople, detProPeople, codePeople, testPeople }
            };

            var workersSeries = new SeriesCollection
            {
                workersData
            };

            Workres.Series = workersSeries;
        }

        // PreviewKeyDown is where you preview the key.
        // Do not put any logic here, instead use the
        // KeyDown event after setting IsInputKey to true.
        private void TextBox_PreviewKeyDown(object sender, System.Windows.Input.KeyEventArgs e)
        {
            var textbox = (TextBox)sender;

            switch (e.Key)
            {
                case System.Windows.Input.Key.Down:
                    textbox.Text = (int.Parse(textbox.Text) - 1).ToString();
                    break;
                case System.Windows.Input.Key.Up:
                    textbox.Text = (int.Parse(textbox.Text) + 1).ToString();
                    break;
            }
        }

        private void ButtonClicked(object sender, RoutedEventArgs e)
        {
            Graphs subWindow = new Graphs();
            subWindow.Show();
        }
    }
}
