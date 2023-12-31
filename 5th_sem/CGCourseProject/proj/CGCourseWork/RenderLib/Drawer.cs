using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using System.Numerics;
using System.Drawing;

namespace RenderLib
{
    public enum DrawerMode 
    { 
        GL, 
        CV 
    }

    public class Drawer
    {
        int width, height;
        public FastBitmap FrameBuffer { get; private set; }
        public float[,] DepthBuffer { get; private set; }
        public float[,] ShadowBuffer { get; private set; }

        DrawerMode mode;

        public Drawer(int width, int height, DrawerMode mode = DrawerMode.CV)
        {
            this.width = width;
            this.height = height;
            FrameBuffer = new FastBitmap(width, height);
            DepthBuffer = new float[width, height];
            ShadowBuffer = new float[width, height];

            this.mode = mode;
        }

        public void DrawScene(Scene scene, bool shadows = true)
        {
            if (shadows)
            {
                // Создание теневой карты
                Drawer shadow_drawer = new Drawer(width, height, DrawerMode.GL);
                Camera light_camera = new Camera(new Pivot(scene.LightSource.Pivot), scene.Camera.ScreenWidth, scene.Camera.ScreenHeight, scene.Camera.ScreenNearDist, scene.Camera.ScreenFarDist);

                Vector3 temp = light_camera.Pivot.YAxis;
                light_camera.Pivot.YAxis = light_camera.Pivot.ZAxis;
                light_camera.Pivot.ZAxis = temp;

                shadow_drawer.DrawScene(new Scene(scene.Terrain, light_camera, scene.LightSource), false);
                ShadowBuffer = (float[,])shadow_drawer.DepthBuffer.Clone();
            }

            var pols = VerticesShading(scene);
            PixelShading(pols, scene.LightSource);
            ZBufferShadow(pols, scene.Camera, scene.LightSource, shadows);
        }

        private List<PolygonInfo> VerticesShading(Scene scene)
        {
            Matrix4x4 model_view_matr = new Matrix4x4();


            if (mode == DrawerMode.GL)
            {
                Matrix4x4 matr_move = Matrix4x4.CreateTranslation(scene.Terrain.VisibleTerrainModel.Position - scene.Camera.Position);
                model_view_matr = scene.Terrain.VisibleTerrainModel.ToWorldMatrix * matr_move * scene.Camera.Pivot.LocalCoordsMatrix;
            }
            else if (mode == DrawerMode.CV)
            {
                Matrix4x4 to_camera = scene.Camera.Pivot.LocalCoordsMatrix;

                to_camera.M41 = scene.Camera.Position.X;
                to_camera.M42 = scene.Camera.Position.Y;
                to_camera.M43 = scene.Camera.Position.Z;

                model_view_matr = scene.Terrain.VisibleTerrainModel.ToWorldMatrix * Matrix4x4.CreateTranslation(scene.Terrain.VisibleTerrainModel.Position) * to_camera;
            }

            var vertices = scene.Terrain.VisibleTerrainModel.Vertices.Clone();
            List<PolygonInfo> visible_pols = new List<PolygonInfo>();
            List<float> ws = new List<float>();
            List<float> light_levels = new List<float>();

            Vector3 light_dir = Vector3.Normalize((-scene.LightSource.LightDirection).Transform(scene.LightSource.Pivot.GlobalCoordsMatrix));

            foreach (var v in vertices)
            {
                Vector3 v_norm = Vector3.Normalize(v.Normal.Transform(scene.Terrain.VisibleTerrainModel.Pivot.GlobalCoordsMatrix));

                float light_level = scene.LightSource.GetAngleIntensity(v_norm, light_dir); 

                v.Transform(model_view_matr, out float w);
                ws.Add(w);
                light_levels.Add(light_level);
            }

            Matrix4x4 perspective_clip = mode == DrawerMode.GL ? scene.Camera.PerspectiveClip : scene.Camera.PerspectiveClipCV;

            foreach (var pol in scene.Terrain.VisibleTerrainModel.Polygons)
            {
                Vertex[] v_persp = new Vertex[3];
                for (int i = 0; i < 3; i++)
                {
                    v_persp[i] = new Vertex(vertices[pol[i]]);
                    v_persp[i].Transform(perspective_clip);
                }

                if (scene.Camera.IsVisible(v_persp[0]) && scene.Camera.IsVisible(v_persp[1]) && scene.Camera.IsVisible(v_persp[2]))
                {
                    visible_pols.Add(new PolygonInfo((Vertex)vertices[pol[0]].Clone(), (Vertex)vertices[pol[1]].Clone(), (Vertex)vertices[pol[2]].Clone(),
                                        scene.Terrain.VisibleTerrainModel.GetPolNormal(pol).Transform(model_view_matr)));

                    var last_pol = visible_pols[visible_pols.Count - 1];
                    for (int i = 0; i < 3; i++)
                    {
                        last_pol.Ws[i] = ws[pol[i]];
                        last_pol.LightLevelsOnVertices[i] = light_levels[pol[i]];

                        last_pol.ScreenVertices[i] = new FragmentInfo(last_pol.Vertices[i].Position, last_pol.Ws[i])
                        {
                            ScreenPos = scene.Camera.ToScreenSpace(v_persp[i].Position),
                            TextureCoords = last_pol.Vertices[i].TextureCoords,
                            Intensity = last_pol.LightLevelsOnVertices[i]
                        };
                    }

                    last_pol.Texture = scene.Terrain.VisibleTerrainModel.GetTexture(pol);
                }
            }

            return visible_pols;
        }

