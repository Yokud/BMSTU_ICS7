using System;
using System.Collections.Generic;
using System.Drawing;

namespace lab_08
{
    class Cutter
    {
        private List<PointF> vertex;
        private List<Vector> normal;
        private bool finished_input = false;
        private int walk_direction = 0;

        public Cutter()
        {
            vertex = new List<PointF>();
            normal = new List<Vector>();
        }

        public void AddVertex(PointF dot)
        {
            vertex.Add(dot);
        }
        public void AddVertex(float x, float y)
        {
            vertex.Add(new PointF(x, y));
        }

        public void Clear()
        {
            vertex.Clear();
            normal.Clear();
            finished_input = false;
            walk_direction = 0;
        }

        // Закончен ввод отсекателя
        public void Finish()
        {
            finished_input = true;
            walk_direction = ConvexityCheck();
            FindNormalVectors(walk_direction);
        }

        public bool IsFinished()
        {
            return finished_input;
        }

        public bool IsEmpty()
        {
            return vertex.Count == 0;
        }

        public bool IsZero(float x)
        {
            return Math.Abs(x) < 1e-3;
        }

        // Получение вершины по индексу
        public PointF GetVertex(int index)
        {
            if (index < 0)
                return vertex[vertex.Count + index]; // Вершина с конца
            else 
                return vertex[index % vertex.Count];
        }
      
        // Проверка выпуклости; возвращает направление обхода
        private int ConvexityCheck()
        {
            if (vertex.Count < 3)
                return 0;

            Vector a = new Vector(vertex[1], vertex[0]);
            Vector b = new Vector();
            Vector res = new Vector();

            int sign = 0;

            for (int i = 0; i < vertex.Count; i++)
            {
                b = new Vector(GetVertex(i + 1), GetVertex(i));
                Vector.VectorMultiplication(a, b, ref res);

                if (sign == 0)
                    sign = Math.Sign(res.z);
                else if ((sign != Math.Sign(res.z)) && (res.z != 0))
                    return 0;

                a = b;
            }

            if (sign == 0) // Вырождается в линию
                return 0;

            return sign;
        }

        public bool IsConvex()
        {
            if (walk_direction == 0)
                return false;
            return true;
        }

        // Нахождение векторов нормали для отсекателя
        private void FindNormalVectors(int direction)
        {
            Vector b;
            normal.Clear();

            for (int i = 0; i < vertex.Count; i++)
            {
                b = new Vector(GetVertex(i), GetVertex(i + 1));
                Vector n;

                if (IsZero(b.x))
                    n = new Vector(1, 0);
                else
                    n = new Vector(-b.y / b.x, 1);

                if (Vector.ScalarMultiplication(n, new Vector(GetVertex(i), GetVertex(i + 2))) < 0)
                {
                    n.x *= -1;
                    n.y *= -1;
                }


                normal.Add(n);
            }
        }

        // Алгоритм Кируса-Бека по отсечению отрезка
        public Segment CutCyrusBeck(Segment l)
        {

            float t_down = 0, t_up = 1;
            float t_tmp;

            Vector D = new Vector(l.start, l.end);
            Vector w;

            float D_sc;
            float W_sc;

            for (int i = 0; i < vertex.Count; i++)
            {
                w = new Vector(vertex[i], l.start);
                D_sc = Vector.ScalarMultiplication(D, normal[i]);
                W_sc = Vector.ScalarMultiplication(w, normal[i]);

                if (IsZero(D_sc)) // отрезок выродился в точку или сторона парралельна
                {
                    if (W_sc < 0)
                        return new Segment();
                    else if (W_sc > 0)
                        continue; // точка видима относительно текущей границы
                }
                else
                {
                    t_tmp = -W_sc / D_sc;
                    if (D_sc > 0) // поиск нижнего предела
                    {
                        if (t_tmp > 1)
                            return new Segment();
                        t_down = Math.Max(t_down, t_tmp);
                    }
                    else // поиск верхнего предела
                    {
                        if (t_tmp < 0)
                            return new Segment();
                        t_up = Math.Min(t_up, t_tmp);
                    }
                }
            }

            if (t_down > t_up)
                return new Segment();

            return new Segment(l.GetDot(t_down), l.GetDot(t_up));
        }



    }
}
