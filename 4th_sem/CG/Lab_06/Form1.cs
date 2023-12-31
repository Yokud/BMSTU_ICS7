using System;
using System.Collections.Generic;
using System.Drawing;
using System.Threading;
using System.Windows.Forms;
using System.Diagnostics;

namespace Lab_06
{
    public partial class Form1 : Form
    {
        Bitmap map;
        int data_rows_count;
        Point fill_pixel;
        Point polygon_start_p;
        public Form1()
        {
            InitializeComponent();

            map = new Bitmap(Canvas.Width, Canvas.Height);
            data_rows_count = 0;
            fill_pixel = Point.Empty;
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
                "построчного затравочного заполнения.\n\tИмеется возможность задать цвет рёбер и фона. Все величины " +
                "задаются целыми числами. Используется экранная система координат. Сам экран имеет размер 825 на 740 пикселей.";

            MessageBox.Show(info, "Информация о программе", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void buttonClearCanvas_Click(object sender, EventArgs e)
        {
            using (Graphics g = Graphics.FromImage(map))
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

            using (Graphics g = Graphics.FromImage(map))
                g.Clear(Canvas.BackColor);

            lines.DrawLines(map, borderColorBox.BackColor, false);
            map.SetPixel(fill_pixel.X, fill_pixel.Y, fillingColorBox.BackColor);
            UpdateCanvas();

            long time = Filling(map, lines, fill_pixel, fillingColorBox.BackColor, borderColorBox.BackColor, checkSleep.Checked);
            UpdateCanvas();

            if (time != 0)
                MessageBox.Show(string.Format("Время работы алгоритма: {0} мс", time), "Замер времени");
        }

        long Filling(Bitmap map, Lines borders, Point fill_pixel, Color filling_color, Color border_color, bool is_sleep)
        {
            if (borders == null || borders.IsVoid() || fill_pixel == Point.Empty)
            {
                MessageBox.Show("Не введена граница затравки", "Ошибка затравки");
                return 0;
            }

            if (is_sleep)
                Thread.Sleep(1500);

            int border_color_argb = border_color.ToArgb();
            int filling_color_argb = filling_color.ToArgb();

            var sw = Stopwatch.StartNew();

            Stack<Point> fill_points = new Stack<Point>();

            fill_points.Push(fill_pixel);

            try
            {
                while (fill_points.Count != 0)
                {
                    Point p = fill_points.Pop();
                    map.SetPixel(p.X, p.Y, filling_color);

                    Point tmp = p;
                    p.X++;

                    int xr, xl;
                    while (map.GetPixel(p.X, p.Y).ToArgb() != border_color_argb)
                    {
                        map.SetPixel(p.X, p.Y, filling_color);
                        p.X++;
                    }
                    xr = p.X - 1;

                    p = tmp;
                    p.X--;
                    while (map.GetPixel(p.X, p.Y).ToArgb() != border_color_argb)
                    {
                        map.SetPixel(p.X, p.Y, filling_color);
                        p.X--;
                    }
                    xl = p.X + 1;

                    p.Y++;
                    for (int i = 0; i < 2; i++)
                    {
                        p.X = xl;
                        bool found;

                        while (p.X <= xr)
                        {
                            found = false;
                            while (map.GetPixel(p.X, p.Y).ToArgb() != border_color_argb && map.GetPixel(p.X, p.Y).ToArgb() != filling_color_argb && p.X <= xr)
                            {
                                found = true;
                                p.X++;
                            }

                            if (found)
                            {
                                p.X--;
                                fill_points.Push(p);
                                p.X++;
                            }

                            while ((map.GetPixel(p.X, p.Y).ToArgb() == border_color_argb || map.GetPixel(p.X, p.Y).ToArgb() == filling_color_argb) && p.X <= xr)
                                p.X++;
                        }

                        p.Y -= 2;
                        sw.Stop();
                        if (is_sleep)
                        {
                            UpdateCanvas();
                            Thread.Sleep(3);
                        }
                        sw.Start();
                    }
                }

                return sw.ElapsedMilliseconds;
            }
            catch
            {
                MessageBox.Show("Выход затравочного пикселя за границы полотна", "Ошибка затравки");
                return 0;
            }
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

                if (polygon_start_p == Point.Empty)
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

        private void buttonPixel_Click(object sender, EventArgs e)
        {
            try
            {
                fill_pixel = new Point(int.Parse(pixelX.Text), int.Parse(pixelY.Text));
                map.SetPixel(fill_pixel.X, fill_pixel.Y, fillingColorBox.BackColor);
                using (Graphics g = Graphics.FromImage(map))
                {
                    g.TextRenderingHint = System.Drawing.Text.TextRenderingHint.AntiAlias;
                    TextRenderer.DrawText(g, "(" + fill_pixel.X.ToString() + ", " + fill_pixel.Y.ToString() + ")",
                                          new Font("Arial", 8), new Point(fill_pixel.X, fill_pixel.Y), fillingColorBox.BackColor);
                }
                UpdateCanvas();
            }
            catch
            {
                MessageBox.Show("Ошибка чтения затравочного пикселя", "Введённые данные некорректны");
            }
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

        private void buttonSlosePol_Click(object sender, EventArgs e)
        {
            if (polygon_start_p == Point.Empty)
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
