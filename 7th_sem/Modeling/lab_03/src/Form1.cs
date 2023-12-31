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
    public partial class Form1 : Form
    {
        const int count = 100;
        const long a = 1103515245, c = 12345, m = 4294967296;

        public Form1()
        {
            InitializeComponent();

            dataGridView1.Columns.Add("1", "1");
            dataGridView1.Columns.Add("2", "2");
            dataGridView1.Columns.Add("3", "3");

            dataGridView2.Columns.Add("1", "1");
            dataGridView2.Columns.Add("2", "2");
            dataGridView2.Columns.Add("3", "3");

            dataGridView3.Columns.Add("1", "1");
            dataGridView3.Columns.Add("2", "2");
            dataGridView3.Columns.Add("3", "3");

            dataGridView4.Columns.Add("1", "1");
            dataGridView4.Columns.Add("2", "2");
            dataGridView4.Columns.Add("3", "3");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Form2 form = new Form2();
            form.ShowDialog();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            var tableRes1 = new TableGenerator().GetRandomSequence(count, 1).ToArray();
            var tableRes2 = new TableGenerator().GetRandomSequence(count, 2).ToArray();
            var tableRes3 = new TableGenerator().GetRandomSequence(count, 3).ToArray();

            var algRes1 = new LCGenerator(a, c, m).GetRandomSequence(count, 1).ToArray();
            var algRes2 = new LCGenerator(a, c, m).GetRandomSequence(count, 2).ToArray();
            var algRes3 = new LCGenerator(a, c, m).GetRandomSequence(count, 3).ToArray();

            for (int i = 0; i < count; i++) 
            {
                dataGridView1.Rows.Add(algRes1[i], algRes2[i], algRes3[i]);
                dataGridView2.Rows.Add(tableRes1[i], tableRes2[i], tableRes3[i]);
            }

            var tableP1 = Criteria.TestCriteria(tableRes1);
            var tableP2 = Criteria.TestCriteria(tableRes2);
            var tableP3 = Criteria.TestCriteria(tableRes3);

            var algP1 = Criteria.TestCriteria(algRes1);
            var algP2 = Criteria.TestCriteria(algRes2);
            var algP3 = Criteria.TestCriteria(algRes3);

            dataGridView3.Rows.Add(algP1, algP2, algP3);
            dataGridView4.Rows.Add(tableP1, tableP2, tableP3);

            dataGridView1.AllowUserToAddRows = false;
            dataGridView2.AllowUserToAddRows = false;
            dataGridView3.AllowUserToAddRows = false;
            dataGridView4.AllowUserToAddRows = false;
        }
    }
}
