using System;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System.Diagnostics;

namespace Lab_05
{
    public partial class Form1 : Form
    {
        Bitmap map;
        int data_rows_count;
        Point polygon_start_p;
        public Form1()
        {
            InitializeComponent();

            map = new Bitmap(Canvas.Width, Canvas.Height);
            data_rows_count = 0;
            polygon_start_p = Point.Empty;
        }

        public void UpdateCanvas()
        {
            Canvas.Image = map;
            Canvas.Refresh();
        }

        public static bool BoxIsVoid(DataGridViewRow rw, int i)
        {
            return Convert.ToString(rw.Cells[i].Value) == string.Empty;
        }

        private void buttonAsk_Click(object sender, EventArgs e)
        {
            string info = "Данная программа позволяет строить произвольные многоугольники и заполнять их определённым цветом с помощью алгоритма " +
                "заполнения со списком рёбер и флагом.\n\tИмеется возможность задать цвет рёбер и фона. Все величины " +
                "задаются целыми числами. Используется экранная система координат. Сам экран имеет размер 825 на 740 пикселей.";

            MessageBox.Show(info, "Информация о программе", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void buttonClearCanvas_Click(object sender, EventArgs e)
        {
            Graphics g = Graphics.FromImage(map);
            g.Clear(Canvas.BackColor);
            Canvas.Refresh();
        }

        private void buttonBG_Click(object sender, EventArgs e)
        {
            if (Canvas.BackColor.ToArgb() != bgColorBox.BackColor.ToArgb())
                Canvas.BackColor = bgColorBox.BackColor;
        }

        private void bgColorBox_Click(object sender, EventArgs e)
        {
            if (bgColorDialog.ShowDialog() == DialogResult.OK)
                bgColorBox.BackColor = bgColorDialog.Color;
        }

        private void fillingColorBox_Click(object sender, EventArgs e)
        {
            if (fillingColorDialog.ShowDialog() == DialogResult.OK)
                fillingColorBox.BackColor = fillingColorDialog.Color;
        }

        private void borderColorBox_Click(object sender, EventArgs e)
        {
            if (borderColorDialog.ShowDialog() == DialogResult.OK)
                borderColorBox.BackColor = borderColorDialog.Color;
        }

        private void buttonDraw_Click(object sender, EventArgs e)
        {
            Lines lines = ReadFromGrid(borderGrid);

            Graphics g = Graphics.FromImage(map);
            g.Clear(Canvas.BackColor);
            Canvas.Refresh();

            lines.DrawLinesSpec(map, borderColorBox.BackColor);
            UpdateCanvas();

            long time = Filling(map, lines, fillingColorBox.BackColor, borderColorBox.BackColor, bgColorBox.BackColor, checkSleep.Checked);
            UpdateCanvas();

            MessageBox.Show(string.Format("Время работы алгоритма: {0} мс", time), "Замер времени");
        }

        long Filling(Bitmap map, Lines borders, Color filling_color, Color border_color, Color bg_color, bool is_sleep)
        {
            if (borders == null || borders.IsVoid())
                return 0;

            if (is_sleep)
                Thread.Sleep(1500);

            borders.MinMaxValues(out int x_min, out int x_max, out int y_min, out int y_max);
            bool flag;
            int border_color_argb = border_color.ToArgb();

            var sw = Stopwatch.StartNew();

            for (int y = y_max; y >= y_min; y--)
            {
                flag = false;

                for (int x = x_min; x <= x_max; x++)
                {
                    if (map.GetPixel(x, y).ToArgb() == border_color_argb)
                        flag = !flag;

                    if (flag)
                        map.SetPixel(x, y, filling_color);
                    else
                        map.SetPixel(x, y, bg_color);
                }

                sw.Stop();
                if (is_sleep)
                {
                    UpdateCanvas();
                    Thread.Sleep(15);
                }
                sw.Start();
            }

            borders.DrawLines(map, filling_color, false);

            return sw.ElapsedMilliseconds;
        }

        public static Lines ReadFromGrid(DataGridView data)
        {
            Lines lines = new Lines();

            foreach (DataGridViewRow row in data.Rows)
                try
                {
                    if (!row.IsNewRow)
                        if (BoxIsVoid(row, 2) || BoxIsVoid(row, 3))
                            lines.AddLine(new Line(int.Parse(row.Cells[0].Value.ToString()), int.Parse(row.Cells[1].Value.ToString()),
                                                   int.Parse(row.Cells[0].Value.ToString()), int.Parse(row.Cells[1].Value.ToString())));
                        else
                            lines.AddLine(new Line(int.Parse(row.Cells[0].Value.ToString()), int.Parse(row.Cells[1].Value.ToString()),
                                                   int.Parse(row.Cells[2].Value.ToString()), int.Parse(row.Cells[3].Value.ToString())));
                }
                catch (Exception Ee)
                {
                    MessageBox.Show(Ee.ToString(), "Ошибка чтения таблицы");
                    break;
                }

            return lines;
        }

        private void buttonClearList_Click(object sender, EventArgs e)
        {
            borderGrid.Rows.Clear();
            borderGrid.Refresh();
            data_rows_count = 0;
        }

        private void Canvas_MouseClick(object sender, MouseEventArgs e)
        {
            if (BoxIsVoid(borderGrid.Rows[data_rows_count], 0) && BoxIsVoid(borderGrid.Rows[data_rows_count], 1) &&
                BoxIsVoid(borderGrid.Rows[data_rows_count], 2) && BoxIsVoid(borderGrid.Rows[data_rows_count], 3))
            {
                borderGrid.Rows.Add(e.X, e.Y);

                if (polygon_start_p.IsEmpty)
                    polygon_start_p = new Point(e.X, e.Y);
            }
            else
            {
                if (Standart.Checked)
                {
                    borderGrid.Rows[data_rows_count].Cells[2].Value = e.X;
                    borderGrid.Rows[data_rows_count].Cells[3].Value = e.Y;

                    borderGrid.Rows.Add(e.X, e.Y);
                }
                else if (Horizontal.Checked)
                {
                    borderGrid.Rows[data_rows_count].Cells[2].Value = e.X;
                    borderGrid.Rows[data_rows_count].Cells[3].Value = borderGrid.Rows[data_rows_count].Cells[1].Value;

                    borderGrid.Rows.Add(e.X, borderGrid.Rows[data_rows_count].Cells[1].Value);
                }
                else if (Vertical.Checked)
                {
                    borderGrid.Rows[data_rows_count].Cells[2].Value = borderGrid.Rows[data_rows_count].Cells[0].Value;
                    borderGrid.Rows[data_rows_count].Cells[3].Value = e.Y;

                    borderGrid.Rows.Add(borderGrid.Rows[data_rows_count].Cells[0].Value, e.Y);
                }
                data_rows_count++;

                Lines lines = ReadFromGrid(borderGrid);

                lines.DrawLines(map, borderColorBox.BackColor, true);
            }

            UpdateCanvas();
        }

        private void Canvas_MouseMove(object sender, MouseEventArgs e)
        {
            if (data_rows_count < borderGrid.RowCount && !BoxIsVoid(borderGrid.Rows[data_rows_count], 0) && !BoxIsVoid(borderGrid.Rows[data_rows_count], 1) &&
                BoxIsVoid(borderGrid.Rows[data_rows_count], 2) && BoxIsVoid(borderGrid.Rows[data_rows_count], 3))
            {
                Line temp = null;
                
                if (Standart.Checked)
                    temp = new Line(int.Parse(borderGrid.Rows[data_rows_count].Cells[0].Value.ToString()),
                                         int.Parse(borderGrid.Rows[data_rows_count].Cells[1].Value.ToString()),
                                         e.X, e.Y);
                else if (Horizontal.Checked)
                    temp = new Line(int.Parse(borderGrid.Rows[data_rows_count].Cells[0].Value.ToString()),
                                    int.Parse(borderGrid.Rows[data_rows_count].Cells[1].Value.ToString()),
                                    e.X, int.Parse(borderGrid.Rows[data_rows_count].Cells[1].Value.ToString()));
                else if (Vertical.Checked)
                    temp = new Line(int.Parse(borderGrid.Rows[data_rows_count].Cells[0].Value.ToString()),
                                    int.Parse(borderGrid.Rows[data_rows_count].Cells[1].Value.ToString()),
                                    int.Parse(borderGrid.Rows[data_rows_count].Cells[0].Value.ToString()), e.Y);

                temp.Draw(map, borderColorBox.BackColor);

                Lines lines = ReadFromGrid(borderGrid);

                lines.DrawLines(map, borderColorBox.BackColor, false);
                UpdateCanvas();
                temp.Draw(map, bgColorBox.BackColor);
            }
        }

        private void buttonUpdateCanvas_Click(object sender, EventArgs e)
        {
            Lines lines = ReadFromGrid(borderGrid);

            Graphics g = Graphics.FromImage(map);
            g.Clear(Canvas.BackColor);
            Canvas.Refresh();
            data_rows_count = borderGrid.RowCount - 1;

            lines.DrawLines(map, borderColorBox.BackColor, true);
            UpdateCanvas();
        }

        private void buttonClosePol_Click(object sender, EventArgs e)
        {
            if (polygon_start_p.IsEmpty)
                return;

            borderGrid.Rows[data_rows_count].Cells[2].Value = polygon_start_p.X;
            borderGrid.Rows[data_rows_count].Cells[3].Value = polygon_start_p.Y;

            Line temp = new Line(new Point(int.Parse(borderGrid.Rows[data_rows_count].Cells[0].Value.ToString()),
                                           int.Parse(borderGrid.Rows[data_rows_count].Cells[1].Value.ToString())), polygon_start_p);
            temp.Draw(map, borderColorBox.BackColor);
            data_rows_count++;

            using (Graphics g = Graphics.FromImage(map))
            {
                g.TextRenderingHint = System.Drawing.Text.TextRenderingHint.AntiAlias;

                TextRenderer.DrawText(g, "(" + polygon_start_p.X.ToString() + ", " + polygon_start_p.Y.ToString() + ")",
                                      new Font("Arial", 8), polygon_start_p, Color.Black);
            }

            polygon_start_p = Point.Empty;

            UpdateCanvas();
        }
    }
}
