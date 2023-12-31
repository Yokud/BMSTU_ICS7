using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab_04
{
    public partial class Form2 : Form
    {
        public Form2(int type, List<(int, long)> dataCanon, List<(int, long)> dataParam, List<(int, long)> dataBresenham, List<(int, long)> dataMidPoint)
        {
            InitializeComponent();

            switch (type)
            {
                case 0:
                    chart1.Titles[0].Visible = true;
                    chart1.Titles[1].Visible = false;
                    chart1.ChartAreas[0].AxisX.Title = "Радиус";
                    chart1.ChartAreas[0].AxisY.Title = "Время (в тактах)";
                    break;

                case 1:
                    chart1.Titles[1].Visible = true;
                    chart1.Titles[0].Visible = false;
                    chart1.ChartAreas[0].AxisX.Title = "Большая полуось";
                    chart1.ChartAreas[0].AxisY.Title = "Время (в тактах)";
                    break;
            }

            foreach (var value in dataCanon)
                chart1.Series[0].Points.AddXY(value.Item1, value.Item2);

            foreach (var value in dataParam)
                chart1.Series[1].Points.AddXY(value.Item1, value.Item2);

            foreach (var value in dataBresenham)
                chart1.Series[2].Points.AddXY(value.Item1, value.Item2);

            foreach (var value in dataMidPoint)
                chart1.Series[3].Points.AddXY(value.Item1, value.Item2);
        }
    }
}
