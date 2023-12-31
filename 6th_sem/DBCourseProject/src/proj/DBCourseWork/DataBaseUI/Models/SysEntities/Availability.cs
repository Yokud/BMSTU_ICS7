using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace DataBaseUI.SysEntities
{
    public class Availability : INotifyPropertyChanged
    {
        int id, shopId, productId;

        public Availability(int id, int shopid, int productid)
        {
            Id = id;
            ShopId = shopid;
            ProductId = productid;
        }

        public Availability(int shopid, int productid)
        {
            ShopId = shopid;
            ProductId = productid;
        }

        public int Id { get => id; set { id = value; OnPropertyChanged("Id"); } }
        public int ShopId { get => shopId; set { shopId = value; OnPropertyChanged("ShopId"); } }
        public int ProductId { get => productId; set { productId = value; OnPropertyChanged("ProductId"); } }

        public event PropertyChangedEventHandler? PropertyChanged;
        public void OnPropertyChanged([CallerMemberName] string prop = "")
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(prop));
        }
    }
}
