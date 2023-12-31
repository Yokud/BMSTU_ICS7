using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;

namespace Lab_04
{
    public partial class Form1 : Form
    {

        Bitmap map;
        public Form1()
        {
            InitializeComponent();

            map = new Bitmap(Canvas.Width, Canvas.Height);
        }

        public static int RoundToInt(double d)
        {
            return (int)Math.Round(d, MidpointRounding.AwayFromZero);
        }

        public static bool IsEqual(double a, double b)
        {
            double eps = 1e-6;

            return Math.Abs(a - b) < eps;
        }

        public static void DrawPoints(Bitmap map, List<Point> points, Color color)
        {
            foreach (Point p in points)
                map.SetPixel(p.X, p.Y, color);
        }

        public static void OctantMirrored(List<Point> points, int x, int y, int centre_x, int centre_y)
        {
            if (points == null)
                return;

            List<Point> new_points = new List<Point>{ 
                new Point(x, y), 
                new Point(2 * centre_x - x, y),
                new Point(x, 2 * centre_y - y),
                new Point(2 * centre_x - x, 2 * centre_y - y),
                new Point(y + centre_x - centre_y, x + centre_y - centre_x),
                new Point(-y + centre_x + centre_y, x + centre_y - centre_x),
                new Point(y + centre_x - centre_y, -x + centre_y + centre_x),
                new Point(-y + centre_x + centre_y, -x + centre_y + centre_x)};

            points.AddRange(new_points);
        }

        public static void QuarterMirrored(List<Point> points, int x, int y, int centre_x, int centre_y)
        {
            if (points == null)
                return;

            List<Point> new_points = new List<Point>{
                new Point(x, y),
                new Point(2 * centre_x - x, y),
                new Point(x, 2 * centre_y - y),
                new Point(2 * centre_x - x, 2 * centre_y - y) };

            points.AddRange(new_points);
        }

        private void buttonClear_Click(object sender, EventArgs e)
        {
            Graphics g = Graphics.FromImage(map);
            g.Clear(bgColorBox.BackColor);
            Canvas.Refresh();
        }

