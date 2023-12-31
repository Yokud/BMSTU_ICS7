using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using DataBaseUI.DB;
using DataBaseUI.Models;
using DataBaseUI.SysEntities;
using DataBaseUI.Views.DialogWindows;
using DataBaseUI.Views.DialogWindows.ProductsView;
using Microsoft.Extensions.Logging;

namespace DataBaseUI.ViewModels
{
    internal class ProductsViewModel : INotifyPropertyChanged
    {
        IProductsRepository products;
        ICostStoryRepository costs;
        IAvailabilityRepository availabilities;
        Shop selectedShop;
        Product selectedProduct;

        bool isAdmin;

        ILogger logger;

        internal Delegate del;

        public ProductsViewModel(SpsrLtDbContext spsr, ILogger logger = null)
        {
            products = new PgSQLProductsRepository(spsr, logger);
            costs = new PgSQLCostStoryRepository(spsr, logger);
            availabilities = new PgSQLAvailabilityRepository(spsr, logger);

            this.logger = logger;
        }

        public Shop SelectedShop
        {
            get { return selectedShop; }
            set 
            { 
                selectedShop = value;
                OnPropertyChanged("SelectedShop");
                OnPropertyChanged("Products");
                logger?.LogInformation("Selected shop was updated.\n");
            }
        }

        public Product SelectedProduct
        {
            get { return selectedProduct; }
            set
            {
                selectedProduct = value;
                SetSelectedProduct(value);
                OnPropertyChanged("SelectedProduct");
                logger?.LogInformation("Selected product was updated.\n");
            }
        }

        public IEnumerable<Product> Products
        {
            get
            {
                return selectedShop == null ? null : products.GetAllFromShop(SelectedShop);
            }
        }

        public bool IsAdmin
        {
            get
            {
                return isAdmin;
            }
            set
            {
                isAdmin = value;
                OnPropertyChanged("IsAdmin");
            }
        }

        RelayCommand addCommand;
        public RelayCommand AddCommand
        {
            get
            {
                return addCommand ??= new RelayCommand(obj =>
                {
                    AddProductWindow wnd = new AddProductWindow(products.GetAll());

                    if (wnd.ShowDialog() == true)
                    {

                        Product prod = wnd.SelectedProduct;
                        CostStory cost = wnd.NewCost;

                        if (prod != null && cost != null)
                            AddProduct(prod, cost);
                    }
                });
            }
        }

        RelayCommand createCommand;
        public RelayCommand CreateCommand
        {
            get
            {
                return createCommand ??= new RelayCommand(obj =>
                {
                    CreateProductWindow wnd = new CreateProductWindow();

                    if (wnd.ShowDialog() == true)
                    {
                        Product prod = wnd.NewProduct;

                        if (prod != null)
                            CreateProduct(prod, wnd.NewCost);
                    }
                });
            }
        }

        RelayCommand deleteCommand;
        public RelayCommand DeleteCommand
        {
            get
            {
                return deleteCommand ??= new RelayCommand(obj =>
                {
                    Product prod = obj as Product;

                    if (prod != null)
                        DeleteProduct(prod);
                }, obj => products.GetAll().Count() > 0);
            }
        }

        RelayCommand updateCommand;
        public RelayCommand UpdateCommand
        {
            get
            {
                return updateCommand ??= new RelayCommand(obj =>
                {
                    UpdateProductWindow wnd = new UpdateProductWindow();

                    if (wnd.ShowDialog() == true)
                    {
                        Product product = obj as Product;

                        if (product != null)
                        {
                            product.Name = wnd.UpdatedProductName ?? product.Name;
                            product.ProductType = wnd.UpdatedProductType ?? product.ProductType;
                            UpdateProduct(product, wnd.NewCost);
                        }
                    }
                }, obj => selectedProduct != null);
            }
        }

        public void AddProduct(Product prod, CostStory cost = null)
        {
            try
            {
                Availability avail = new Availability(selectedShop.Id, prod.Id);
                availabilities.Create(avail);

                if (cost != null)
                {
                    cost.AvailabilityId = avail.Id;
                    costs.Create(cost);
                }
                
                logger?.LogInformation(string.Format("Product with id = {0} was added.\n", prod.Id));
                OnPropertyChanged("Products");
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
                logger?.LogError(e.Message);
            }
        }

        public void CreateProduct(Product prod, CostStory cost = null)
        {
            try
            {
                products.Create(prod);
                Availability newAvail = new Availability(SelectedShop.Id, prod.Id);
                availabilities.Create(newAvail);

                if (cost != null)
                {
                    cost.AvailabilityId = newAvail.Id;
                    costs.Create(cost);
                }
                
                logger?.LogInformation(string.Format("Product with id = {0} was created.\n", prod.Id));
                OnPropertyChanged("Products");
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
                logger?.LogError(e.Message);
            }
        }

        public void DeleteProduct(Product prod)
        {
            try
            {
                availabilities.Delete(availabilities.GetAll().Where(x => x.ShopId == selectedShop.Id && x.ProductId == prod.Id).First());
                logger?.LogInformation(string.Format("Product with id = {0} was deleted.\n", prod.Id));
                OnPropertyChanged("Products");
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
                logger?.LogError(e.Message);
            }
        }

        public void UpdateProduct(Product prod, CostStory cost = null)
        {
            try
            {
                products.Update(prod);

                if (cost != null)
                {
                    cost.AvailabilityId = availabilities.GetAll().Where(x => x.ProductId == prod.Id && x.ShopId == selectedShop.Id).First().Id;
                    costs.Create(cost);
                }

                prod.Cost = null;
                logger?.LogInformation(string.Format("Product with id = {0} was updated.\n", prod.Id));
                OnPropertyChanged("Products");
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
                logger?.LogError(e.Message);
            }
        }

        internal void SetSelectedProduct(Product product)
        {
            del.DynamicInvoke(product);
        }

        public event PropertyChangedEventHandler? PropertyChanged;
        public void OnPropertyChanged([CallerMemberName] string prop = "")
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(prop));
        }
    }
}
