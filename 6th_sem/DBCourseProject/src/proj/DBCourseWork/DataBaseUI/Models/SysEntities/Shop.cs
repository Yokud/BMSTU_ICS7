using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace DataBaseUI.SysEntities
{
    public class Shop : INotifyPropertyChanged
    {
        int id;
        string name;
        string description;

        public Shop(int id, string name, string description)
        {
            Id = id;
            Name = name;
            Description = description;
        }

        public Shop(string name, string description)
        {
            Name = name;
            Description = description;
        }

        public int Id { get => id; set { id = value; OnPropertyChanged("Id"); } }
        public string Name { get => name; set { name = value; OnPropertyChanged("Name"); } }
        public string Description { get => description; set { description = value; OnPropertyChanged("Description"); } }

        public event PropertyChangedEventHandler? PropertyChanged;
        public void OnPropertyChanged([CallerMemberName] string prop = "")
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(prop));
        }
    }
}
