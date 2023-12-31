using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;


namespace lab_07
{
    public partial class Form1 : Form
    {
        List<Line> lines;
        Line last_line;
        Cutter cutter;

        Bitmap saved_picture;
        Graphics g;
        Graphics g_move;

        Pen pen_cutter;
        Pen pen_lines;
        Pen pen_choosen;

        double eps;

        public Form1()
        {
            InitializeComponent();

            lines = new List<Line>();
            lines.Add(new Line());
            last_line = lines[0];
            cutter = new Cutter();

            saved_picture = new Bitmap(canvasBase.Width, canvasBase.Height);
            g = Graphics.FromImage(saved_picture);
            g_move = canvasBase.CreateGraphics();
            canvasBase.Image = saved_picture;

            pen_cutter = new Pen(Color.Black, 1);
            pen_lines = new Pen(Color.Red, 1);
            pen_choosen = new Pen(Color.Blue, 1);

            eps = 1e-3;
        }

        static void Swap<T>(ref T a, ref T b)
        {
            T temp = a;
            a = b;
            b = temp;
        }

        // Рекурсивный вариант алгоритма
        //void MidPointCut(Line line)
        //{
        //    if (line.Len() < eps)
        //        return;

        //    int visible = cutter.IsVisible(line);
        //    if (visible == 0)
        //        return;
        //    else if (visible == 1)
        //    {
        //        g.DrawLine(pen_choosen, line.a, line.b);
        //        return;
        //    }

        //    MidPointCut(new Line(line.a, new PointF((line.a.X + line.b.X) / 2, (line.a.Y + line.b.Y) / 2)));
        //    MidPointCut(new Line(new PointF((line.a.X + line.b.X) / 2, (line.a.Y + line.b.Y) / 2), line.b));
        //}

        void MidPointCut(Line line)
        {
            for (int i = 0; i < 2; i++)
            {
                int is_visible = cutter.IsVisible(line);
                if (is_visible == 1)
                {
                    g.DrawLine(pen_choosen, line.a, line.b);
                    return;
                }
                else if (is_visible == 0)
                    return;

                PointF R = line.a;

                if (cutter.GetCode(line.b) == 0)
                    Swap(ref line.a, ref line.b);
                else
                {
                    while (line.Len() >= eps)
                    {
                        PointF p_mid = new PointF((line.a.X + line.b.X) / 2, (line.a.Y + line.b.Y) / 2);
                        PointF temp = line.a;
                        line.a = p_mid;

                        if (cutter.IsVisible(line) == 0)
                        {
                            line.a = temp;
                            line.b = p_mid;
                        }
                    }

                    line.a = line.b;
                    line.b = R;
                }
            }

            if ((cutter.GetCode(line.a) & cutter.GetCode(line.b)) == 0)
                g.DrawLine(pen_choosen, line.a, line.b);
        }

        private void buttonGetCutter_Click(object sender, EventArgs e)
        {
            lines.Clear();
            lines.Add(new Line());
            last_line = lines[0];

            g.Clear(Color.White);
            canvasBase.Refresh();

            try
            {
                cutter.left = int.Parse(textBoxLeft.Text);
                cutter.right = int.Parse(textBoxRight.Text);
                cutter.down = int.Parse(textBoxDown.Text);
                cutter.up = int.Parse(textBoxUp.Text);

                for (int i = 0; i < 4; i++)
                {
                    int point_border = i < 2 ? canvasBase.Width : canvasBase.Height;
                    if (cutter[i] < 0 || cutter[i] > point_border)
                        throw new Exception("Границы должны быть больше нуля и меньше длины/ширины полотна");
                }

                g.DrawRectangle(pen_cutter, cutter.left, cutter.up, cutter.right - cutter.left, cutter.down - cutter.up);
                canvasBase.Refresh();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Ошибка ввода отсекателя");
            }
        }

        private void canvasBase_MouseClick(object sender, MouseEventArgs e)
        {
            PointF mousePos = new PointF(e.X, e.Y);

            if (e.Button == MouseButtons.Left)
            {
                if (last_line.a.IsEmpty)
                    last_line.a = mousePos;
                else
                {
                    if (ModifierKeys == Keys.Control) // горизонтальная линия
                        last_line.b = new PointF(mousePos.X, last_line.a.Y);
                    else if (ModifierKeys == Keys.Alt) // вертикальная линия
                        last_line.b = new PointF(last_line.a.X, mousePos.Y);
                    else
                        last_line.b = mousePos;

                    g.DrawLine(pen_lines, last_line.a, last_line.b);
                    canvasBase.Refresh();
                    lines.Add(new Line());
                    last_line = lines[lines.Count() - 1];
                }
            }
        }


        private void buttonClear_Click(object sender, EventArgs e)
        {
            lines.Clear();
            lines.Add(new Line());
            last_line = lines[0];

            g.Clear(Color.White);
            canvasBase.Refresh();
        }


        private void buttonCut_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < lines.Count() -1; i++)
            {
                MidPointCut(lines[i]);
                canvasBase.Refresh();
            }
            canvasBase.Refresh();
        }

        private void canvasBase_MouseMove(object sender, MouseEventArgs e)
        {
            labelLocation.Text = "Положение курсора: " + canvasBase.PointToClient(MousePosition).ToString();
            canvasBase.Refresh();

            if (last_line.b.IsEmpty && !last_line.a.IsEmpty)
            {
                PointF a = last_line.a;
                PointF b = canvasBase.PointToClient(MousePosition);

                if (ModifierKeys == Keys.Control)
                    b.Y = a.Y;
                else if (ModifierKeys == Keys.Alt)
                    b.X = a.X;

                g_move.DrawLine(pen_lines, a, b);
            }
        }

        private void buttonInfo_Click(object sender, EventArgs e)
        {
            string info = "Данная программа позволяет отсекать отрезки регулярным отсекателем с помощью алгоритма " +
                "разбиения средней точкой.\n\tГраницы отсекателя задаются целыми числами. Используется экранная система координат. " +
                "Сам экран имеет размер 1300 на 700 пикселей.";

            MessageBox.Show(info, "Информация о программе", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }
    }
}
