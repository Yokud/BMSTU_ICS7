using System.Collections.Generic;
using System.Drawing;
using System;

namespace Lab_06
{
    public class Lines
    {
        List<Line> lines;

        public Lines()
        {
            lines = new List<Line>();
        }

        public void AddLine(Line line)
        {
            lines.Add(line);
        }

        public bool IsVoid()
        {
            return lines.Count == 0;
        }

        public void DrawLines(Bitmap map, Color color, bool draw_coord)
        {
            foreach (Line line in lines)
            {
                line.Draw(map, color);

                if (draw_coord)
                    using (Graphics g = Graphics.FromImage(map))
                    {
                        g.TextRenderingHint = System.Drawing.Text.TextRenderingHint.AntiAlias;
                        Point temp = new Point(line.end.X, line.end.Y);

                        System.Windows.Forms.TextRenderer.DrawText(g, "(" + temp.X.ToString() + ", " + temp.Y.ToString() + ")",
                                              new Font("Arial", 8), temp, Color.Black);
                    }
            }
        }

        public void MinMaxValues(out int x_min, out int x_max, out int y_min, out int y_max)
        {
            x_min = lines[0].start.X;
            x_max = lines[0].start.X;
            y_min = lines[0].start.Y;
            y_max = lines[0].start.Y;

            foreach (Line l in lines)
            {
                if (l.start.X < x_min)
                    x_min = l.start.X;
                if (l.end.X < x_min)
                    x_min = l.end.X;

                if (l.start.X > x_max)
                    x_max = l.start.X;
                if (l.end.X > x_max)
                    x_max = l.end.X;

                if (l.start.Y < y_min)
                    y_min = l.start.Y;
                if (l.end.Y < y_min)
                    y_min = l.end.Y;

                if (l.start.Y > y_max)
                    y_max = l.start.Y;
                if (l.end.Y > y_max)
                    y_max = l.end.Y;
            }
        }
    }
}
