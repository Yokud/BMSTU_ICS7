using Kolmogor;
using MathNet.Numerics.LinearAlgebra;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using OxyPlot.WindowsForms;
using OxyPlot.Series;
using OxyPlot;

namespace WindowsFormsApp1
{
    public partial class Form1 : Form
    {
        int states;

        public Form1()
        {
            InitializeComponent();

            ResultDataGridView.Columns.Add("ultProb", "Предельная вероятность");
            ResultDataGridView.Columns.Add("statTime", "Точка стабилизации системы");
            button2.Enabled = false;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            states = int.Parse(StatesValue.Text);

            if (states > KolmogorovMath.MaxStatesCount)
            {
                MessageBox.Show("States must be less or equal " + KolmogorovMath.MaxStatesCount);
                MainDataGridView.Rows.Clear();
                MainDataGridView.Columns.Clear();
                return;
            }

            MainDataGridView.Rows.Clear();
            MainDataGridView.Columns.Clear();

            for (int i = 0; i < states; i++)
            {
                MainDataGridView.Columns.Add("P" + i, i.ToString());
                MainDataGridView.Rows.Add();
            }

            button2.Enabled = true;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Matrix<double> matrix = Matrix<double>.Build.Dense(states, states);

            for (int i = 0; i < states; i++)
            {
                for (int j = 0; j < states; j++)
                    matrix[i, j] = double.Parse(MainDataGridView.Rows[i].Cells[j].Value.ToString(), CultureInfo.InvariantCulture);
            }

            var ultProbs = KolmogorovMath.GetUltimatePropabilities(matrix);
            var startProbs = Vector<double>.Build.Dense(Enumerable.Repeat(1.0 / states, states).ToArray());
            var stats = KolmogorovMath.GetStabilizationTimes(matrix, startProbs, ultProbs.EnumerateColumns().First()).ToArray();

            ResultDataGridView.Rows.Clear();

            for (int i = 0; i < states; i++)
                ResultDataGridView.Rows.Add(ultProbs[i, 0], stats[i]);

            var lst = KolmogorovMath.PropabilityOverTime(matrix, startProbs, 5).ToArray();
            var model = new PlotModel();

            for (int i = 0; i < states; i++)
            { 
                var ser = new ScatterSeries();

                foreach (var p in lst[i])
                    ser.Points.Add(new ScatterPoint(p.X, p.Y, 0.8));

                model.Series.Add(ser);
            }

            var serP = new ScatterSeries();

            for (int i = 0; i < states; i++)
                serP.Points.Add(new ScatterPoint(stats[i], ultProbs[i, 0], 4));

            model.Series.Add(serP);

            var form = new Form2();
            form.plot.Model = model;
            form.Show();
        }
    }
}
