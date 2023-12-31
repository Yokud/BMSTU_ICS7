using MathNet.Numerics;
using MathNet.Numerics.Interpolation;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab_1
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
            List<double> mas, res;
            Modeller.CreateGraph(out mas, out res);

            chart1.Series[0].Points.AddXY(0, 0);
            var min = res.Min();
            for (int k = 0; k < res.Count; k++)
                chart1.Series[0].Points.AddXY(mas[k], res[k] - min);

            chart1.ChartAreas[0].AxisX.LabelStyle.Format = "{0:f1}";
            chart1.Show();
        }
    }
}
