using System;
using System.Windows.Forms;
using OxyPlot;


namespace Lab_03
{
    public partial class Form2 : Form
    {
        public Form2(PlotModel model)
        {
            InitializeComponent();

            plotView1.Model = model;
        }
    }
}
