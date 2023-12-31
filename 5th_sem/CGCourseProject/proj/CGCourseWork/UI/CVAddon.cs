using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Numerics;
using System.Windows.Media.Imaging;
using Emgu.CV;

namespace UI
{
    public static class CVAddon
    {
        public static BitmapImage ToBitmapImage(this Bitmap bitmap)
        {
            using (var memory = new MemoryStream())
            {
                bitmap.Save(memory, ImageFormat.Png);
                memory.Position = 0;

                var bitmapImage = new BitmapImage();
                bitmapImage.BeginInit();
                bitmapImage.StreamSource = memory;
                bitmapImage.CacheOption = BitmapCacheOption.OnLoad;
                bitmapImage.EndInit();
                bitmapImage.Freeze();

                return bitmapImage;
            }
        }

        public static Bitmap ConcatTwoImages(Bitmap b1, Bitmap b2)
        {
            var concat = new Bitmap(b1);
            var gr = Graphics.FromImage(concat);
            gr.DrawImage(b2, 0, 0);

            return concat;
        }

        public static Matrix4x4 ToMatrix4x4(this Mat m)
        {
            double[,] tmp = (double[,])m.GetData();

            Matrix4x4 matr = new Matrix4x4()
            {
                M11 = (float)tmp[0, 0], M12 = (float)tmp[0, 1], M13 = (float)tmp[0, 2],
                M21 = (float)tmp[1, 0], M22 = (float)tmp[1, 1], M23 = (float)tmp[1, 2],
                M31 = (float)tmp[2, 0], M32 = (float)tmp[2, 1], M33 = (float)tmp[2, 2],
                M44 = 1
            };

            return matr;
        }
    }
}
