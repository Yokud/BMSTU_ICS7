using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Windows;
using System.Threading.Tasks;
using DataBaseUI.Models;
using DataBaseUI.SysEntities;
using DataBaseUI.DB;
using Microsoft.Extensions.Logging;
using DataBaseUI.Views.DialogWindows;

namespace DataBaseUI.ViewModels
{
    internal class ShopsViewModel : INotifyPropertyChanged
    {
        IShopsRepository shopsRepository;
        Shop selectedShop;
        internal Delegate del;
        ILogger logger;

        bool isAdmin;

        public ShopsViewModel(SpsrLtDbContext spsr, ILogger logger = null)
        {
            shopsRepository = new PgSQLShopsRepository(spsr, logger);
            this.logger = logger;
        }

        public IEnumerable<Shop> Shops
        {
            get
            {
                return shopsRepository.GetAll();
            }
        }

        public Shop SelectedShop
        {
            get { return selectedShop; }
            set
            {
                selectedShop = value;
                SetSelectedShop(value);
                OnPropertyChanged("SelectedShop");
                logger?.LogInformation("Selected shop was updated.\n");
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
                    AddShopWindow wnd = new AddShopWindow();

                    if (wnd.ShowDialog() == true)
                    {
                        var shop = wnd.NewShop;

                        if (shop != null)
                            AddShop(shop);
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
                    Shop shop = obj as Shop;

                    if (shop != null)
                        DeleteShop(shop);
                },
                (obj => shopsRepository.GetAll().Count() > 0)
                );
            }
        }

        RelayCommand updateCommand;
        public RelayCommand UpdateCommand
        {
            get
            {
                return updateCommand ??= new RelayCommand(obj =>
                {
                    UpdateShopWindow wnd = new UpdateShopWindow();

                    if (wnd.ShowDialog() == true)
                    {
                        Shop shop = obj as Shop;

                        if (shop != null)
                        {
                            shop.Name = wnd.NewShopName ?? shop.Name;
                            shop.Description = wnd.NewShopDescr ?? shop.Description;
                            UpdateShop(shop);
                        }
                    }
                }, (obj => selectedShop != null)
                );
            }
        }

        internal void SetSelectedShop(Shop selectedShop)
        {
            del.DynamicInvoke(selectedShop);
        }

        public void AddShop(Shop shop)
        {
            try
            {
                shopsRepository.Create(shop);
                logger?.LogInformation(string.Format("Shop with id = {0} was added.\n", shop.Id));
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
                logger?.LogError(e.Message);
            }
        }

        public void DeleteShop(Shop shop)
        {
            try
            {
                shopsRepository.Delete(shop);
                logger?.LogInformation(string.Format("Shop with id = {0} was deleted.\n", shop.Id));
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
                logger?.LogError(e.Message);
            }
        }

        public void UpdateShop(Shop shop)
        {
            try
            {
                shopsRepository.Update(shop);
                logger?.LogInformation(string.Format("Shop with id = {0} was updated.\n", shop.Id));
                OnPropertyChanged("Shops");
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
                logger?.LogError(e.Message);
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
