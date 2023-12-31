using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace DataBaseUI.SysEntities
{
    public class Product : INotifyPropertyChanged
    {
        int id;
        string name;
        string productType;
        int? cost;

        public Product(int id, string name, string productType, int? cost = null)
        {
            Id = id;
            Name = name;
            ProductType = productType;
            Cost = cost;
        }

        public Product(string name, string productType, int? cost = null)
        {
            Name = name;
            ProductType = productType;
            Cost = cost;
        }

        public int Id { get => id; set { id = value; OnPropertyChanged("Id"); } }
        public string Name { get => name; set { name = value; OnPropertyChanged("Name"); } }
        public string ProductType { get => productType; set { productType = value; OnPropertyChanged("ProductType"); } }
        public int? Cost { get => cost; set { cost = value; OnPropertyChanged("Cost"); } }

        public event PropertyChangedEventHandler? PropertyChanged;
        public void OnPropertyChanged([CallerMemberName] string prop = "")
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(prop));
        }
    }
}
