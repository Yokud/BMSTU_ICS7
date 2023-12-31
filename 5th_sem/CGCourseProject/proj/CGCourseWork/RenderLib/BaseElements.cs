using System;
using System.Collections.Generic;
using System.Numerics;

namespace RenderLib
{
    /// <summary>
    /// Класс вершины
    /// </summary>
    public class Vertex : ICloneable
    {
        /// <summary>
        /// Позиция вершины в мировой системе координат
        /// </summary>
        public Vector3 Position { get; set; }

        /// <summary>
        /// Текстурные координаты
        /// </summary>
        public Vector2 TextureCoords { get; set; }

        /// <summary>
        /// Нормаль вершины
        /// </summary>
        public Vector3 Normal { get; set; }

        /// <summary>
        /// Смежные грани
        /// </summary>
        public List<int> AdjacentPolygons { get; set; }

        public Vertex(float x, float y, float z)
        {
            Position = new Vector3(x, y, z);

            AdjacentPolygons = new List<int>();
        }

        public Vertex(float x, float y, float z, float u, float v) : this(x, y, z)
        {
            TextureCoords = new Vector2(u, v);
        }

        public Vertex(Vector3 pos)
        {
            Position = pos;

            AdjacentPolygons = new List<int>();
        }

        public Vertex(Vector3 pos, Vector2 texcoords)
        {
            Position = pos;
            TextureCoords = texcoords;

            AdjacentPolygons = new List<int>();
        }

        public Vertex(Vector3 pos, Vector2 texcoords, Vector3 norm)
        {
            Position = pos;
            TextureCoords = texcoords;
            Normal = norm;

            AdjacentPolygons = new List<int>();
        }

        public Vertex(Vector3 pos, Vector2 texcoords, Vector3 norm, List<int> adj_pols)
        {
            Position = pos;
            TextureCoords = texcoords;
            Normal = norm;

            AdjacentPolygons = adj_pols;
        }

        public Vertex(Vertex v)
        {
            Position = v.Position;
            TextureCoords = v.TextureCoords;
            Normal = v.Normal;
            AdjacentPolygons = new List<int>();

            foreach (var elem in v.AdjacentPolygons)
                AdjacentPolygons.Add(elem);
        }

        /// <summary>
        /// Перемещение вершины относительно начала координат
        /// </summary>
        /// <param name="dx">Величина перемещения по оси OX</param>
        /// <param name="dy">Величина перемещения по оси OY</param>
        /// <param name="dz">Величина перемещения по оси OZ</param>
        public void Move(float dx, float dy, float dz)
        {
            Position = Position.Move(dx, dy, dz);
        }

        /// <summary>
        /// Масштабирование вершины относительно начала координат
        /// </summary>
        /// <param name="kx">Коэффициент масштабирования по оси OX</param>
        /// <param name="ky">Коэффициент масштабирования по оси OY</param>
        /// <param name="kz">Коэффициент масштабирования по оси OZ</param>
        public void Scale(float kx, float ky, float kz)
        {
            Matrix4x4 matr = new Matrix4x4() { M11 = kx, M22 = ky, M33 = kz, M44 = 1 };
            Position = Position.Transform(matr);
        }

        /// <summary>
        /// Поворот вершины относительно начала координат
        /// </summary>
        /// <param name="angle">Угол поворота</param>
        /// <param name="axis">Ось вращения</param>
        public void Rotate(float angle, Axis axis)
        {
            Position = Position.Rotate(angle, axis);
        }

        /// <summary>
        /// Преобразование вершины и нормали вершины по заданной матрице
        /// </summary>
        /// <param name="matr">Матрица преобразования</param>
        public void Transform(Matrix4x4 matr)
        {
            Position = Position.Transform(matr);
            Normal = Normal.Transform(matr);
        }

        public void Transform(Matrix4x4 matr, out float w)
        {
            Position = Position.Transform(matr, out w);
            Normal = Normal.Transform(matr);
        }

        public object Clone()
        {
            List<int> adj_pols = new List<int>();

            foreach (var elem in AdjacentPolygons)
                adj_pols.Add(elem);

            return new Vertex(Position, TextureCoords, Normal, adj_pols);
        }
    }

    /// <summary>
    /// Класс грани
    /// </summary>
    public class Polygon
    {
        /// <summary>
        /// Номера вершин грани
        /// </summary>
        public int[] Vertices { get; set; }

        public Polygon(int v1, int v2, int v3)
        {
            Vertices = new int[3] { v1, v2, v3 };
        }

        public int this[int index]
        {
            get { return Vertices[index]; }
            set { Vertices[index] = value; }
        }
    }

    /// <summary>
    /// Класс локальной системы координат (ЛСК)
    /// </summary>
    public class Pivot
    {
        /// <summary>
        /// Центр ЛСК в мировой системе координат (МСК)
        /// </summary>
        public Vector3 Center { get; private set; }

        /// <summary>
        /// Ось OX
        /// </summary>
        public Vector3 XAxis { get; set; }
        /// <summary>
        /// Ось OY
        /// </summary>
        public Vector3 YAxis { get; set; }
        /// <summary>
        /// Ось OZ
        /// </summary>
        public Vector3 ZAxis { get; set; }

