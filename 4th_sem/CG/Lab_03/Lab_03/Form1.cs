using System;
using System.Diagnostics;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using OxyPlot;
using OxyPlot.Series;
using OxyPlot.Axes;

namespace Lab_03
{
    public partial class MainWindow : Form
    {
        Bitmap map;

        public MainWindow()
        {
            InitializeComponent();

            map = new Bitmap(pictureBox1.Width, pictureBox1.Height);
        }

        public static int RoundToInt(double d)
        {
            return (int)Math.Round(d, MidpointRounding.AwayFromZero);
        }

        public static Color ColorByIntensityLevels(Color c, float Intensity, int levelsIntensity)
        {
            return Color.FromArgb(RoundToInt(Intensity * (255f / levelsIntensity)), c.R, c.G, c.B);
        }

        public static Color ColorByIntensity(Color c, float Intensity)
        {
            return Color.FromArgb(RoundToInt(Intensity * 255), c.R, c.G, c.B);
        }

        public static void SwapInt(ref int a, ref int b)
        {
            int temp = a;
            a = b;
            b = temp;
        }

        public static bool IsEqual(double a, double b)
        {
            double eps = 1e-6;

            return Math.Abs(a - b) < eps;
        }

        public static long Standard(Bitmap map, Color lineColor, int x_start, int y_start, int x_end, int y_end)
        {
            var sw = Stopwatch.StartNew();
            using (Graphics g = Graphics.FromImage(map))
                g.DrawLine(new Pen(lineColor), x_start, y_start, x_end, y_end);
            return sw.ElapsedTicks;
        }

        public static KeyValuePair<long, int> DDA(Bitmap map, Color lineColor, int x_start, int y_start, int x_end, int y_end)
        {
            if (x_start == x_end && y_start == y_end && x_start >= 0 && x_start < map.Width && y_start >= 0 &&
                y_start < map.Height)
            {
                map.SetPixel(x_start, y_start, lineColor);
                return new KeyValuePair<long, int>(1, 0);
            }
            else
            {
                var sw = Stopwatch.StartNew();

                int l = Math.Abs(x_end - x_start) >= Math.Abs(y_end - y_start) ? Math.Abs(x_end - x_start) :
                                                                                 Math.Abs(y_end - y_start);
                float dx = (float)(x_end - x_start) / l;
                float dy = (float)(y_end - y_start) / l;

                float x = x_start, y = y_start;
                int stairs = 0;
                int x_prev = RoundToInt(x), y_prev = RoundToInt(y);
                for (int i = 0; i <= l; i++)
                {
                    int x_r = RoundToInt(x), y_r = RoundToInt(y);

                    if (Math.Abs(x_r - x_prev) == 1 && Math.Abs(y_r - y_prev) == 1)
                        stairs++;

                    x_prev = x_r;
                    y_prev = y_r;

                    sw.Stop();
                    if (map != null && x_r >= 0 && x_r < map.Width && y_r >= 0 && y_r < map.Height)
                        map.SetPixel(x_r, y_r, lineColor);
                    sw.Start();

                    x += dx;
                    y += dy;
                }

                sw.Stop();
                return new KeyValuePair<long, int>(sw.ElapsedTicks, stairs);
            }
        }

        public static KeyValuePair<long, int> BresenhamReal(Bitmap map, Color lineColor, int x_start, int y_start, int x_end, int y_end)
        {
            if (x_start == x_end && y_start == y_end && x_start >= 0 && x_start < map.Width && y_start >= 0 &&
                y_start < map.Height)
            {
                map.SetPixel(x_start, y_start, lineColor);
                return new KeyValuePair<long, int>(1, 0);
            }
            else
            {
                var sw = Stopwatch.StartNew();
                int swap_f = 0;
                int dx = x_end - x_start, dy = y_end - y_start;
                int sx = Math.Sign(dx), sy = Math.Sign(dy);

                dx = Math.Abs(dx);
                dy = Math.Abs(dy);
                float m = (float)dy / dx;

                if (m > 1)
                {
                    SwapInt(ref dx, ref dy);

                    m = 1 / m;
                    swap_f = 1;
                }

                float error = m - 0.5f;
                int x = x_start, y = y_start;
                int x_prev = x, y_prev = y;
                int stairs = 0;
                for (int i = 0; i <= dx; i++)
                {
                    sw.Stop();
                    if (map != null && x >= 0 && x < map.Width && y >= 0 && y < map.Height)
                        map.SetPixel(x, y, lineColor);
                    sw.Start();

                    if (Math.Abs(x - x_prev) == 1 && Math.Abs(y - y_prev) == 1)
                        stairs++;

                    x_prev = x;
                    y_prev = y;

                    if (error > 0)
                    {
                        if (swap_f == 1)
                            x += sx;
                        else
                            y += sy;
                        error -= 1;
                    }

                    if (error < 0)
                    {
                        if (swap_f == 1)
                            y += sy;
                        else
                            x += sx;
                    }

                    error += m;
                }

                sw.Stop();
                return new KeyValuePair<long, int>(sw.ElapsedTicks, stairs);
            }
        }

