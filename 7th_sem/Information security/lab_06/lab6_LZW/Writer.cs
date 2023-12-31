using System;
using System.IO;
using System.Collections;

namespace lab6_LZW
{
    public class MyBinaryWriter : BinaryWriter
    {
        private bool[] curByte = new bool[8];
        private byte curBitIndx = 0;

        public MyBinaryWriter(Stream s) : base(s) { }

        public override void Flush()
        {
            base.Write(ConvertToByte(curByte));
            base.Flush();
        }

        public override void Write(bool value)
        {
            curByte[curBitIndx] = value;
            curBitIndx++;

            if (curBitIndx == 8)
            {
                base.Write(ConvertToByte(curByte));
                this.curBitIndx = 0;
                this.curByte = new bool[8];
            }
        }

        public void WriteNBits(int value, int n)
        {
            BitArray bitVal = new BitArray(new int[] { value });
            for (int i = 0; i < n; i++)
            {
                Write(bitVal[i]); // т.к. значащие в начале 
            }
        }

        private static byte ConvertToByte(bool[] bools)
        {
            byte b = 0;

            byte bitIndex = 0;
            for (int i = 0; i < 8; i++)
            {
                if (bools[i])
                {
                    b |= (byte)(((byte)1) << bitIndex);
                }
                bitIndex++;
            }

            return b;
        }

        public override void Close()
        {
            WriteNBits(0, 8);
            base.Close();
        }
    }
}
