using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace DataBaseUI.SysEntities
{
    public class CostStory : INotifyPropertyChanged
    {
        int id, year, month, cost, availabilityId;

        public CostStory(int id, int year, int month, int cost, int availabilityid)
        {
            Id = id;
            Year = year;
            Month = month;
            Cost = cost;
            AvailabilityId = availabilityid;
        }

        public CostStory(int year, int month, int cost, int availabilityid)
        {
            Year = year;
            Month = month;
            Cost = cost;
            AvailabilityId = availabilityid;
        }

        public int Id { get => id; set { id = value; OnPropertyChanged("Id"); } }
        public int Year { get => year; set { year = value; OnPropertyChanged("Year"); } }
        public int Month { get => month; set { month = value; OnPropertyChanged("Month"); } }
        public int Cost { get => cost; set { cost = value; OnPropertyChanged("Cost"); } }
        public int AvailabilityId { get => availabilityId; set { availabilityId = value; OnPropertyChanged("AvailabilityId"); } }

        public event PropertyChangedEventHandler? PropertyChanged;
        public void OnPropertyChanged([CallerMemberName] string prop = "")
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(prop));
        }
    }
}
