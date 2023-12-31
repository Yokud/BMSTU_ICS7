using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Numerics;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Navigation;
using System.Windows.Shapes;
using HeightMapLib;
using RenderLib;
using System.Threading;
using Emgu.CV;
using Emgu.CV.Aruco;
using Emgu.CV.CvEnum;
using Emgu.CV.Structure;
using Emgu.CV.Util;
using Microsoft.Win32;
using System.Diagnostics;

namespace UI
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        List<Texture> textures;
        Facade fac;
        Vector3 Center;
        public HeightMap Map { get; private set; }
        int visWidth, visHeight;

        double rot_dx = 0, rot_dy = 0, rot_dz = 0;
        private bool dragStarted1 = false;
        private bool dragStarted2 = false;
        private bool dragStarted3 = false;

        CultureInfo ci;
        string hm_info;

        static VideoCapture capture;
        bool captured = false;

        static int markersX = 1;
        static int markersY = 1;
        static int markersLength = 320;
        static int markersSeparation = 10;
        static Dictionary ArucoDict = new Dictionary(Dictionary.PredefinedDictionaryName.Dict4X4_100);
        static GridBoard ArucoBoard = new GridBoard(markersX, markersY, markersLength, markersSeparation, ArucoDict);

        public MainWindow()
        {
            InitializeComponent();

            Center = new Vector3(0, 0, 0);

            textures = new List<Texture>() {
                new Texture(@"D:\Repos\GitHub\CGCourseWork\proj\CGCourseWork\textures\water.jpg"),
                new Texture(@"D:\Repos\GitHub\CGCourseWork\proj\CGCourseWork\textures\sand.jpg"),
                new Texture(@"D:\Repos\GitHub\CGCourseWork\proj\CGCourseWork\textures\grass.jpg"),
                new Texture(@"D:\Repos\GitHub\CGCourseWork\proj\CGCourseWork\textures\rock.jpg"),
                new Texture(@"D:\Repos\GitHub\CGCourseWork\proj\CGCourseWork\textures\snow.jpg")
            };

            ci = (CultureInfo)CultureInfo.CurrentCulture.Clone();
            ci.NumberFormat.CurrencyDecimalSeparator = ".";

            try
            {
                capture = new VideoCapture(0);
                captured = true;
            }
            catch (Exception exc)
            {
                MessageBox.Show(exc.Message);
                Close();
            }
        }

        private void Generate_Click(object sender, RoutedEventArgs e)
        {
            GenMapWindow mapWindow = new GenMapWindow();

            if (mapWindow.ShowDialog() == true)
            {
                int seed = -1, octs = 1;
                if (mapWindow.seed)
                    seed = mapWindow.Seed;

                if (mapWindow.oct)
                    octs = mapWindow.Octaves;

                float lacun = 2f, pers = 0.5f;
                if (mapWindow.lac)
                    lacun = mapWindow.Lacunarity;
                if (mapWindow.pers)
                    pers = mapWindow.Persistence;

                Map = new HeightMap(mapWindow.MapWidth, mapWindow.MapHeight, new PerlinNoise(mapWindow.Scale, octs, lacun, pers, seed));
                StateText.Text = $"Карта высот была сгенерирована с параметрами:\n- Ширина карты высот: {Map.Width}\n- Высота карты высот: {Map.Height}\n- Масштаб: {Map.Scale}\n- Кол-во октав: {Map.Octaves}\n- Лакунарность: {Map.Lacunarity}\n- Стойкость: {Map.Persistence}\n- Ключ генерации: {Map.Seed}";
                hm_info = StateText.Text;
            }
    
        }

        private void ChangeAccept_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                int dx = int.Parse(DeltaX_textbox.Text);
                int dy = int.Parse(DeltaY_textbox.Text);

                fac.MoveTerrain(dx, dy);
            }
            catch (Exception exc)
            {
                MessageBox.Show(exc.Message);
            }
        }

        private void RotateAccept_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                int d_angle = int.Parse(DeltaAngle_textbox.Text);

                fac.RotateTerrain(MathAddon.DegToRad(d_angle), Axis.Z);
            }
            catch (Exception exc)
            {
                MessageBox.Show(exc.Message);
            }
        }

        private void ScaleAccept_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                float kx = float.Parse(ScaleX_textbox.Text, NumberStyles.Any, ci);
                float ky = float.Parse(ScaleY_textbox.Text, NumberStyles.Any, ci);
                float kz = float.Parse(ScaleZ_textbox.Text, NumberStyles.Any, ci);

                fac.ScaleTerrain(kx, ky, kz);
            }
            catch (Exception exc)
            {
                MessageBox.Show(exc.Message);
            }
        }

        private void slValue1_DragStarted(object sender, System.Windows.Controls.Primitives.DragStartedEventArgs e)
        {
            dragStarted1 = true;
        }

        private void slValue1_DragCompleted(object sender, System.Windows.Controls.Primitives.DragCompletedEventArgs e)
        {
            fac.RotateLight(MathAddon.DegToRad((float)(slValue1.Value - rot_dx)), Axis.X);
            rot_dx = slValue1.Value;

            dragStarted1 = false;
        }

        private void slValue2_DragStarted(object sender, System.Windows.Controls.Primitives.DragStartedEventArgs e)
        {
            dragStarted2 = true;
        }

        private void slValue2_DragCompleted(object sender, System.Windows.Controls.Primitives.DragCompletedEventArgs e)
        {
            fac.RotateLight(MathAddon.DegToRad((float)(slValue2.Value - rot_dy)), Axis.Y);
            rot_dy = slValue2.Value;

            dragStarted2 = false;
        }

        private void slValue1_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (!dragStarted1 && RotateLightSourse.IsEnabled)
            {
                fac.RotateLight(MathAddon.DegToRad((float)(slValue1.Value - rot_dx)), Axis.X);
                rot_dx = slValue1.Value;
            }
        }

        private void slValue2_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (!dragStarted2 && RotateLightSourse.IsEnabled)
            {
                fac.RotateLight(MathAddon.DegToRad((float)(slValue2.Value - rot_dy)), Axis.Y);
                rot_dy = slValue2.Value;
            }
        }

        private void slValue3_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            if (!dragStarted3 && RotateLightSourse.IsEnabled)
            {
                fac.RotateLight(MathAddon.DegToRad((float)(slValue3.Value - rot_dz)), Axis.Z);
                rot_dz = slValue3.Value;
            }
        }

        private void slValue3_DragStarted(object sender, System.Windows.Controls.Primitives.DragStartedEventArgs e)
        {
            dragStarted3 = true;
        }

        private void slValue3_DragCompleted(object sender, System.Windows.Controls.Primitives.DragCompletedEventArgs e)
        {
            fac.RotateLight(MathAddon.DegToRad((float)(slValue3.Value - rot_dz)), Axis.Z);
            rot_dz = slValue3.Value;

            dragStarted3 = false;
        }

        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            captured = false;
            capture.Dispose();
        }

        private void CreateLand_Click(object sender, RoutedEventArgs e)
        {
            SetLimitWindow limWindow = new SetLimitWindow();

            limWindow.Owner = this;

            if (limWindow.ShowDialog() == true)
            {
                visWidth = limWindow.VisWidth;
                visHeight = limWindow.VisHeight;
                StateText.Text = hm_info + $"\n- Ширина видимой части: {visWidth}\n- Высота видимой части: {visHeight}";


                Camera cam = new Camera(Pivot.BasePivot(0, 0, 0), 640, 480, 150, 100000);

                DirectionalLight light = new DirectionalLight(Pivot.BasePivot(0, 700, 0), new Vector3(0, -1, 0));

                Terrain terr = new Terrain(Map, visWidth, visHeight, textures);

                Scene scene = new Scene(terr, cam, light);
                Drawer draw = new Drawer(cam.ScreenWidth, cam.ScreenHeight);
                fac = new Facade(scene, draw);
                fac.RotateLight(MathAddon.DegToRad((float)slValue1.Value), Axis.X);
                fac.RotateLight(MathAddon.DegToRad((float)slValue2.Value), Axis.Y);
                fac.RotateLight(MathAddon.DegToRad((float)slValue3.Value), Axis.Z);
                rot_dx = slValue1.Value;
                rot_dy = slValue2.Value;
                rot_dz = slValue3.Value;

                ChangeTerrainView.IsEnabled = true;
                RotateTerrainView.IsEnabled = true;
                ScaleTerrainView.IsEnabled = true;
                RotateLightSourse.IsEnabled = true;

                Capturing();
            }
        }

        private void GetMarker_Click(object sender, RoutedEventArgs e)
        {
            SaveFileDialog saveFileDialog1 = new SaveFileDialog();
            saveFileDialog1.Filter = "Jpeg Image|*.jpg|Bitmap Image|*.bmp|Png Image|*.png";
            saveFileDialog1.Title = "Сохранение файла с изображением маркера";
            saveFileDialog1.ShowDialog();

            if (!string.IsNullOrEmpty(saveFileDialog1.FileName) && !string.IsNullOrWhiteSpace(saveFileDialog1.FileName))
                PrintArucoBoard(ArucoBoard, saveFileDialog1.FileName, markersX, markersY, markersLength, markersSeparation);
        }

        static void PrintArucoBoard(GridBoard ArucoBoard, string path, int markersX = 1, int markersY = 1, int markersLength = 80, int markersSeparation = 30)
        {
            int borderBits = 1;

            System.Drawing.Size imageSize = new System.Drawing.Size();
            Mat boardImage = new Mat();
            imageSize.Width = markersX * (markersLength + markersSeparation) - markersSeparation + 2 * markersSeparation;
            imageSize.Height = markersY * (markersLength + markersSeparation) - markersSeparation + 2 * markersSeparation;
            ArucoBoard.Draw(imageSize, boardImage, markersSeparation, borderBits);

            var img = boardImage.ToBitmap();
            img.Save(path);
        }

        void Capturing()
        {
            DetectorParameters ArucoParameters = DetectorParameters.GetDefault();

            string cameraConfigurationFile = @"D:\Repos\GitHub\CGCourseWork\proj\CGCourseWork\cameraParameters.xml";
            FileStorage fs = new FileStorage(cameraConfigurationFile, FileStorage.Mode.Read);

            if (!fs.IsOpened)
                throw new Exception("Could not open configuration file " + cameraConfigurationFile);


            Mat cameraMatrix = new Mat(new System.Drawing.Size(3, 3), DepthType.Cv32F, 1);
            Mat distortionMatrix = new Mat(1, 8, DepthType.Cv32F, 1);
            fs["cameraMatrix"].ReadMat(cameraMatrix);
            fs["dist_coeffs"].ReadMat(distortionMatrix);

            while (captured)
            {
                Mat frame = new Mat();
                frame = capture.QueryFrame();

                if (!frame.IsEmpty)
                {
                    VectorOfInt ids = new VectorOfInt(); // name/id of the detected markers
                    VectorOfVectorOfPointF corners = new VectorOfVectorOfPointF(); // corners of the detected marker
                    VectorOfVectorOfPointF rejected = new VectorOfVectorOfPointF(); // rejected contours
                    ArucoInvoke.DetectMarkers(frame, ArucoDict, corners, ids, ArucoParameters, rejected);

                    // If we detected at least one marker
                    if (ids.Size != 0)
                    {
                        ArucoInvoke.DrawDetectedMarkers(frame, corners, ids, new MCvScalar(255, 0, 255));

                        Mat rvecs = new Mat(); // rotation vector
                        Mat tvecs = new Mat(); // translation vector
                        ArucoInvoke.EstimatePoseSingleMarkers(corners, markersLength, cameraMatrix, distortionMatrix, rvecs, tvecs);

                        Mat rvecMat = rvecs.Row(0);
                        Mat tvecMat = tvecs.Row(0);
                        VectorOfDouble rvec = new VectorOfDouble();
                        VectorOfDouble tvec = new VectorOfDouble();
                        
                        double[] values = new double[3];
                        rvecMat.CopyTo(values);
                        rvec.Push(values);
                        tvecMat.CopyTo(values);
                        tvec.Push(values);
                        //ArucoInvoke.DrawAxis(frame,
                        //                        cameraMatrix,
                        //                        distortionMatrix,
                        //                        rvec,
                        //                        tvec,
                        //                        markersLength * 0.5f);

                        Matrix4x4 rot = GetRotMatFromRotVec(rvec).ToMatrix4x4();
                        Vector4 t = new Vector4((float)tvec[0], (float)tvec[1], (float)tvec[2], 1);

                        Vector3 x_a = new Vector3(rot.M11, rot.M12, rot.M13);
                        Vector3 y_a = new Vector3(rot.M21, rot.M22, rot.M23);
                        Vector3 z_a = new Vector3(rot.M31, rot.M32, rot.M33);

                        Vector3 pos = new Vector3(t.X, -t.Y, -t.Z);

                        fac.SetCamera(pos, x_a, -y_a, -z_a);

                        //Stopwatch sw = Stopwatch.StartNew();
                        FastBitmap land_frame = fac.DrawScene((bool)WithShadows.IsChecked);
                        //sw.Stop();
                        //Console.WriteLine($"Время рендера (мс) (тени: {(bool)WithShadows.IsChecked}): {sw.ElapsedMilliseconds}");

                        MainFrame.Source = CVAddon.ConcatTwoImages(frame.ToImage<Rgba, byte>().ToBitmap(), land_frame.Bitmap).ToBitmapImage();
                    }
                    else
                        MainFrame.Source = frame.ToImage<Rgba, byte>().ToBitmap().ToBitmapImage();
     
                    CvInvoke.WaitKey(24);
                }
            }
        }

        Mat GetRotMatFromRotVec(VectorOfDouble rvec)
        {
            Mat rmat = new Mat();
            CvInvoke.Rodrigues(rvec, rmat);

            return rmat;
        }
    }
}
