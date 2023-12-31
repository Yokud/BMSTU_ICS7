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
    /// Логика взаимодействия для AddShopWindow.xaml
    /// </summary>
    public partial class AddShopWindow : Window
    {
        public AddShopWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            this.DialogResult = true;
        }

        public Shop NewShop
        {
            get { return !string.IsNullOrWhiteSpace(ShopName.Text) && !string.IsNullOrWhiteSpace(ShopDescr.Text) ? new Shop(ShopName.Text, ShopDescr.Text) : null; }
        }
    }
}
