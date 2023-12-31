using System.Drawing;

namespace lab_07
{
    class Cutter
    {
        public int left = 0;
        public int right = 0;
        public int up = 0;
        public int down = 0;


        public int GetCode(PointF p)
        {
            int sum = 0;

            if (p.X < left)
                sum += 8;
            if (p.X > right)
                sum += 4;
            if (p.Y > down)
                sum += 2;
            if (p.Y < up)
                sum += 1;

            return sum;
        }


        public int IsVisible(Line line)
        {
            int SumA = GetCode(line.a);
            int SumB = GetCode(line.b);

            int visibility = -1; // не определено

            if (SumA == 0 && SumB == 0)
                visibility = 1; // полностью видимо
            else
                if ((SumA & SumB) != 0) // проверка тривиальной невидимости отрезка
                    visibility = 0;

            return visibility;
        }


        public int this[int index]
        {
            get
            {
                switch(index)
                {
                    case 0:
                        return left;
                    case 1:
                        return right;
                    case 2:
                        return down;
                    case 3:
                        return up;
                    default:
                        return -1;
                }
            }
        }
    }
}