        public static KeyValuePair<long, int> BresenhamInt(Bitmap map, Color lineColor, int x_start, int y_start, int x_end, int y_end)
        {
            if (x_start == x_end && y_start == y_end && x_start >= 0 && x_start < map.Width && y_start >= 0 &&
                y_start < map.Height)
            {
                map.SetPixel(x_start, y_start, lineColor);
                return new KeyValuePair<long, int>(1, 0);
            }
            else
            {
                var sw = Stopwatch.StartNew();
                int swap_f = 0;
                int dx = x_end - x_start, dy = y_end - y_start;
                int sx = Math.Sign(dx), sy = Math.Sign(dy);

                dx = Math.Abs(dx);
                dy = Math.Abs(dy);
                float m = (float)dy / dx;

                if (m > 1)
                {
                    SwapInt(ref dx, ref dy);

                    m = 1 / m;
                    swap_f = 1;
                }

                int error = 2 * dy - dx;
                int x = x_start, y = y_start;
                int x_prev = x, y_prev = y;
                int stairs = 0;
                for (int i = 0; i <= dx; i++)
                {
                    sw.Stop();
                    if (map != null && x >= 0 && x < map.Width && y >= 0 && y < map.Height)
                        map.SetPixel(x, y, lineColor);
                    sw.Start();

                    if (Math.Abs(x - x_prev) == 1 && Math.Abs(y - y_prev) == 1)
                        stairs++;

                    x_prev = x;
                    y_prev = y;

                    if (error > 0)
                    {
                        if (swap_f == 1)
                            x += sx;
                        else
                            y += sy;
                        error -= 2 * dx;
                    }

                    if (error < 0)
                    {
                        if (swap_f == 1)
                            y += sy;
                        else
                            x += sx;
                    }

                    error += 2 * dy;
                }

                sw.Stop();
                return new KeyValuePair<long, int>(sw.ElapsedTicks, stairs);
            }
        }

        public static KeyValuePair<long, int> BresenhamWS(Bitmap map, Color lineColor, int x_start, int y_start, int x_end, int y_end, int Intensity)
        {
            if (x_start == x_end && y_start == y_end && x_start >= 0 && x_start < map.Width && y_start >= 0 &&
                y_start < map.Height)
            {
                map.SetPixel(x_start, y_start, lineColor);
                return new KeyValuePair<long, int>(1, 0);
            }
            else
            {
                var sw = Stopwatch.StartNew();
                int swap_f = 0;
                int dx = x_end - x_start, dy = y_end - y_start;
                int sx = Math.Sign(dx), sy = Math.Sign(dy);

                dx = Math.Abs(dx);
                dy = Math.Abs(dy);
                float m = (float)dy / dx;

                if (m > 1)
                {
                    SwapInt(ref dx, ref dy);

                    m = 1 / m;
                    swap_f = 1;
                }

                float error = IsEqual(m, 0) ? Intensity : Intensity / 2.0f;
                int x = x_start, y = y_start;
                m *= Intensity;
                float W = Intensity - m;
                Color start_c = ColorByIntensityLevels(lineColor, error, Intensity);

                sw.Stop();
                if (map != null && x >= 0 && x < map.Width && y >= 0 && y < map.Height)
                    map.SetPixel(x, y, start_c);

                int stairs = 0;
                for (int i = 0; i < dx; i++)
                {
                    sw.Start();
                    if (error <= W)
                    {
                        if (swap_f == 1)
                            y += sy;
                        else
                            x += sx;
                        error += m;
                    }
                    else if (error > W)
                    {
                        y += sy;
                        x += sx;
                        error -= W;
                        stairs++;
                    }

                    Color c = ColorByIntensityLevels(lineColor, error, Intensity);
                    sw.Stop();
                    if (map != null && x >= 0 && x < map.Width && y >= 0 && y < map.Height)
                        map.SetPixel(x, y, c);
                }

                sw.Stop();
                return new KeyValuePair<long, int>(sw.ElapsedTicks, stairs);
            }
        }

