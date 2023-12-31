using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace DataBaseUI.Views.DialogWindows.CostStoryView
{
    /// <summary>
    /// Логика взаимодействия для UpdateCostStoryWindow.xaml
    /// </summary>
    public partial class UpdateCostStoryWindow : Window
    {
        public UpdateCostStoryWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            DialogResult = true;
        }

        public int? NewYear
        {
            get => !string.IsNullOrWhiteSpace(NewCostYear.Text) && int.TryParse(NewCostYear.Text, out int year) ? year : null;
        }

        public int? NewMonth
        {
            get => !string.IsNullOrWhiteSpace(NewCostMonth.Text) && int.TryParse(NewCostMonth.Text, out int month) ? month : null;
        }

        public int? NewCost
        {
            get => !string.IsNullOrWhiteSpace(NewCostValue.Text) && int.TryParse(NewCostValue.Text, out int cost) ? cost : null;
        }
    }
}
