using Emgu.CV;
using System.Numerics;

namespace RenderLib
{
    public class Facade
    {
        Scene Scene { get; set; }
        Drawer Drawer { get; set; }

        public Facade(Scene scene, Drawer drawer)
        {
            Scene = scene;
            Drawer = drawer;
        }

        public FastBitmap DrawScene(bool shadows = true)
        {
            Drawer.DrawScene(Scene, shadows);
            return (FastBitmap)Drawer.FrameBuffer.Clone();
        }

        public void RotateTerrain(float angle, Axis axis)
        {
            Scene.RotateTerrain(angle, axis);
        }

        public void ScaleTerrain(float kx, float ky, float kz)
        {
            Scene.ScaleTerrain(kx, ky, kz);
        }

        public void MoveTerrain(int dx, int dz)
        {
            Scene.MoveTerrainLimits(dx, dz);
        }

        public void RotateLight(float angle, Axis axis)
        {
            Scene.RotateLight(angle, axis);
        }

        public void SetCamera(Vector3 pos, Vector3 x_a, Vector3 y_a, Vector3 z_a)
        {
            Scene.SetCamera(pos, x_a, y_a, z_a);
        }
    }
}
