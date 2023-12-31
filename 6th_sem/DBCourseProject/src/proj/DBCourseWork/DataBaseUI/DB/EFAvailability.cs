using System;
using System.Collections.Generic;

namespace DataBaseUI.DB
{
    public partial class EFAvailability
    {
        public EFAvailability()
        {
            Coststories = new HashSet<EFCostStory>();
            Salereceiptpositions = new HashSet<EFSaleReceiptPosition>();
        }

        public int Id { get; set; }
        public int Shopid { get; set; }
        public int Productid { get; set; }

        public virtual EFProduct Product { get; set; } = null!;
        public virtual EFShop Shop { get; set; } = null!;
        public virtual ICollection<EFCostStory> Coststories { get; set; }
        public virtual ICollection<EFSaleReceiptPosition> Salereceiptpositions { get; set; }
    }
}
