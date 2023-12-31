using System;
using System.Collections.Generic;

namespace DataBaseUI.DB
{
    public partial class EFSaleReceiptPosition
    {
        public int Id { get; set; }
        public int Availabilityid { get; set; }
        public int Salereceiptid { get; set; }

        public virtual EFAvailability Availability { get; set; } = null!;
        public virtual EFSaleReceipt Salereceipt { get; set; } = null!;
    }
}
