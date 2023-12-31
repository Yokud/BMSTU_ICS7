using System.Drawing;
using System;

namespace Lab_05
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

        public void DrawSpec(Bitmap map, Color color)
        {
            if (start.X == end.X && start.Y == end.Y)
            {
                map.SetPixel(start.X, start.Y, color);
                return;
            }

            // Случай горизонтальной линии
            if (start.Y == end.Y)
            {
                int start_x = start.X, end_x = end.X;

                if (start.X > end.X)
                {
                    end_x = start.X;
                    start_x = end.X;
                }

                for (int curr_x = start_x; curr_x < end_x; curr_x++)
                    map.SetPixel(curr_x, start.Y, color);
                return;
            }

            bool swap_f = false;
            int dx = end.X - start.X, dy = end.Y - start.Y;
            int sx = Math.Sign(dx), sy = Math.Sign(dy);

            dx = Math.Abs(dx);
            dy = Math.Abs(dy);

            int dx_real = dx, dy_real = dy;

            if (dy >= dx)
            {
                int temp = dx;
                dx = dy;
                dy = temp;

                swap_f = true;
            }

            int error = 2 * dy - dx;
            int x = start.X, y = start.Y;
            int last_y = -1;

            for (int i = 0; i <= dx; i++)
            {
                // гарантируем, что последний пиксель линии, у которой dx > dy, будет закрашен несмотря на заполнение по левой границе.
                // это нужно, чтобы в одной горизонтали не образовалось двух ограничивающих пикселей, нарисованных разными линиями
                if (dx_real > dy_real && y == end.Y)
                {
                    map.SetPixel(end.X, end.Y, color);
                    break;
                }

                // заполняем по левой границе, чтобы обеспечить единственность ограничивающего пикселя в одной строке
                if (y != last_y)
                {
                    last_y = y;
                    // точки не должны быть начальной и конечной, потому что иначе
                    // на краях отрезка будут вставлены лишние пиксели, при этом обработкой
                    // краёв занимается цикл по ребрам после отрисовки всего контура
                    if (map.GetPixel(x, y).ToArgb() == color.ToArgb() && (x != start.X || y != start.Y) && (x != end.X || y != end.Y))
                        map.SetPixel(x + 1, y, color);
                    else
                        map.SetPixel(x, y, color);
                }

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
