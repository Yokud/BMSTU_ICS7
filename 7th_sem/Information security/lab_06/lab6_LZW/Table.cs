using System;
using System.Collections.Generic;
using System.Text;

namespace lab6_LZW
{
    class Table
    {
        List<TableRow> table;

        public TableRow this[int i]
        {
            get { return table[i]; }
        }

        public int Count => table.Count;

        public Table()
        {
            table = new List<TableRow>();

            for (int i = 0; i < 256; i++)
                table.Add(new TableRow(i));
        }

        public int FindIndex(TableRow tableRow)
        {
            return table.FindIndex(x => x.Equals(tableRow));
        }

        public bool IsRowInTable(TableRow tableRow)
        {
            return (FindIndex(tableRow) == -1) ? false : true;
        }

        public void Add(TableRow tableRow)
        {
            table.Add(tableRow);
        }
    }
}
