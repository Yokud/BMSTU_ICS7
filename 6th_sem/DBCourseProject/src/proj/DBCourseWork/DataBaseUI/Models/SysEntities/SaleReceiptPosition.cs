using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace DataBaseUI.SysEntities
{
    public class SaleReceiptPosition : INotifyPropertyChanged
    {
        int id, availabilityId, saleReceiptId;

        public SaleReceiptPosition(int id, int availabilityid, int salereceiptid)
        {
            Id = id;
            AvailabilityId = availabilityid;
            SaleReceiptId = salereceiptid;
        }

        public SaleReceiptPosition(int availabilityid, int salereceiptid)
        {
            AvailabilityId = availabilityid;
            SaleReceiptId = salereceiptid;
        }

        public int Id { get => id; set { id = value; OnPropertyChanged("Id"); } }
        public int AvailabilityId { get => availabilityId; set { availabilityId = value; OnPropertyChanged("AvailabilityId"); } }
        public int SaleReceiptId { get => saleReceiptId; set { saleReceiptId = value; OnPropertyChanged("SaleReceiptId"); } }

        public event PropertyChangedEventHandler? PropertyChanged;
        public void OnPropertyChanged([CallerMemberName] string prop = "")
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(prop));
        }
    }
}
