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

namespace DataBaseUI.Views.DialogWindows.SaleReceiptsView
{
    /// <summary>
    /// Логика взаимодействия для AddSaleReceiptWindow.xaml
    /// </summary>
    public partial class AddSaleReceiptWindow : Window
    {
        public AddSaleReceiptWindow()
        {
            InitializeComponent();
        }

        public SaleReceipt NewSaleReceipt
        {
            get
            {
                return !string.IsNullOrWhiteSpace(FIO.Text) && !string.IsNullOrWhiteSpace(DateOfPurchase.Text) && DateOnly.TryParse(DateOfPurchase.Text, out DateOnly date) ? new SaleReceipt(FIO.Text, date, 0) : null;
            }
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            DialogResult = true;
        }
    }
}
