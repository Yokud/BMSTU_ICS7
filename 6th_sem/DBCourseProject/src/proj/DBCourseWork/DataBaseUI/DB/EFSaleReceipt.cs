using System;
using System.Collections.Generic;

namespace DataBaseUI.DB
{
    public partial class EFSaleReceipt
    {
        public EFSaleReceipt()
        {
            Salereceiptpositions = new HashSet<EFSaleReceiptPosition>();
        }

        public int Id { get; set; }
        public string Fio { get; set; } = null!;
        public int Shopid { get; set; }
        public DateOnly Dateofpurchase { get; set; }

        public virtual EFShop Shop { get; set; } = null!;
        public virtual ICollection<EFSaleReceiptPosition> Salereceiptpositions { get; set; }
    }
}
