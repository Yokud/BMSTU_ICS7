using System;
using System.Collections.Generic;

namespace DataBaseUI.DB
{
    public partial class EFProduct
    {
        public EFProduct()
        {
            Availabilities = new HashSet<EFAvailability>();
        }

        public int Id { get; set; }
        public string Name { get; set; } = null!;
        public string Producttype { get; set; } = null!;

        public virtual ICollection<EFAvailability> Availabilities { get; set; }
    }
}
