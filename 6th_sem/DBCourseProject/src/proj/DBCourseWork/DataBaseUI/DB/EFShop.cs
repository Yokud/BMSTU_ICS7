using System;
using System.Collections.Generic;

namespace DataBaseUI.DB
{
    public partial class EFShop
    {
        public EFShop()
        {
            Availabilities = new HashSet<EFAvailability>();
            Salereceipts = new HashSet<EFSaleReceipt>();
        }

        public int Id { get; set; }
        public string Name { get; set; } = null!;
        public string Description { get; set; } = null!;

        public virtual ICollection<EFAvailability> Availabilities { get; set; }
        public virtual ICollection<EFSaleReceipt> Salereceipts { get; set; }
    }
}