        public static KeyValuePair<long, int> Wu(Bitmap map, Color lineColor, int x_start, int y_start, int x_end, int y_end)
        {
            var sw = Stopwatch.StartNew();
            bool swap_f = Math.Abs(y_end - y_start) > Math.Abs(x_end - x_start);

            if (swap_f)
            {
                SwapInt(ref x_start, ref y_start);
                SwapInt(ref x_end, ref y_end);
            }

            if (x_end < x_start)
            {
                SwapInt(ref x_start, ref x_end);
                SwapInt(ref y_start, ref y_end);
            }

            int dx = x_end - x_start, dy = y_end - y_start;
            float grad = (float)dy / dx;
            Color start_c = ColorByIntensity(lineColor, 1f);


            if (!swap_f)
            {
                if (map != null)
                {
                    sw.Stop();
                    map.SetPixel(x_start, y_start, start_c);
                    map.SetPixel(x_end, y_end, start_c);
                }
            }
            else
            {
                if (map != null)
                {
                    sw.Stop();
                    map.SetPixel(y_start, x_start, start_c);
                    map.SetPixel(y_end, x_end, start_c);
                }
            }
            if (!sw.IsRunning)
                sw.Start();
            float y = y_start + grad;
            int x_prev = x_start, y_prev = y_start;
            int stairs = 0;
            for (int x = x_start + 1; x < x_end; x++)
            {
                if (Math.Abs(x - x_prev) == 1 && Math.Abs((int)y - y_prev) == 1)
                    stairs++;

                x_prev = x;
                y_prev = (int)y;

                if (!swap_f)
                {
                    Color c1 = ColorByIntensity(lineColor, 1 - (y - (float)Math.Truncate(y)));
                    Color c2 = ColorByIntensity(lineColor, y - (float)Math.Truncate(y));

                    if (map != null)
                    {
                        sw.Stop();
                        map.SetPixel(x, (int)y, c1);
                        map.SetPixel(x, (int)y + 1, c2);
                    }
                }
                else
                {
                    Color c1 = ColorByIntensity(lineColor, 1 - (y - (float)Math.Truncate(y)));
                    Color c2 = ColorByIntensity(lineColor, y - (float)Math.Truncate(y));

                    if (map != null)
                    {
                        sw.Stop();
                        map.SetPixel((int)y, x, c1);
                        map.SetPixel((int)y + 1, x, c2);
                    }
                }
                if (!sw.IsRunning)
                    sw.Start();
                y += grad;
            }

            sw.Stop();
            return new KeyValuePair<long, int> (sw.ElapsedTicks, stairs);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            int x_start, y_start;
            int x_end, y_end;

            if (int.TryParse(textStartP_X.Text, out x_start) && int.TryParse(textStartP_Y.Text, out y_start) &&
                int.TryParse(textEndP_X.Text, out x_end) && int.TryParse(textEndP_Y.Text, out y_end))
            {
                switch (choiceAlg.SelectedIndex)
                {
                    case 0:
                        Standard(map, lineColor.BackColor, x_start, y_start, x_end, y_end);
                        break;

                    case 1:
                        DDA(map, lineColor.BackColor, x_start, y_start, x_end, y_end);
                        break;

                    case 2:
                        BresenhamReal(map, lineColor.BackColor, x_start, y_start, x_end, y_end);
                        break;

                    case 3:
                        BresenhamInt(map, lineColor.BackColor, x_start, y_start, x_end, y_end);
                        break;

                    case 4:
                        BresenhamWS(map, lineColor.BackColor, x_start, y_start, x_end, y_end, 10);
                        break;

                    case 5:
                        Wu(map, lineColor.BackColor, x_start, y_start, x_end, y_end);
                        break;

                    default:
                        MessageBox.Show("Выберите алгоритм рисования отрезка.", "Ошибка ввода данных",
                                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                        return;
                }
                pictureBox1.BackColor = bgColor.BackColor;
                pictureBox1.Image = map;
            }
            else
                MessageBox.Show("Не введены концы отрезка или введены некорректно.", "Ошибка ввода данных",
                                MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        private void pictureBox2_Click(object sender, EventArgs e)
        {
            if (colorDialog1.ShowDialog() == DialogResult.OK)
            {
                lineColor.BackColor = colorDialog1.Color;
            }
        }

        private void pictureBox2_Click_1(object sender, EventArgs e)
        {
            if (colorDialog2.ShowDialog() == DialogResult.OK)
            {
                bgColor.BackColor = colorDialog2.Color;
            }
        }

        private void buttonAsk_Click(object sender, EventArgs e)
        {
            string info = "Данная программа позволяет строить отрезки и спектры(отрезки, построенные из общей начальной точки с " +
                "заданным шагом поворота и заданной длиной отрезка) различными алгоритмами построения отрезков, сравнивать алгоритмы " +
                "на быстродействие и исследовать их на ступенчатость.\n\tИмеется возможность задать цвет линии и фона. Все величины " +
                "задаются целыми числами. Используется экранная система координат. Сам экран имеет размер 600 на 600 пикселей. Угол измеряется в градусах.";

            MessageBox.Show(info, "Информация о программе", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void buttonClear_Click(object sender, EventArgs e)
        {
            Graphics g = Graphics.FromImage(map);
            g.Clear(bgColor.BackColor);
            pictureBox1.Refresh();
        }

        private void buttonSpectre_Click(object sender, EventArgs e)
        {
            int len, angle;
            int centre_x, centre_y;

            if (int.TryParse(S_length.Text, out len) && int.TryParse(S_angle.Text, out angle) &&
                int.TryParse(S_centre_x.Text, out centre_x) && int.TryParse(S_centre_y.Text, out centre_y))
            {
                if (len < 0)
                {
                    MessageBox.Show("Длина отрезка не может быть меньше нуля.", "Ошибка ввода данных",
                                MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                angle = Math.Abs(angle);
                if (angle > 360)
                {
                    MessageBox.Show("Угол поворота по модулю не может превышать 360.", "Ошибка ввода данных",
                                MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return;
                }

                switch (choiceAlg.SelectedIndex)
                {
                    case 0:
                        using (Graphics g = Graphics.FromImage(map))
                            for (float ang = 0; ang < 360; ang += angle)
                            {
                                int x_end = RoundToInt(centre_x + len * Math.Cos(ang * Math.PI / 180));
                                int y_end = RoundToInt(centre_y + len * Math.Sin(ang * Math.PI / 180));

                                g.DrawLine(new Pen(lineColor.BackColor), centre_x, centre_y, x_end, y_end);
                            }
                        break;

                    case 1:
                        for (float ang = 0; ang < 360; ang += angle)
                        {
                            int x_end = RoundToInt(centre_x + len * Math.Cos(ang * Math.PI / 180));
                            int y_end = RoundToInt(centre_y + len * Math.Sin(ang * Math.PI / 180));

                            DDA(map, lineColor.BackColor, centre_x, centre_y, x_end, y_end);
                        }
                        break;

                    case 2:
                        for (float ang = 0; ang < 360; ang += angle)
                        {
                            int x_end = RoundToInt(centre_x + len * Math.Cos(ang * Math.PI / 180));
                            int y_end = RoundToInt(centre_y + len * Math.Sin(ang * Math.PI / 180));

                            BresenhamReal(map, lineColor.BackColor, centre_x, centre_y, x_end, y_end);
                        }
                        break;

                    case 3:
                        for (float ang = 0; ang < 360; ang += angle)
                        {
                            int x_end = RoundToInt(centre_x + len * Math.Cos(ang * Math.PI / 180));
                            int y_end = RoundToInt(centre_y + len * Math.Sin(ang * Math.PI / 180));

                            BresenhamInt(map, lineColor.BackColor, centre_x, centre_y, x_end, y_end);
                        }
                        break;

                    case 4:
                        for (float ang = 0; ang < 360; ang += angle)
                        {
                            int x_end = RoundToInt(centre_x + len * Math.Cos(ang * Math.PI / 180));
                            int y_end = RoundToInt(centre_y + len * Math.Sin(ang * Math.PI / 180));

                            BresenhamWS(map, lineColor.BackColor, centre_x, centre_y, x_end, y_end, 10);
                        }
                        break;

                    case 5:
                        for (float ang = 0; ang < 360; ang += angle)
                        {
                            int x_end = RoundToInt(centre_x + len * Math.Cos(ang * Math.PI / 180));
                            int y_end = RoundToInt(centre_y + len * Math.Sin(ang * Math.PI / 180));

                            Wu(map, lineColor.BackColor, centre_x, centre_y, x_end, y_end);
                        }
                        break;

                    default:
                        MessageBox.Show("Выберите алгоритм рисования отрезка.", "Ошибка ввода данных",
                                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                        return;
                }
                pictureBox1.BackColor = bgColor.BackColor;
                pictureBox1.Image = map;
            }
            else
                MessageBox.Show("Не введены параметры спектра или введены некорректно.", "Ошибка ввода данных",
                                MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        private void buttonCmpAlgs_Click(object sender, EventArgs e)
        {
            int x_start, y_start;
            int x_end, y_end;

            if (int.TryParse(textStartP_X.Text, out x_start) && int.TryParse(textStartP_Y.Text, out y_start) &&
                int.TryParse(textEndP_X.Text, out x_end) && int.TryParse(textEndP_Y.Text, out y_end))
            {
                long dda_t = 0, br_r_t = 0, br_i_t = 0, br_a_t = 0, wu_t = 0;
                int count = 1000;

                for (int i = 0; i < count; i++)
                {
                    dda_t += DDA(null, lineColor.BackColor, x_start, y_start, x_end, y_end).Key;
                    br_r_t += BresenhamReal(null, lineColor.BackColor, x_start, y_start, x_end, y_end).Key;
                    br_i_t += BresenhamInt(null, lineColor.BackColor, x_start, y_start, x_end, y_end).Key;
                    br_a_t += BresenhamWS(null, lineColor.BackColor, x_start, y_start, x_end, y_end, 10).Key;
                    wu_t += Wu(null, lineColor.BackColor, x_start, y_start, x_end, y_end).Key;
                }

                dda_t /= count;
                br_r_t /= count;
                br_i_t /= count;
                br_a_t /= count;
                wu_t /= count;

                var myModel = new PlotModel { Title = "Сравнение алгоритмов построения отрезков\nпо скорости(в тактах)" };
                var barSeries = new ColumnSeries
                {
                    ItemsSource = new List<ColumnItem>(new[]
                    {
                    new ColumnItem{ Value = dda_t },
                    new ColumnItem{ Value = br_r_t },
                    new ColumnItem{ Value = br_i_t },
                    new ColumnItem{ Value = br_a_t },
                    new ColumnItem{ Value = wu_t}
                }),
                    LabelPlacement = LabelPlacement.Inside,
                    LabelFormatString = "{0}"
                };
                myModel.Series.Add(barSeries);

                myModel.Axes.Add(new CategoryAxis
                {
                    Position = AxisPosition.Bottom,
                    ItemsSource = new[]
                        {
                            "ЦДА",
                            "Брезенхем\n(действ.)",
                            "Брезенхем\n(целые)",
                            "Брезенхем\n(без ступенч.)",
                            "Ву"
                        }
                });

                Form2 hist_window = new Form2(myModel);

                hist_window.Show();
            }
            else
                MessageBox.Show("Не введены концы отрезка или введены некорректно.", "Ошибка ввода данных",
                                MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        private void buttonCompute_Click(object sender, EventArgs e)
        {
            if (choiceAlg.SelectedIndex == -1)
            {
                MessageBox.Show("Выберите алгоритм рисования отрезка.", "Ошибка ввода данных",
                                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            else if (choiceAlg.SelectedIndex == 0)
            {
                MessageBox.Show("Для данного алгоритма измерить ступенчатость невозможно.", "Ошибка ввода данных",
                                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }

            var model = new PlotModel { Title = "Исследование алгоритма на ступенчатость\n(" + 
                                        choiceAlg.SelectedItem.ToString() + ", длина отрезка - 100 пикселей)" };

            model.Axes.Add(new LinearAxis { Position = AxisPosition.Bottom, Title = "Угол наклона прямой(в градусах)" });
            model.Axes.Add(new LinearAxis { Position = AxisPosition.Left, Title = "Кол-во ступенек" });

            var plot = new LineSeries();

            int len = 100;
            int centre_x = 250, centre_y = 250;

            for (int ang = 0; ang <= 360; ang++)
            {
                int stairs = 0;

                int x_end = RoundToInt(centre_x + len * Math.Cos(ang * Math.PI / 180));
                int y_end = RoundToInt(centre_y + len * Math.Sin(ang * Math.PI / 180));

                switch (choiceAlg.SelectedIndex)
                {
                    case 1:
                        stairs = DDA(null, lineColor.BackColor, centre_x, centre_y, x_end, y_end).Value;
                        break;

                    case 2:
                        stairs = BresenhamReal(null, lineColor.BackColor, centre_x, centre_y, x_end, y_end).Value;
                        break;

                    case 3:
                        stairs = BresenhamInt(null, lineColor.BackColor, centre_x, centre_y, x_end, y_end).Value;
                        break;

                    case 4:
                        stairs = BresenhamWS(null, lineColor.BackColor, centre_x, centre_y, x_end, y_end, 10).Value;
                        break;

                    case 5:
                        stairs = Wu(null, lineColor.BackColor, centre_x, centre_y, x_end, y_end).Value;
                        break;
                }

                plot.Points.Add(new DataPoint(ang, stairs));
            }
;
            model.Series.Add(plot);

            Form2 hist_window = new Form2(model);
            hist_window.Show();
        }
    }
}