        /// <summary>
        /// Матрица перевода в ЛСК
        /// </summary>
        public Matrix4x4 LocalCoordsMatrix => new Matrix4x4
            (
                XAxis.X, YAxis.X, ZAxis.X, 0,
                XAxis.Y, YAxis.Y, ZAxis.Y, 0,
                XAxis.Z, YAxis.Z, ZAxis.Z, 0,
                0, 0, 0, 1
            );
        /// <summary>
        /// Матрица перевода в МСК
        /// </summary>
        public Matrix4x4 GlobalCoordsMatrix => new Matrix4x4
            (
                XAxis.X, XAxis.Y, XAxis.Z, 0,
                YAxis.X, YAxis.Y, YAxis.Z, 0,
                ZAxis.X, ZAxis.Y, ZAxis.Z, 0,
                0, 0, 0, 1
            );

        /// <summary>
        /// Длина векторов базиса должна быть равна 1
        /// </summary>
        /// <param name="center"></param>
        /// <param name="xaxis"></param>
        /// <param name="yaxis"></param>
        /// <param name="zaxis"></param>
        public Pivot(Vector3 center, Vector3 xaxis, Vector3 yaxis, Vector3 zaxis)
        {
            Center = center;
            XAxis = xaxis;
            YAxis = yaxis;
            ZAxis = zaxis;
        }

        public Pivot(Pivot p)
        {
            Center = new Vector3(p.Center.X, p.Center.Y, p.Center.Z);
            XAxis = new Vector3(p.XAxis.X, p.XAxis.Y, p.XAxis.Z);
            YAxis = new Vector3(p.YAxis.X, p.YAxis.Y, p.YAxis.Z);
            ZAxis = new Vector3(p.ZAxis.X, p.ZAxis.Y, p.ZAxis.Z);
        }

        /// <summary>
        /// ЛСК со стандартным ортонормированным базисом
        /// </summary>
        /// <param name="center">Положение в МСК</param>
        /// <returns></returns>
        public static Pivot BasePivot(Vector3 center) => new Pivot(center, new Vector3(1, 0, 0), new Vector3(0, 1, 0), new Vector3(0, 0, 1));
        public static Pivot BasePivot(float x, float y, float z) => BasePivot(new Vector3(x, y, z));

        /// <summary>
        /// Перемещение ЛСК относительно начала координат
        /// </summary>
        /// <param name="dx">Величина перемещения по оси OX</param>
        /// <param name="dy">Величина перемещения по оси OY</param>
        /// <param name="dz">Величина перемещения по оси OZ</param>
        public void Move(float dx, float dy, float dz)
        {
            Center = Center.Move(dx, dy, dz);
        }

        /// <summary>
        /// Поворот ЛСК относительно начала координат
        /// </summary>
        /// <param name="angle">Угол поворота</param>
        /// <param name="axis">Ось вращения</param>
        public void Rotate(float angle, Axis axis)
        {
            XAxis = XAxis.Rotate(angle, axis);
            YAxis = YAxis.Rotate(angle, axis);
            ZAxis = ZAxis.Rotate(angle, axis);
        }

        /// <summary>
        /// Поворот ЛСК относительно точки
        /// </summary>
        /// <param name="point">Точка поворота</param>
        /// <param name="angle">Угол поворота</param>
        /// <param name="axis">Ось поворота</param>
        public void RotateAt(Vector3 point, float angle, Axis axis)
        {
            // Создание базиса в точке поворота
            Pivot rotationBasis = BasePivot(point);

            // Перевод ЛСК в ЛСК точки поворота
            Vector3 center = Center - point;
            Vector3 xaxis = center + XAxis;
            Vector3 yaxis = center + YAxis;
            Vector3 zaxis = center + ZAxis;

            // Поворот в ЛСК точки поворота
            center = center.Rotate(angle, axis);
            xaxis = xaxis.Rotate(angle, axis);
            yaxis = yaxis.Rotate(angle, axis);
            zaxis = zaxis.Rotate(angle, axis);

            // Перевод в МСК
            Vector3 newCenter = rotationBasis.ToGlobalCoords(center);
            Vector3 newx = rotationBasis.ToGlobalCoords(xaxis);
            Vector3 newy = rotationBasis.ToGlobalCoords(yaxis);
            Vector3 newz = rotationBasis.ToGlobalCoords(zaxis);

            // Получение новой ЛКС
            Center = newCenter;
            XAxis = newx - Center;
            YAxis = newy - Center;
            ZAxis = newz - Center;
        }

        public void Scale(float kx, float ky, float kz)
        {
            Matrix4x4 matr = new Matrix4x4() { M11 = kx, M22 = ky, M33 = kz, M44 = 1 };
            Center = Center.Transform(matr);
        }

        /// <summary>
        /// Перевод в МСК
        /// </summary>
        /// <param name="local">Точка в ЛСК</param>
        /// <returns></returns>
        public Vector3 ToGlobalCoords(Vector3 local)
        {
            return Vector3.Transform(local, GlobalCoordsMatrix) + Center;
        }

        /// <summary>
        /// Перевод в ЛСК
        /// </summary>
        /// <param name="global">Точка в МСК</param>
        /// <returns></returns>
        public Vector3 ToLocalCoords(Vector3 global)
        {
            return Vector3.Transform(global - Center, LocalCoordsMatrix);
        }
    }

    /// <summary>
    /// Абстрактный класс трёхмерного объекта
    /// </summary>
    public abstract class Object3D
    {
        public Pivot Pivot { get; protected set; }

        public Vector3 Position => Pivot.Center;

        public abstract void Move(float dx, float dy, float dz);
        public abstract void Rotate(float angle, Axis axis);
        public abstract void Scale(float kx, float ky, float kz);
    }
}