        private void PixelShading(List<PolygonInfo> pols, Light light)
        {
            foreach (var pol in pols)
            {
                var first = pol.ScreenVertices[0];
                var second = pol.ScreenVertices[1];
                var third = pol.ScreenVertices[2];

                List<Point> outline_points = new List<Point>();

                for (int i = 0; i < 3; i++)
                {
                    var line = Brezenhem((int)pol.ScreenVertices[i % 3].ScreenPos.X, (int)pol.ScreenVertices[i % 3].ScreenPos.Y, 
                                            (int)pol.ScreenVertices[(i + 1) % 3].ScreenPos.X, (int)pol.ScreenVertices[(i + 1) % 3].ScreenPos.Y);
                    outline_points.AddRange(line);
                }
                
                var outline_segs = ClusterizeByY(outline_points);

                foreach (var seg in outline_segs)
                {
                    int yi = seg.Key;
                    int x1 = seg.Value.MinX, x2 = seg.Value.MaxX;

                    // Положение пикселя внутри проекции полигона на экран
                    float det;
                    Vector3 bar_p1 = MathAddon.Baricentric(first.ScreenPos.ToPoint(), second.ScreenPos.ToPoint(), third.ScreenPos.ToPoint(), new Point(x1, yi), out det);
                    Vector3 bar_p2 = MathAddon.Baricentric(first.ScreenPos.ToPoint(), second.ScreenPos.ToPoint(), third.ScreenPos.ToPoint(), new Point(x2, yi), out det);

                    // Полигон проецируется в отрезок на экран
                    if (MathAddon.IsEqual(det, 0))
                        break;

                    // Перспективно-корректное текстурирование
                    float w_11 = MathAddon.InBaricentric(bar_p1, 1f / first.W, 1f / second.W, 1f / third.W);
                    float w_12 = MathAddon.InBaricentric(bar_p2, 1f / first.W, 1f / second.W, 1f / third.W);

                    Vector2 uv_w1 = MathAddon.InBaricentric(bar_p1, first.TextureCoords / first.W, second.TextureCoords / second.W, third.TextureCoords / third.W);
                    Vector2 uv_w2 = MathAddon.InBaricentric(bar_p2, first.TextureCoords / first.W, second.TextureCoords / second.W, third.TextureCoords / third.W);

                    float dw_1 = (w_12 - w_11) / (x2 - x1 + 1);
                    Vector2 d_uv_w = (uv_w2 - uv_w1) / (x2 - x1 + 1);

                    Vector2 uv_w = uv_w1;
                    float w_1 = w_11;


                    // Закраска Гуро
                    float I1 = MathAddon.InBaricentric(bar_p1, first.Intensity, second.Intensity, third.Intensity);
                    float I2 = MathAddon.InBaricentric(bar_p2, first.Intensity, second.Intensity, third.Intensity);

                    float dI = (I2 - I1) / (x2 - x1 + 1);
                    float I_start = I1;


                    // Координаты в пространстве обзора
                    float x_start = MathAddon.InBaricentric(bar_p1, first.Position.X, second.Position.X, third.Position.X);
                    float x_end = MathAddon.InBaricentric(bar_p2, first.Position.X, second.Position.X, third.Position.X);
                    float dx = (x_end - x_start) / (x2 - x1 + 1);
                    float x_i = x_start;

                    float y_start = MathAddon.InBaricentric(bar_p1, first.Position.Y, second.Position.Y, third.Position.Y);
                    float y_end = MathAddon.InBaricentric(bar_p2, first.Position.Y, second.Position.Y, third.Position.Y);
                    float dy = (y_end - y_start) / (x2 - x1 + 1);
                    float y_i = y_start;

                    float z_start = MathAddon.InBaricentric(bar_p1, first.Position.Z, second.Position.Z, third.Position.Z);
                    float z_end = MathAddon.InBaricentric(bar_p2, first.Position.Z, second.Position.Z, third.Position.Z);
                    float dz = (z_end - z_start) / (x2 - x1 + 1);
                    float z_i = z_start;

                    for (int xi = x1; xi <= x2; xi++)
                    {
                        Color texel = pol.Texture.GetTexel(uv_w.X / w_1, uv_w.Y / w_1);

                        pol.Pixels.Add(new FragmentInfo(x_i, y_i, z_i, 1f / w_1, xi, yi, light.GetColorByIntensity(texel, I_start)));

                        uv_w += d_uv_w;
                        w_1 += dw_1;
                        I_start += dI;
                        z_i += dz;
                        x_i += dx;
                        y_i += dy;
                    }
                }
            }
        }

