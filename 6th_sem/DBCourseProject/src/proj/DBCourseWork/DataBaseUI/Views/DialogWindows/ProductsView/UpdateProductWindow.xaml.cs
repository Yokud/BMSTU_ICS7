using DataBaseUI.SysEntities;
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

namespace DataBaseUI.Views.DialogWindows.ProductsView
{
    /// <summary>
    /// Логика взаимодействия для UpdateProductWindow.xaml
    /// </summary>
    public partial class UpdateProductWindow : Window
    {
        public UpdateProductWindow()
        {
            InitializeComponent();
        }

        public string UpdatedProductName
        {
            get
            {
                return !string.IsNullOrWhiteSpace(NewProductName.Text) ? NewProductName.Text : null;
            }
        }

        public string UpdatedProductType
        {
            get
            {
                return !string.IsNullOrWhiteSpace(NewProductType.Text) ? NewProductType.Text : null;
            }
        }

        public CostStory NewCost
        {
            get
            {
                return !string.IsNullOrWhiteSpace(NewCostYear.Text) && int.TryParse(NewCostYear.Text, out int year) &&
                    !string.IsNullOrWhiteSpace(NewCostMonth.Text) && int.TryParse(NewCostMonth.Text, out int month) &&
                    !string.IsNullOrWhiteSpace(NewCostValue.Text) && int.TryParse(NewCostValue.Text, out int cost) ?
                    new CostStory(year, month, cost, 0) : null;
            }
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            DialogResult = true;
        }
    }
}
