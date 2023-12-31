using DataBaseUI.SysEntities;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
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
    /// Логика взаимодействия для AddProduct.xaml
    /// </summary>
    public partial class AddProductWindow : Window, INotifyPropertyChanged
    {
        IEnumerable<Product> _products;
        Product selectedProduct;

        public AddProductWindow(IEnumerable<Product> products)
        {
            InitializeComponent();
            _products = products;

            DataContext = this;
        }

        public IEnumerable<Product> Products
        {
            get { return _products; }
        }

        public Product SelectedProduct
        {
            get { return selectedProduct; }
            set
            {
                selectedProduct = value;
                OnPropertyChanged("SelectedProduct");
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

        public event PropertyChangedEventHandler? PropertyChanged;
        public void OnPropertyChanged([CallerMemberName] string prop = "")
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(prop));
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            DialogResult = true;
        }
    }
}
