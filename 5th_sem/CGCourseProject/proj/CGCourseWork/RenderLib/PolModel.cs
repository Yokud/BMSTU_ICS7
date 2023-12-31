using System;
using System.Collections.Generic;
using System.Numerics;
using System.Drawing;

namespace RenderLib
{
    public class PolModel : Object3D, ICloneable
    {
        public List<Vertex> Vertices { get; protected set; }
        public List<Polygon> Polygons { get; protected set; }
        public List<Vector3> Normals { get; protected set; }
        public Texture Texture { get; protected set; }

        public static readonly Color DefaultTexture = Color.Red;


        public PolModel()
        {
            Vertices = new List<Vertex>();
            Polygons = new List<Polygon>();
            Normals = new List<Vector3>();
            Texture = new Texture();
            Pivot = Pivot.BasePivot(0, 0, 0);
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="verts">Координаты вершин в пространстве модели</param>
        /// <param name="pols"></param>
        /// <param name="texture"></param>
        /// <param name="p"></param>
        public PolModel(List<Vertex> verts, List<Polygon> pols, Texture texture, Pivot p)
        {
            Vertices = verts;
            Polygons = pols;
            Texture = texture;
            Pivot = p;

            Normals = new List<Vector3>();

            RecalcProcs();
        }

        public PolModel(List<Vertex> verts, List<Polygon> pols, Pivot p) : this(verts, pols, new Texture(), p)
        {

        }

        public override void Move(float dx, float dy, float dz)
        {
            Pivot.Move(dx, dy, dz);
        }

        public override void Rotate(float angle, Axis axis)
        {
            Pivot.Rotate(angle, axis);
        }

        public override void Scale(float kx, float ky, float kz)
        {
            foreach (var v in Vertices)
                v.Scale(kx, ky, kz);
        }

        protected void RecalcProcs()
        {
            RecalcNormals();
            RecalcAdjPols();
            RecalcVertexNormals();
        }

        protected void RecalcNormals()
        {
            Normals.Clear();
            foreach (var pol in Polygons)
            {
                Vector3 a = Vertices[pol.Vertices[2]].Position - Vertices[pol.Vertices[0]].Position;
                Vector3 b = Vertices[pol.Vertices[1]].Position - Vertices[pol.Vertices[0]].Position;

                Normals.Add(Vector3.Normalize(Vector3.Cross(a, b)));
            }
        }

        protected void RecalcAdjPols()
        {
            for (int i = 0; i < Vertices.Count; i++)
            {
                Vertices[i].AdjacentPolygons.Clear();
                for (int j = 0; j < Polygons.Count; j++)
                    if (Polygons[j].Vertices[0] == i || Polygons[j].Vertices[1] == i || Polygons[j].Vertices[2] == i)
                        Vertices[i].AdjacentPolygons.Add(j);
            }
        }

        protected void RecalcVertexNormals()
        {
            foreach (var v in Vertices)
            {
                Vector3 sum_norms = new Vector3(0, 0, 0);

                foreach (var ap in v.AdjacentPolygons)
                    sum_norms += GetPolNormal(Polygons[ap]);

                v.Normal = sum_norms / v.AdjacentPolygons.Count;
            }
        }

        public object Clone()
        {
            return new PolModel(Vertices, Polygons, Texture, Pivot);
        }

        public Vertex GetPolVertex(Polygon pol, int vert_num)
        {
            if (vert_num > -1 && vert_num < 3)
                return Vertices[pol[vert_num]];
            else
                throw new Exception("Недопустимый номер вершины!\n");
        }

        public Vertex[] GetPolVertices(Polygon pol)
        {
            return new Vertex[] { GetPolVertex(pol, 0), GetPolVertex(pol, 1), GetPolVertex(pol, 2) };
        }

        public Vector3 GetPolNormal(Polygon pol)
        {
            int index = Polygons.IndexOf(pol);

            return Normals[index];
        }

        public Matrix4x4 ToModelMatrix => Pivot.LocalCoordsMatrix;

        public Matrix4x4 ToWorldMatrix => Pivot.GlobalCoordsMatrix;
    }
}
