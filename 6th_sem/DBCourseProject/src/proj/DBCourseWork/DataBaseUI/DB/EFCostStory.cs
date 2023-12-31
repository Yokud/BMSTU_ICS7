using System;
using System.Collections.Generic;

namespace DataBaseUI.DB
{
    public partial class EFCostStory
    {
        public int Id { get; set; }
        public int Year { get; set; }
        public int Month { get; set; }
        public int Cost { get; set; }
        public int Availabilityid { get; set; }

        public virtual EFAvailability Availability { get; set; } = null!;
    }
}
