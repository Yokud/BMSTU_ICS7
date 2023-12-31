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
    /// Логика взаимодействия для UpdateShopWindow.xaml
    /// </summary>
    public partial class UpdateShopWindow : Window
    {
        public UpdateShopWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            DialogResult = true;
        }

        public string NewShopName
        {
            get { return !string.IsNullOrWhiteSpace(ShopName.Text) ? ShopName.Text : null; }
        }

        public string NewShopDescr
        {
            get { return !string.IsNullOrWhiteSpace(ShopDescr.Text) ? ShopDescr.Text : null; }
        }
    }
}
