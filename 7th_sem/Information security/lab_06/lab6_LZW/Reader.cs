using System;
using System.IO;
using System.Collections;

namespace lab6_LZW
{
    public class MyBinaryReader : BinaryReader
    {
        private bool[] curByte = new bool[8];
        private byte curBitIndx = 0;
        private BitArray ba;
        private bool EOS = false;

        public MyBinaryReader(Stream s) : base(s)
        {
            ba = new BitArray(new byte[] { base.ReadByte() });
            ba.CopyTo(curByte, 0);
            ba = null;
        }

        public override bool ReadBoolean()
        {
            if (curBitIndx == 8)
            {
                ba = new BitArray(new byte[] { base.ReadByte() });
                ba.CopyTo(curByte, 0);
                ba = null;
                this.curBitIndx = 0;
            }

            bool b = curByte[curBitIndx];
            curBitIndx++;
            return b;
        }

        public int ReadNBits(int n)
        {
            if (EOS)
                return -1;

            BitArray bitVal = new BitArray(32);
            for (int i = 0; i < n; i++)
            {
                try
                {
                    bitVal[i] = ReadBoolean();
                }
                catch (EndOfStreamException)
                {
                    EOS = true;
                    break;
                }
            }

            int[] array = new int[1];
            bitVal.CopyTo(array, 0);

            return array[0];
        }
    }
}
