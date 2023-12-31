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
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Diagnostics;
using DataBaseUI.DB;
using DataBaseUI.Views;
using DataBaseUI.ViewModels;
using DataBaseUI.SysEntities;
using Microsoft.Extensions.Logging;
using DataBaseUI.Logger;
using DataBaseUI.Views.DialogWindows;

namespace DataBaseUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        internal delegate void ShopValuePassDelegate(Shop selectedShop);
        internal event ShopValuePassDelegate ShopValuePassEvent;

        internal delegate void ProductValuePassDelegate(Product product);
        internal event ProductValuePassDelegate ProductValuePassEvent;

        SpsrLtDbContext dbContext;

        public MainWindow()
        {
            InitializeComponent();

            dbContext = new SpsrLtDbContext();
            ILogger logger = new DbLogger();

            ShopsContentControl.Content = new ShopsView();
            ShopsContentControl.DataContext = new ShopsViewModel(dbContext, logger);

            ProductsContentControl.Content = new ProductsView();
            ProductsContentControl.DataContext = new ProductsViewModel(dbContext);

            SaleReceiptsContentControl.Content = new SaleReceiptsView();
            SaleReceiptsContentControl.DataContext = new SaleReceiptsViewModel(dbContext);

            CostStoriesContentControl.Content = new CostStoryView();
            CostStoriesContentControl.DataContext = new CostStoryViewModel(dbContext);

            ShopValuePassEvent += new ShopValuePassDelegate(SetSelectedShop);
            ((ShopsViewModel)ShopsContentControl.DataContext).del = ShopValuePassEvent;

            ProductValuePassEvent += new ProductValuePassDelegate(SetSelectedProduct);
            ((ProductsViewModel)ProductsContentControl.DataContext).del = ProductValuePassEvent;

            dbContext.ChangeConnection("user", "");
        }

        internal void SetSelectedShop(Shop selectedShop)
        {
            ((ProductsViewModel)ProductsContentControl.DataContext).SelectedShop = selectedShop;
            ((SaleReceiptsViewModel)SaleReceiptsContentControl.DataContext).SelectedShop = selectedShop;

            ((CostStoryViewModel)CostStoriesContentControl.DataContext).SelectedShop = selectedShop;
        }

        internal void SetSelectedProduct(Product product)
        {
            ((CostStoryViewModel)CostStoriesContentControl.DataContext).SelectedProduct = product;
        }

        private void UserRB_Checked(object sender, RoutedEventArgs e)
        {
            if (ShopsContentControl?.DataContext != null)
                ((ShopsViewModel)ShopsContentControl.DataContext).IsAdmin = false;

            if (ProductsContentControl?.DataContext != null)
                ((ProductsViewModel)ProductsContentControl.DataContext).IsAdmin = false;

            if (SaleReceiptsContentControl?.DataContext != null)
                ((SaleReceiptsViewModel)SaleReceiptsContentControl.DataContext).IsAdmin = false;

            if (CostStoriesContentControl?.DataContext != null)
            {
                ((CostStoryViewModel)CostStoriesContentControl.DataContext).IsAnalyst = false;
                ((CostStoryViewModel)CostStoriesContentControl.DataContext).IsAdmin = false;
            }
        }

        private void AnalystRB_Checked(object sender, RoutedEventArgs e)
        {
            PasswordWindow wnd = new PasswordWindow();

            if (wnd.ShowDialog() == true)
            {
                try
                {
                    dbContext.ChangeConnection("analyst", wnd.Password);

                    if (ShopsContentControl?.DataContext != null)
                        ((ShopsViewModel)ShopsContentControl.DataContext).IsAdmin = false;

                    if (ProductsContentControl?.DataContext != null)
                        ((ProductsViewModel)ProductsContentControl.DataContext).IsAdmin = false;

                    if (SaleReceiptsContentControl?.DataContext != null)
                        ((SaleReceiptsViewModel)SaleReceiptsContentControl.DataContext).IsAdmin = false;

                    if (CostStoriesContentControl?.DataContext != null)
                    {
                        ((CostStoryViewModel)CostStoriesContentControl.DataContext).IsAnalyst = true;
                        ((CostStoryViewModel)CostStoriesContentControl.DataContext).IsAdmin = false;
                    }
                }
                catch (Exception exc)
                {
                    MessageBox.Show(exc.Message);

                    AnalystRB.IsChecked = false;
                    UserRB.IsChecked = true;
                }
            }
            else 
            {
                AnalystRB.IsChecked = false;
                UserRB.IsChecked = true;
            }
        }

        private void AdminRB_Checked(object sender, RoutedEventArgs e)
        {
            PasswordWindow wnd = new PasswordWindow();

            if (wnd.ShowDialog() == true)
            {
                try
                {
                    dbContext.ChangeConnection("admin", wnd.Password);

                    if (ShopsContentControl?.DataContext != null)
                        ((ShopsViewModel)ShopsContentControl.DataContext).IsAdmin = true;

                    if (ProductsContentControl?.DataContext != null)
                        ((ProductsViewModel)ProductsContentControl.DataContext).IsAdmin = true;

                    if (SaleReceiptsContentControl?.DataContext != null)
                        ((SaleReceiptsViewModel)SaleReceiptsContentControl.DataContext).IsAdmin = true;

                    if (CostStoriesContentControl?.DataContext != null)
                    {
                        ((CostStoryViewModel)CostStoriesContentControl.DataContext).IsAnalyst = true;
                        ((CostStoryViewModel)CostStoriesContentControl.DataContext).IsAdmin = true;
                    }
                }
                catch (Exception exc)
                {
                    MessageBox.Show(exc.Message);

                    AdminRB.IsChecked = false;
                    UserRB.IsChecked = true;
                }
            }
            else
            {
                AdminRB.IsChecked = false;
                UserRB.IsChecked = true;
            }
        }
    }
}
