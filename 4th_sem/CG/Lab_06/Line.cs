using System.Drawing;
using System;

namespace Lab_06
{
    public class Line
    {
        public Point start, end;

        public Line(Point start, Point end)
        {
            this.start = start;
            this.end = end;
        }

        public Line(int x_start, int y_start, int x_end, int y_end)
        {
            start.X = x_start;
            start.Y = y_start;

            end.X = x_end;
            end.Y = y_end;
        }

        public void Draw(Bitmap map, Color color)
        {
            if (start.X == end.X && start.Y == end.Y)
            {
                map.SetPixel(start.X, start.Y, color);
                return;
            }

            bool swap_f = false;
            int dx = end.X - start.X, dy = end.Y - start.Y;
            int sx = Math.Sign(dx), sy = Math.Sign(dy);

            dx = Math.Abs(dx);
            dy = Math.Abs(dy);

            if (dy >= dx)
            {
                int temp = dx;
                dx = dy;
                dy = temp;

                swap_f = true;
            }

            int error = 2 * dy - dx;
            int x = start.X, y = start.Y;

            for (int i = 0; i < dx; i++)
            {
                map.SetPixel(x, y, color);

                if (error >= 0)
                {
                    if (swap_f)
                        x += sx;
                    else
                        y += sy;
                    error -= 2 * dx;
                }

                if (error < 0)
                {
                    if (swap_f)
                        y += sy;
                    else
                        x += sx;
                }

                error += 2 * dy;
            }
        }
    }
}
