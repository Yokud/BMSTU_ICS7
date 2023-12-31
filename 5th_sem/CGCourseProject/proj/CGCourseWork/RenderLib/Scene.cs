using System.Collections.Generic;
using System.Numerics;

namespace RenderLib
{
    public class Scene
    {
        public Camera Camera { get; private set; }
        public Terrain Terrain { get; private set; }
        public DirectionalLight LightSource { get; private set; }

        public Scene(Terrain terr, Camera cam, DirectionalLight light)
        {
            Terrain = terr;
            Camera = cam;
            LightSource = light;
        }

        public List<Object3D> Objects => new List<Object3D>() { Terrain.VisibleTerrainModel, Camera, LightSource };


        public void RotateTerrain(float angle, Axis axis)
        {
            Terrain.Rotate(angle, axis);
        }

        public void ScaleTerrain(float kx, float ky, float kz)
        {
            Terrain.Scale(kx, ky, kz);
        }

        public void MoveTerrainLimits(int dx, int dz)
        {
            Terrain.Move(dx, dz);
        }

        public void RotateLight(float angle, Axis axis)
        {
            LightSource.RotateAt(Terrain.VisibleTerrainModel.Pivot.Center, angle, axis);
        }

        public void SetCamera(Vector3 pos, Vector3 x_a, Vector3 y_a, Vector3 z_a)
        {
            Camera.MoveTo(pos);
            Camera.RotateTo(x_a, y_a, z_a);
        }
    }
}
