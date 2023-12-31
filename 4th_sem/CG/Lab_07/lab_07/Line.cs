using System.Drawing;


namespace lab_07
{
        class Line
        {
            public PointF a, b;

            public Line(PointF a, PointF b)
            {
                this.a = a;
                this.b = b;
            }

            public Line()
            {
                a = PointF.Empty;
                b = PointF.Empty;
            }

            public double Len()
            {
                return System.Math.Sqrt((a.X - b.X) * (a.X - b.X) + (a.Y - b.Y) * (a.Y - b.Y));
            }

            public static double Len(PointF a1, PointF a2)
            {
                return System.Math.Sqrt((a1.X - a2.X) * (a1.X - a2.X) + (a1.Y - a2.Y) * (a1.Y - a2.Y));
            }
        }
}