        private void ZBufferShadow(List<PolygonInfo> pols, Camera cam, DirectionalLight light, bool shadows = true)
        {
            // Очистка буферов
            FrameBuffer.Clear();
            for (int i = 0; i < width; i++)
                for (int j = 0; j < height; j++)
                    DepthBuffer[i, j] = float.PositiveInfinity;

            Camera shadow_camera = null;
            Matrix4x4 cam_to_light_matr = Matrix4x4.Identity;
            if (shadows)
            {
                shadow_camera = new Camera(new Pivot(light.Pivot), cam.ScreenWidth, cam.ScreenHeight, cam.ScreenNearDist, cam.ScreenFarDist);
                
                Vector3 temp = shadow_camera.Pivot.YAxis;
                shadow_camera.Pivot.YAxis = shadow_camera.Pivot.ZAxis;
                shadow_camera.Pivot.ZAxis = temp;

                Matrix4x4 from_cv_cam = cam.Pivot.LocalCoordsMatrix;
                from_cv_cam.M41 = cam.Position.X;
                from_cv_cam.M42 = cam.Position.Y;
                from_cv_cam.M43 = cam.Position.Z;

                Matrix4x4.Invert(from_cv_cam, out from_cv_cam);

                cam_to_light_matr = from_cv_cam * Matrix4x4.CreateTranslation(-shadow_camera.Pivot.Center) * shadow_camera.Pivot.LocalCoordsMatrix;
            }

            Parallel.ForEach(pols, p => 
            {
                foreach (var pixel in p.Pixels)
                {
                    if (pixel.Position.Z < DepthBuffer[(int)pixel.ScreenPos.X, (int)pixel.ScreenPos.Y])
                    {
                        DepthBuffer[(int)pixel.ScreenPos.X, (int)pixel.ScreenPos.Y] = pixel.Position.Z;

                        if (shadows)
                        {
                            var pixel_loc = Vector3.Transform(pixel.Position, cam_to_light_matr);
                            var pixel_persp = pixel_loc.Transform(shadow_camera.PerspectiveClip);
                            var scr_proj = shadow_camera.ToScreenSpace(pixel_persp).ToPoint();

                            if (scr_proj.X < 0 || scr_proj.X >= width || scr_proj.Y < 0 || scr_proj.Y >= height)
                                pixel.Color = light.GetColorByIntensity(pixel.Color, 0.7f);
                            else if (pixel_loc.Z > ShadowBuffer[scr_proj.X, scr_proj.Y] + 3f || ShadowBuffer[scr_proj.X, scr_proj.Y] == float.PositiveInfinity)
                                pixel.Color = light.GetColorByIntensity(pixel.Color, 0.7f);
                        }

                        FrameBuffer.SetPixel((int)pixel.ScreenPos.X, (int)pixel.ScreenPos.Y, pixel.Color);
                    }
                }
            });
        }

