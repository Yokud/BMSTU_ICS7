using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Lab_1
{
    public partial class Form1 : Form
    {
        public static double s_pTeor;

        public Form1()
        {
            InitializeComponent();

            textBox1.Text = "5";
            textBox2.Text = "20";
            textBox3.Text = "0";
            textBox4.Text = "1000";
            textBox9.Text = "0";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            double intensivityGen = double.Parse(textBox1.Text, System.Globalization.NumberStyles.Number);
            double rangeGen = double.Parse(textBox9.Text, System.Globalization.NumberStyles.Number);
            double intensivityProc = double.Parse(textBox2.Text, System.Globalization.NumberStyles.Number);
            double rangeProc = double.Parse(textBox3.Text, System.Globalization.NumberStyles.Number);
            double timeModeling = double.Parse(textBox4.Text, System.Globalization.NumberStyles.Number);

            double step = 0.1;

            RequestGenerator generator = new RequestGenerator(new RayleighGenerator(1 / intensivityGen));
            IGenerator OA = new UniformGenerator(1 / intensivityProc, rangeProc == 0 ? 0 : 1 / rangeProc);
            RequestProcessor processor = new RequestProcessor(OA);
            Modeller model = new Modeller(generator, processor);
            ModelingResults resultTb = model.RunTimeBasedModeling(step, timeModeling);

            s_pTeor = intensivityGen / intensivityProc;
            double p = s_pTeor;

            textBox8.Text = p > 0 && p < 1 ? string.Format("{0:g3}", p) : "---";
            textBox7.Text = string.Format("{0:g3}", resultTb.WorkloadFact);
            textBox6.Text = p > 0 && p < 1 ? string.Format("{0:g3}", p / (1 - p) / intensivityGen) : "---";
            textBox5.Text = string.Format("{0:g3}", resultTb.AvgTimeSMO);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            var form = new Form2();
            form.ShowDialog();
        }
    }
}
