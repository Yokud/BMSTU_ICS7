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

namespace DataBaseUI.Views.DialogWindows
{
    /// <summary>
    /// Логика взаимодействия для CreateProductWindow.xaml
    /// </summary>
    public partial class CreateProductWindow : Window
    {
        public CreateProductWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            DialogResult = true;
        }

        public Product NewProduct
        {
            get
            {
                return !string.IsNullOrWhiteSpace(NewProductName.Text) && !string.IsNullOrWhiteSpace(NewProductType.Text) ? 
                    new Product(NewProductName.Text, NewProductType.Text) : null;
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
    }
}
