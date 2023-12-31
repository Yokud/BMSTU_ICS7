using System;
using System.Collections.Generic;
using System.Numerics;

namespace RenderLib
{
    public class Camera : Object3D
    {
        public int ScreenWidth { get; private set; }
        public int ScreenHeight { get; private set; }

        public float ScreenNearDist { get; private set; }
        public float ScreenFarDist { get; private set; }

        public float FocalLength { get; private set; }

        private static double fov = Math.PI / 2;
        private float r, t, tg_fov = (float)Math.Tan(fov / 2);

        public Camera(Pivot p, int width, int height, float near_dist, float far_dist)
        {
            Pivot = p;
            ScreenWidth = width;
            ScreenHeight = height;
            ScreenNearDist = near_dist;
            ScreenFarDist = far_dist;

            FocalLength = width;

            t = ScreenNearDist * tg_fov;
            r = t * ((float)ScreenWidth / ScreenHeight);
        }

        public Camera(Pivot p, int width, int height, float focal_length)
        {
            Pivot = p;
            ScreenWidth = width;
            ScreenHeight = height;
            FocalLength = focal_length;
        }

        public Matrix4x4 PerspectiveClip => new Matrix4x4
        (
            ScreenNearDist / r, 0, 0, 0,
            0, ScreenNearDist / t, 0, 0,
            0, 0, (ScreenFarDist + ScreenNearDist) / (ScreenNearDist - ScreenFarDist), -1f,
            0, 0, 2f * ScreenNearDist * ScreenFarDist / (ScreenNearDist - ScreenFarDist), 0
        );

        public Matrix4x4 PerspectiveClipCV => new Matrix4x4
        (
            FocalLength / (ScreenWidth / 2f), 0, 0, 0,
            0, -FocalLength / (ScreenHeight / 2f), 0, 0,
            0, 0, (ScreenFarDist + ScreenNearDist) / (ScreenNearDist - ScreenFarDist), -1f,
            0, 0, 2f * ScreenNearDist * ScreenFarDist / (ScreenNearDist - ScreenFarDist), 0
        );

        public bool IsVisible(Vector3 p)
        {
            float min = -1, max = 1;

            return min <= p.X && p.X <= max && min <= p.Y && p.Y <= max && min <= p.Z && p.Z <= max;
        }

        public bool IsVisible(Vertex v)
        {
            return IsVisible(v.Position);
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
            Pivot.Scale(kx, ky, kz);
        }

        public void MoveTo(Vector3 p)
        {
            Pivot = new Pivot(p, Pivot.XAxis, Pivot.YAxis, Pivot.ZAxis);
        }

        public void RotateTo(Vector3 xa, Vector3 ya, Vector3 za)
        {
            Pivot.XAxis = xa;
            Pivot.YAxis = ya;
            Pivot.ZAxis = za;
        }

        public void RotateAt(Vector3 p, float angle, Axis axis)
        {
            Pivot.RotateAt(p, angle, axis);
        }

        public Vector2 ToScreenSpace(Vector3 p)
        {
            float x = (ScreenWidth - 1) * 0.5f * (1 + p.X);
            float y = (ScreenHeight - 1) * (1 - 0.5f * (1 + p.Y));

            return new Vector2(MathAddon.RoundToInt(x), MathAddon.RoundToInt(y));
        }
    }
}
