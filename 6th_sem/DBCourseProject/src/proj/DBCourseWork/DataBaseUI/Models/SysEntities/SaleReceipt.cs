using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace DataBaseUI.SysEntities
{
    public class SaleReceipt : INotifyPropertyChanged
    {
        int id;
        string fio;
        DateOnly dateOfPurchase;
        int shopId;
        int? summaryCost;

        public SaleReceipt(int id, string fio, DateOnly dateOfPurchase, int shopId)
        {
            Id = id;
            Fio = fio;
            DateOfPurchase = dateOfPurchase;
            ShopId = shopId;
        }

        public SaleReceipt(string fio, DateOnly dateOfPurchase, int shopId)
        {
            Fio = fio;
            DateOfPurchase = dateOfPurchase;
            ShopId = shopId;
        }

        public int Id { get => id; set { id = value; OnPropertyChanged("Id"); } }
        public string Fio { get => fio; set { fio = value; OnPropertyChanged("Fio"); } }
        public DateOnly DateOfPurchase { get => dateOfPurchase; set { dateOfPurchase = value; OnPropertyChanged("DateOfPurchase"); } }
        public int ShopId { get => shopId; set { shopId = value; OnPropertyChanged("ShopId"); } }
        public int? SummaryCost { get => summaryCost; set { summaryCost = value; OnPropertyChanged("SummaryCost"); } }

        public event PropertyChangedEventHandler? PropertyChanged;
        public void OnPropertyChanged([CallerMemberName] string prop = "")
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(prop));
        }
    }
}
