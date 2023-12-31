using System;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Drawing.Imaging;

namespace RenderLib
{
    public class FastBitmap : IDisposable, ICloneable
    {
        public Bitmap Bitmap { get; private set; }
        public int[] Bits { get; private set; }
        public bool Disposed { get; private set; }
        public int Height { get; private set; }
        public int Width { get; private set; }

        protected GCHandle BitsHandle { get; private set; }

        public static FastBitmap FromBitmap(Bitmap bitmap)
        {
            FastBitmap fastBitmap = new FastBitmap(bitmap.Width, bitmap.Height);
            for (int i = 0; i < bitmap.Width; i++)
            {
                for (int j = 0; j < bitmap.Height; j++)
                {
                    fastBitmap.Bits[j * bitmap.Width + i] = bitmap.GetPixel(i, bitmap.Height - 1 - j).ToArgb();
                }
            }
            return fastBitmap;
        }
        public FastBitmap(int width, int height)
        {
            Width = width;
            Height = height;
            Bits = new int[width * height];
            BitsHandle = GCHandle.Alloc(Bits, GCHandleType.Pinned);
            Bitmap = new Bitmap(width, height, width * 4, PixelFormat.Format32bppPArgb, BitsHandle.AddrOfPinnedObject());
            Disposed = false;
        }

        public void Clear()
        {
            for (int i = 0; i < Bits.Length; i++)
            {
                Bits[i] = 0;
            }
        }
        public void SetPixel(int x, int y, Color color)
        {
            int col = color.ToArgb();
            Bits[x + (y * Width)] = col;
        }

        public void SetPixel(int x, int y, int color)
        {
            Bits[x + (y * Width)] = color;
        }

        public Color GetPixel(int x, int y)
        {
            int index = x + (y * Width);
            Color color = Color.FromArgb(Bits[index]);
            return color;
        }

        public void Dispose()
        {
            BitsHandle.Free();
            Disposed = true;
        }

        public object Clone()
        {
            return FastBitmap.FromBitmap(Bitmap);
        }
    }

    public class Texture
    {
        public FastBitmap Texels { get; private set; }
        public Color DefaultTexture { get; private set; }

        public Texture(string filepath)
        {
            Texels = FastBitmap.FromBitmap((Bitmap)Image.FromFile(filepath));
        }

        public Texture(Bitmap bmp)
        {
            Texels = FastBitmap.FromBitmap(bmp);
        }

        public Texture()
        {
            DefaultTexture = PolModel.DefaultTexture;
        }

        public Color GetTexel(float u, float v)
        {
            if (Texels == null)
                return DefaultTexture;

            if (u < 0 || u > 1)
                u -= (float)Math.Floor(u);

            if (v < 0 || v > 1)
                v -= (float)Math.Floor(v);

            int x_texel = MathAddon.RoundToInt((Texels.Width - 1) * u);
            int y_texel = MathAddon.RoundToInt((Texels.Height - 1) * v);

            return Texels.GetPixel(x_texel, y_texel);
        }
    }
}
