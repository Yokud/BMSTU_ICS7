using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace RandomNumbers
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();

            dataGridView1.Columns.Add("data", "Данные");
            for (int i = 0; i < 10; i++) 
            {
                dataGridView1.Rows.Add();
            }

            dataGridView1.AllowUserToAddRows= false;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int[] data = new int[10];

            for (int i = 0; i < 10; i++)
            {
                data[i] = int.Parse((string)dataGridView1.Rows[i].Cells[0].Value);
            }

            double p = Criteria.TestCriteria(data);
            label2.Text = p.ToString();
        }
    }
}
