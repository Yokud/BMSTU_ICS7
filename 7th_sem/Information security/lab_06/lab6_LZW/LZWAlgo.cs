using System;
using System.Collections.Generic;
using System.IO;

namespace lab6_LZW
{
    static class LZWAlgo
    {        
        /// <summary>
        /// Сжатие
        /// </summary>
        /// <param name="src">Путь к файлу с данными</param>
        /// <param name="dst">Путь для создания сжатого файла</param>
        public static void Compress(string src, string dst)
        {
            Table table = new Table();

            using (var input = new FileStream(src, FileMode.Open))
            {
                var output = new MyBinaryWriter(new FileStream(dst, FileMode.Create));
                {
                    TableRow p = new TableRow(); // empty
                    
                    int last = input.ReadByte();
                    while (last != -1)
                    {
                        TableRow pPlusC = p + new TableRow(last); //string pPlusC = p + (char)last;
                        bool eofFlag = false; // flag for EOF while searching new row
                        while (table.IsRowInTable(pPlusC) && !eofFlag) //dictionary.FindIndex(x => x == pPlusC) != -1)
                        {
                            p = pPlusC;
                            last = input.ReadByte();

                            if (last == -1)
                                eofFlag = true;
                            else
                                pPlusC += new TableRow(last);
                        }

                        if (!eofFlag)
                            table.Add(pPlusC);

                        int indexToAdd = table.FindIndex(p);
                        output.WriteNBits(indexToAdd, GetBitsAmount(table.Count));
                        p = new TableRow();
                    }
                }
                output.Close();
            }
        }

        /// <summary>
        /// Распаковка
        /// </summary>
        /// <param name="src">Путь к сжатому файлу</param>
        /// <param name="dst">Путь для создания распакованного файла</param>
        public static void Decompress(string src, string dst)
        {
            Table table = new Table();

            using (var input = new MyBinaryReader(new FileStream(src, FileMode.Open)))
            {
                using (var output = new FileStream(dst, FileMode.Create))
                {
                    TableRow w = new TableRow();

                    var cW = input.ReadNBits(GetBitsAmount(table.Count));

                    while (cW != -1)
                    {
                        TableRow entry = new TableRow();
                        if (cW < table.Count)
                            entry = table[cW];
                        else if (cW == table.Count)
                            entry = w + w[0];
                        else
                            break;

                        foreach (byte b in entry.row)
                            output.WriteByte(b);

                        if (entry.row.Count != 0 && !table.IsRowInTable(w + entry[0]))
                            table.Add(w + entry[0]);

                        w = entry;

                        cW = input.ReadNBits(GetBitsAmount(table.Count));
                    }
                }
            }
        }
        
        public static int GetBitsAmount(int maxVal)
        {
            int pow = 0;
            while (maxVal > 0)
            {
                maxVal >>= 1;
                pow++;
            }

            return pow;
        }
    }
}