        private List<Point> Brezenhem(int x_start, int y_start, int x_end, int y_end)
        {
            List<Point> points = new List<Point>();

            bool swap_f;
            int dx = x_end - x_start, dy = y_end - y_start;
            int sx = Math.Sign(dx), sy = Math.Sign(dy);

            dx = Math.Abs(dx);
            dy = Math.Abs(dy);

            if (swap_f = dy > dx)
                SystemAddon.Swap(ref dx, ref dy);

            int error = 2 * dy - dx;
            int x = x_start, y = y_start;
            for (int i = 0; i <= dx; i++)
            {
                points.Add(new Point(x, y));
                if (error >= 0)
                {
                    if (swap_f)
                        x += sx;
                    else
                        y += sy;
                    error -= 2 * dx;
                }

                if (swap_f)
                    y += sy;
                else
                    x += sx;

                error += 2 * dy;
            }

            return points;
        }

        private Dictionary<int, SegmentX> ClusterizeByY(List<Point> points)
        {
            Dictionary<int, SegmentX> outline = new Dictionary<int, SegmentX>();

            foreach (var point in points)
            { 
                if (!outline.ContainsKey(point.Y))
                    outline.Add(point.Y, new SegmentX(point.X, point.X));
                else
                {
                    outline[point.Y].MinX = Math.Min(outline[point.Y].MinX, point.X);
                    outline[point.Y].MaxX = Math.Max(outline[point.Y].MaxX, point.X);
                }
            }

            return outline;
        }

        class SegmentX
        {
            public int MinX { get; set; }
            public int MaxX { get; set; }

            public SegmentX(int x_min, int x_max)
            {
                MinX = x_min;
                MaxX = x_max;
            }
        }
    }

    /// <summary>
    /// Класс для описания промежуточных данных при обработке полигонов для получения конечного изображения
    /// </summary>
    class PolygonInfo
    {
        public Vertex[] Vertices { get; set; }
        public Vector3 Normal { get; set; }
        public float[] LightLevelsOnVertices { get; set; }
        public float[] Ws { get; set; } // Четвёртая координата каждой вершины
        public FragmentInfo[] ScreenVertices { get; set; }
        public List<FragmentInfo> Pixels { get; set; }

        public Texture Texture { get; set; }

        public PolygonInfo(Vertex v1, Vertex v2, Vertex v3, Vector3 norm)
        {
            Vertices = new Vertex[] { v1, v2, v3 };
            Normal = norm;
            LightLevelsOnVertices = new float[3];
            Ws = new float[3];
            Pixels = new List<FragmentInfo>();
            ScreenVertices = new FragmentInfo[3];
        }
    }


    /// <summary>
    /// Класс для описания точки в экранных координатах и её глубины
    /// </summary>
    class FragmentInfo
    {
        public Vector3 Position { get; set; }
        public float W;
        public Vector2 ScreenPos { get; set; }
        public Vector2 TextureCoords { get; set; }
        public Color Color { get; set; }
        public float Intensity { get; set; }

        public FragmentInfo(Vector3 v, float w)
        {
            Position = v;
            W = w;
        }

        public FragmentInfo(float x, float y, float z, float w, int scr_x, int scr_y, Color c)
        {
            Position = new Vector3(x, y, z);
            W = w;
            ScreenPos = new Vector2(scr_x, scr_y);
            Color = c;
        }
    }
}
