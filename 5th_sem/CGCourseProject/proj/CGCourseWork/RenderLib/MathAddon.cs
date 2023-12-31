using System;
using System.Numerics;
using System.Drawing;

namespace RenderLib
{
    public enum Axis { X, Y, Z }

    public static class MathAddon
    {
        /// <summary>
        /// Поворот вектора
        /// </summary>
        /// <param name="v"></param>
        /// <param name="angle">Угол поворота</param>
        /// <param name="axis">Ось поворота</param>
        public static Vector3 Rotate(this Vector3 v, float angle, Axis axis)
        {
            Matrix4x4 rotation = axis == Axis.X ? Matrix4x4.CreateRotationX(angle) : axis == Axis.Y ? Matrix4x4.CreateRotationY(angle) : Matrix4x4.CreateRotationZ(angle);
            return v.Transform(rotation);
        }

        /// <summary>
        /// Проекция первого вектора на второй
        /// </summary>
        /// <param name="v1"></param>
        /// <param name="v2"></param>
        /// <returns></returns>
        public static Vector3 Proection(Vector3 v1, Vector3 v2)
        {
            return Vector3.Dot(v1, v2) / Vector3.Dot(v2, v2) * v2;
        }

        /// <summary>
        /// Перемещение
        /// </summary>
        /// <param name="v"></param>
        /// <param name="dx"></param>
        /// <param name="dy"></param>
        /// <param name="dz"></param>
        public static Vector3 Move(this Vector3 v, float dx, float dy, float dz)
        {
            return v + new Vector3(dx, dy, dz);
        }

        /// <summary>
        /// Преобразование по матрице
        /// </summary>
        /// <param name="v"></param>
        /// <param name="matrix4X4">Матрица преобразования</param>
        public static Vector3 Transform(this Vector3 v, Matrix4x4 matrix4X4)
        {
            Vector4 new_v = Vector4.Transform(v.ToVec4(), matrix4X4);
            return new_v.FromVec4();
        }

        public static Vector3 Transform(this Vector3 v, Matrix4x4 matrix4X4, out float w)
        {
            Vector4 new_v = Vector4.Transform(v.ToVec4(), matrix4X4);
            w = new_v.W;
            return new_v.FromVec4();
        }

        /// <summary>
        /// Перевод в однородную систему координат
        /// </summary>
        /// <param name="v"></param>
        /// <param name="w"></param>
        /// <returns></returns>
        public static Vector4 ToVec4(this Vector3 v, float w = 1f)
        {
            return new Vector4(v.X, v.Y, v.Z, w);
        }

        /// <summary>
        /// Перевод из однородной системы координат
        /// </summary>
        /// <param name="v"></param>
        /// <returns></returns>
        public static Vector3 FromVec4(this Vector4 v)
        {
            return new Vector3(v.X / v.W, v.Y / v.W, v.Z / v.W);
        }

        public static Point ToPoint(this Vector2 v)
        {
            return new Point((int)v.X, (int)v.Y);
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

        public static Vector3 Baricentric(Point a, Point b, Point c, Point p, out float det_res)
        {
            Vector3 bar = new Vector3();

            float det = (b.Y - c.Y) * (a.X - c.X) + (c.X - b.X) * (a.Y - c.Y);
            det_res = det;
            bar.X = ((b.Y - c.Y) * (p.X - c.X) + (c.X - b.X) * (p.Y - c.Y)) / det;
            bar.Y = ((c.Y - a.Y) * (p.X - c.X) + (a.X - c.X) * (p.Y - c.Y)) / det;
            bar.Z = 1 - bar.X - bar.Y;

            return bar;
        }

        public static float InBaricentric(Vector3 bar, float v1, float v2, float v3)
        {
            return bar.X * v1 + bar.Y * v2 + bar.Z * v3;
        }

        public static Vector2 InBaricentric(Vector3 bar, Vector2 v1, Vector2 v2, Vector2 v3)
        {
            return bar.X * v1 + bar.Y * v2 + bar.Z * v3;
        }

        public static float DegToRad(float deg)
        {
            return deg * (float)Math.PI / 180f;
        }
    }
}