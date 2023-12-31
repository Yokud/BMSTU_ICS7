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

namespace DataBaseUI.Views.DialogWindows.SaleReceiptsView
{
    /// <summary>
    /// Логика взаимодействия для AddSaleReceiptPositionWindow.xaml
    /// </summary>
    public partial class AddSaleReceiptPositionWindow : Window, INotifyPropertyChanged
    {
        IEnumerable<Product> products;
        Product selectedProduct;

        public AddSaleReceiptPositionWindow(IEnumerable<Product> products)
        {
            InitializeComponent();

            this.products = products;
            DataContext = this;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            DialogResult = true;
        }

        public IEnumerable<Product> Products
        {
            get { return products; }
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

        public event PropertyChangedEventHandler? PropertyChanged;
        public void OnPropertyChanged([CallerMemberName] string prop = "")
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(prop));
        }
    }
}