        private void buttonAsk_Click(object sender, EventArgs e)
        {
            string info = "Данная программа позволяет строить окружности, эллипсы, концентрические окружности и эллипсы " +
                "различными алгоритмами построения окружностей и эллипсов и сравнивать алгоритмы " +
                "на быстродействие.\n\tИмеется возможность задать цвет линии и фона. Все величины " +
                "задаются целыми числами. Используется экранная система координат. Сам экран имеет размер 700 на 800 пикселей. ";

            MessageBox.Show(info, "Информация о программе", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void circleColorBox_Click(object sender, EventArgs e)
        {
            if (circleColor.ShowDialog() == DialogResult.OK)
                circleColorBox.BackColor = circleColor.Color;
        }

        private void circlesColorBox_Click(object sender, EventArgs e)
        {
            if (circlesColor.ShowDialog() == DialogResult.OK)
                circlesColorBox.BackColor = circlesColor.Color;
        }

        private void ellipseColorBox_Click(object sender, EventArgs e)
        {
            if (ellipseColor.ShowDialog() == DialogResult.OK)
                ellipseColorBox.BackColor = ellipseColor.Color;
        }

        private void ellipsesColorBox_Click(object sender, EventArgs e)
        {
            if (ellipsesColor.ShowDialog() == DialogResult.OK)
                ellipsesColorBox.BackColor = ellipsesColor.Color;
        }

        private void bgColorBox_Click(object sender, EventArgs e)
        {
            if (bgColor.ShowDialog() == DialogResult.OK)
                bgColorBox.BackColor = bgColor.Color;
        }

        public static long circleCanon(List<Point> points, int centre_x, int centre_y, int radius)
        {
            var timer = Stopwatch.StartNew();

            for (int x = centre_x; x <= centre_x + RoundToInt(radius / Math.Sqrt(2)); x++)
            {
                int y = centre_y + RoundToInt(Math.Sqrt(radius * radius - (x - centre_x) * (x - centre_x)));

                OctantMirrored(points, x, y, centre_x, centre_y);
            }

            return timer.ElapsedTicks;
        }

        public static long circleParam(List<Point> points, int centre_x, int centre_y, int radius)
        {
            var timer = Stopwatch.StartNew();

            double step = 1.0 / radius;

            for (double t = 0.0; t <= Math.PI / 4; t += step)
            {
                int x = centre_x + RoundToInt(radius * Math.Cos(t));
                int y = centre_y + RoundToInt(radius * Math.Sin(t));

                OctantMirrored(points, x, y, centre_x, centre_y);
            }

            return timer.ElapsedTicks;
        }

        public static long circleBresenham(List<Point> points, int centre_x, int centre_y, int radius)
        {
            var timer = Stopwatch.StartNew();

            int x = 0, y = radius, D = 2 * (1 - radius);

            while (x <= y)
            {
                OctantMirrored(points, x + centre_x, y + centre_y, centre_x, centre_y);

                if (D < 0)
                {
                    int D1 = 2 * D + 2 * y - 1;
                    if (D1 <= 0)
                    {
                        x += 1;
                        D += 2 * x + 1;
                    }
                    else
                    {
                        x += 1;
                        y -= 1;
                        D += 2 * (x - y + 1);
                    }
                }
                else
                {
                    x += 1;
                    y -= 1;
                    D += 2 * (x - y + 1);
                }
            }

            return timer.ElapsedTicks;
        }

        public static long circleMidPoint(List<Point> points, int centre_x, int centre_y, int radius)
        {
            var timer = Stopwatch.StartNew();

            int x = 0, y = radius, delta = RoundToInt(1.25 - radius);

            while (x <= y)
            {
                OctantMirrored(points, x + centre_x, y + centre_y, centre_x, centre_y);

                if (delta > 0)
                {
                    x += 1;
                    y -= 1;
                    delta += 2 * (x - y);
                }
                else
                {
                    x += 1;
                    delta += 2 * x + 1;
                }
            }

            return timer.ElapsedTicks;
        }

        public static long ellipseCanon(List<Point> points, int centre_x, int centre_y, int a, int b)
        {
            var timer = Stopwatch.StartNew();

            int limit = centre_x + RoundToInt(a / Math.Sqrt(1 +  b * b / (a * a)));

            for (int x = centre_x; x <= limit; x++)
            {
                int y = RoundToInt(Math.Sqrt(a * a - (x - centre_x) * (x - centre_x)) * b / a) + centre_y;
                QuarterMirrored(points, x, y, centre_x, centre_y);
            }

            limit = centre_y + RoundToInt(b / Math.Sqrt(1 + a * a / (b * b)));

            for (int y = limit; y > centre_y - 1; y--)
            {
                int x = RoundToInt(Math.Sqrt(b * b - (y - centre_y) * (y - centre_y)) * a / b) + centre_x;
                QuarterMirrored(points, x, y, centre_x, centre_y);
            }

            return timer.ElapsedTicks;
        }

        public static long ellipseParam(List<Point> points, int centre_x, int centre_y, int a, int b)
        {
            var timer = Stopwatch.StartNew();

            double step = 1.0 / Math.Max(a, b);

            for (double t = 0.0; t <= Math.PI / 2; t += step)
            {
                int x = centre_x + RoundToInt(a * Math.Cos(t));
                int y = centre_y + RoundToInt(b * Math.Sin(t));

                QuarterMirrored(points, x, y, centre_x, centre_y);
            }

            return timer.ElapsedTicks;
        }

        public static long ellipseBresenham(List<Point> points, int centre_x, int centre_y, int a, int b)
        {
            var timer = Stopwatch.StartNew();

            int x = 0, y = b;
            int b2 = b * b, a2 = a * a;
            int delta = RoundToInt(b2 - a2 * b + 0.25 * a2);

            while (b2 * x < a2 * y)
            {
                QuarterMirrored(points, x + centre_x, y + centre_y, centre_x, centre_y);

                if (delta >= 0)
                {
                    y -= 1;
                    delta -= 4 * a2 * y;
                }

                delta += 2 * b2 * (3 + 2 * x);
                x += 1;
            }

            delta = RoundToInt(b2 * (x + 0.5) * (x + 0.5) + a2 * (y - 0.5) * (y - 0.5) - a2 * b2);

            while (y + 1 > 0)
            {
                QuarterMirrored(points, x + centre_x, y + centre_y, centre_x, centre_y);

                if (delta <= 0)
                {
                    x += 1;
                    delta += 4 * b2 * x;
                }

                y -= 1;
                delta += 2 * a2 * (3 - 2 * y);
            }

            return timer.ElapsedTicks;
        }

        public static long ellipseMidPoint(List<Point> points, int centre_x, int centre_y, int a, int b)
        {
            var timer = Stopwatch.StartNew();

            int x = 0, y = b;

            int b2 = b * b, a2 = a * a;

            double delta = b2 - a2 * b + 0.25 * a2;

            while (b2 * x < a2 * y)
            {
                QuarterMirrored(points, x + centre_x, y + centre_y, centre_x, centre_y);

                if (delta > 0)
                {
                    x += 1;
                    y -= 1;
                    
                    delta += 2 * b2 * x - 2 * a2 * y;
                }
                else
                {
                    x += 1;
                    delta += b2 * (2 * x + 1);
                }
            }

            delta += 0.75 * (a2 + b2) - (a2 * y + b2 * x);

            while (y >= 0)
            {
                QuarterMirrored(points, x + centre_x, y + centre_y, centre_x, centre_y);

                if (delta > 0)
                {
                    y -= 1;
                    x += 1;
                    delta += a2 * (2 * y + 1) - 2 * b2 * x;
                }
                else
                {
                    y -= 1;
                    delta += a2 * (2 * y + 1);
                }
            }

            return timer.ElapsedTicks;
        }

        private void buttonDrawCircle_Click(object sender, EventArgs e)
        {
            List<Point> points = new List<Point>();

            if (int.TryParse(circleX.Text, out int x) && int.TryParse(circleY.Text, out int y) && int.TryParse(circleRad.Text, out int radius))
            {
                switch (cIrcleAlg.SelectedIndex)
                {
                    case 0:
                        circleCanon(points, x, y, radius);
                        break;

                    case 1:
                        circleParam(points, x, y, radius);
                        break;

                    case 2:
                        circleBresenham(points, x, y, radius);
                        break;

                    case 3:
                        circleMidPoint(points, x, y, radius);
                        break;

                    case 4:
                        using (Graphics g = Graphics.FromImage(map))
                            g.DrawEllipse(new Pen(circleColorBox.BackColor), new Rectangle(x - radius, y - radius, 2 * radius, 2 * radius));
                        break;

                    default:
                        MessageBox.Show("Выберите алгоритм рисования окружности.", "Ошибка ввода данных",
                                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                        return;
                }

                
                DrawPoints(map, points, circleColorBox.BackColor);
                Canvas.BackColor = bgColorBox.BackColor;
                Canvas.Image = map;
            }
            else
                MessageBox.Show("Не введены параметры окружности или введены некорректно.", "Ошибка ввода данных",
                                MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        private void buttonDrawCircles_Click(object sender, EventArgs e)
        {
            List<Point> points = new List<Point>();

            if (int.TryParse(circlesX.Text, out int x) && int.TryParse(circlesY.Text, out int y) &&
                int.TryParse(circlesRad.Text, out int radius) && int.TryParse(circlesStep.Text, out int step) &&
                int.TryParse(circlesCount.Text, out int count))
            {
                switch (circlesAlg.SelectedIndex)
                {
                    case 0:
                        for (int i = 0; i < count; i++)
                            circleCanon(points, x, y, radius + step * i);
                        break;

                    case 1:
                        for (int i = 0; i < count; i++)
                            circleParam(points, x, y, radius + step * i);
                        break;

                    case 2:
                        for (int i = 0; i < count; i++)
                            circleBresenham(points, x, y, radius + step * i);
                        break;

                    case 3:
                        for (int i = 0; i < count; i++)
                            circleMidPoint(points, x, y, radius + step * i);
                        break;

                    case 4:
                        using (Graphics g = Graphics.FromImage(map))
                        {
                            for (int i = 0; i < count; i++)
                                g.DrawEllipse(new Pen(circlesColorBox.BackColor), new Rectangle(x - (radius + step * i), y - (radius + step * i),
                                                                                                2 * (radius + step * i), 2 * (radius + step * i)));
                        }
                        break;

                    default:
                        MessageBox.Show("Выберите алгоритм рисования окружностей.", "Ошибка ввода данных",
                                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                        return;
                }

                
                DrawPoints(map, points, circlesColorBox.BackColor);
                Canvas.BackColor = bgColorBox.BackColor;
                Canvas.Image = map;
            }
            else
                MessageBox.Show("Не введены параметры концентрических окружностей или введены некорректно.", "Ошибка ввода данных",
                                MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        private void buttonDrawEllipse_Click(object sender, EventArgs e)
        {
            List<Point> points = new List<Point>();

            if (int.TryParse(ellipseX.Text, out int x) && int.TryParse(ellipseY.Text, out int y) &&
                int.TryParse(ellipseA.Text, out int a) && int.TryParse(ellipseB.Text, out int b))
            {
                switch (ellipseAlg.SelectedIndex)
                {
                    case 0:
                        ellipseCanon(points, x, y, a, b);
                        break;

                    case 1:
                        ellipseParam(points, x, y, a, b);
                        break;

                    case 2:
                        ellipseBresenham(points, x, y, a, b);
                        break;

                    case 3:
                        ellipseMidPoint(points, x, y, a, b);
                        break;

                    case 4:
                        using (Graphics g = Graphics.FromImage(map))
                            g.DrawEllipse(new Pen(ellipseColorBox.BackColor), new Rectangle(x - a, y - b, 2 * a, 2 * b));
                        break;

                    default:
                        MessageBox.Show("Выберите алгоритм рисования отрезка.", "Ошибка ввода данных",
                                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                        return;
                }

                DrawPoints(map, points, ellipseColorBox.BackColor);
                Canvas.BackColor = bgColorBox.BackColor;
                Canvas.Image = map;
            }
            else
                MessageBox.Show("Не введены параметры эллипса или введены некорректно.", "Ошибка ввода данных",
                                MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        private void buttonDrawEllipses_Click(object sender, EventArgs e)
        {
            List<Point> points = new List<Point>();

            if (int.TryParse(ellipsesX.Text, out int x) && int.TryParse(ellipsesY.Text, out int y) &&
                int.TryParse(ellipsesA.Text, out int a) && int.TryParse(ellipsesB.Text, out int b) &&
                int.TryParse(ellipsesAStep.Text, out int step) && int.TryParse(ellipsesCount.Text, out int count))
            {
                double exc = a >= b ? Math.Sqrt(1 - (double) b * b / (a * a)) : Math.Sqrt(1 - (double) a * a / (b * b));

                switch (ellipsesAlg.SelectedIndex)
                {
                    case 0:
                        for (int i = 0; i < count; i++)
                            if (a >= b)
                                ellipseCanon(points, x, y, a + step * i, RoundToInt((a + step * i) * Math.Sqrt(1 - exc * exc)));
                            else
                                ellipseCanon(points, x, y, RoundToInt((b + step * i) * Math.Sqrt(1 - exc * exc)), b + step * i);
                        break;

                    case 1:
                        for (int i = 0; i < count; i++)
                            if (a >= b)
                                ellipseParam(points, x, y, a + step * i, RoundToInt((a + step * i) * Math.Sqrt(1 - exc * exc)));
                            else
                                ellipseParam(points, x, y, RoundToInt((b + step * i) * Math.Sqrt(1 - exc * exc)), b + step * i);
                        break;

                    case 2:
                        for (int i = 0; i < count; i++)
                            if (a >= b)
                                ellipseBresenham(points, x, y, a + step * i, RoundToInt((a + step * i) * Math.Sqrt(1 - exc * exc)));
                            else
                                ellipseBresenham(points, x, y, RoundToInt((b + step * i) * Math.Sqrt(1 - exc * exc)), b + step * i);
                        break;

                    case 3:
                        for (int i = 0; i < count; i++)
                            if (a >= b)
                                ellipseMidPoint(points, x, y, a + step * i, RoundToInt((a + step * i) * Math.Sqrt(1 - exc * exc)));
                            else
                                ellipseMidPoint(points, x, y, RoundToInt((b + step * i) * Math.Sqrt(1 - exc * exc)), b + step * i);
                        break;

                    case 4:
                        using (Graphics g = Graphics.FromImage(map))
                        {
                            for (int i = 0; i < count; i++)
                                if (a >= b)
                                    g.DrawEllipse(new Pen(ellipsesColorBox.BackColor), new Rectangle(x - (a + step * i), 
                                                    y - RoundToInt((a + step * i) * Math.Sqrt(1 - exc * exc)), 2 * (a + step * i), 
                                                    2 * RoundToInt((a + step * i) * Math.Sqrt(1 - exc * exc))));
                                else
                                    g.DrawEllipse(new Pen(ellipsesColorBox.BackColor), 
                                                    new Rectangle(x - RoundToInt((b + step * i) * Math.Sqrt(1 - exc * exc)),
                                                                  y - (b + step * i), 
                                                                  2 * RoundToInt((b + step * i) * Math.Sqrt(1 - exc * exc)),
                                                                  2 * (b + step * i)));
                        }
                        break;

                    default:
                        MessageBox.Show("Выберите алгоритм рисования эллипсов.", "Ошибка ввода данных",
                                        MessageBoxButtons.OK, MessageBoxIcon.Error);
                        return;
                }

                DrawPoints(map, points, ellipsesColorBox.BackColor);
                Canvas.BackColor = bgColorBox.BackColor;
                Canvas.Image = map;
            }
            else
                MessageBox.Show("Не введены параметры эллипсов или введены некорректно.", "Ошибка ввода данных",
                                MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        private void buttonCompCircles_Click(object sender, EventArgs e)
        {
            int n = 1000;
            (int, int) rad_interval = (10, 100);

            List<(int, long)> dataCanon = new List<(int, long)>();
            List<(int, long)> dataParam = new List<(int, long)>();
            List<(int, long)> dataBresenham = new List<(int, long)>();
            List<(int, long)> dataMidPoint = new List<(int, long)>();

            for (int r = rad_interval.Item1; r <= rad_interval.Item2; r++)
            {
                long sum_time_canon = 0, sum_time_param = 0, sum_time_br = 0, sum_time_midp = 0;
                for (int i = 0; i < n; i++)
                {
                    sum_time_canon += circleCanon(null, 0, 0, r);
                    sum_time_param += circleParam(null, 0, 0, r);
                    sum_time_br += circleBresenham(null, 0, 0, r);
                    sum_time_midp += circleMidPoint(null, 0, 0, r);
                }

                dataCanon.Add((r, sum_time_canon / n));
                dataParam.Add((r, sum_time_param / n));
                dataBresenham.Add((r, sum_time_br / n));
                dataMidPoint.Add((r, sum_time_midp / n));
            }

            Form2 circles_info = new Form2(0, dataCanon, dataParam, dataBresenham, dataMidPoint);
            circles_info.Show();
        }

        private void buttonCompEllipses_Click(object sender, EventArgs e)
        {
            int n = 1000;
            (int, int) a_interval = (10, 100);
            int b = 5;
            double exc = Math.Sqrt(1 - (double)b * b / (a_interval.Item1 * a_interval.Item1));

            List<(int, long)> dataCanon = new List<(int, long)>();
            List<(int, long)> dataParam = new List<(int, long)>();
            List<(int, long)> dataBresenham = new List<(int, long)>();
            List<(int, long)> dataMidPoint = new List<(int, long)>();

            for (int a = a_interval.Item1; a <= a_interval.Item2; a++)
            {
                long sum_time_canon = 0, sum_time_param = 0, sum_time_br = 0, sum_time_midp = 0;
                for (int i = 0; i < n; i++)
                {
                    sum_time_canon += ellipseCanon(null, 0, 0, a, RoundToInt(a * Math.Sqrt(1 - exc * exc)));
                    sum_time_param += ellipseParam(null, 0, 0, a, RoundToInt(a * Math.Sqrt(1 - exc * exc)));
                    sum_time_br += ellipseBresenham(null, 0, 0, a, RoundToInt(a * Math.Sqrt(1 - exc * exc)));
                    sum_time_midp += ellipseMidPoint(null, 0, 0, a, RoundToInt(a * Math.Sqrt(1 - exc * exc)));
                }

                dataCanon.Add((a, sum_time_canon / n));
                dataParam.Add((a, sum_time_param / n));
                dataBresenham.Add((a, sum_time_br / n));
                dataMidPoint.Add((a, sum_time_midp / n));
            }

            Form2 circles_info = new Form2(1, dataCanon, dataParam, dataBresenham, dataMidPoint);
            circles_info.Show();
        }
    }
}
