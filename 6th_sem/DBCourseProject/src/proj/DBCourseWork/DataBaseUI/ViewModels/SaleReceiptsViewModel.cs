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
using DataBaseUI.Views.DialogWindows.SaleReceiptsView;
using Microsoft.Extensions.Logging;

namespace DataBaseUI.ViewModels
{
    internal class SaleReceiptsViewModel : INotifyPropertyChanged
    {
        ISaleReceiptsRepository saleReceipts;
        ISaleReceiptPositionsRepository saleReceiptPositions;
        IAvailabilityRepository availavilities;
        Shop selectedShop;
        SaleReceipt selectedSaleReceipt;
        Product selectedSaleReceiptPosition;

        ILogger logger;

        bool isAdmin;

        public SaleReceiptsViewModel(SpsrLtDbContext dbContext, ILogger logger = null)
        {
            saleReceipts = new PgSQLSaleReceiptsRepository(dbContext, logger);
            saleReceiptPositions = new PgSQLSaleReceiptPositionsRepository(dbContext, logger);
            availavilities = new PgSQLAvailabilityRepository(dbContext, logger);

            this.logger = logger;
        }

        public Shop SelectedShop
        {
            get { return selectedShop; }
            set 
            { 
                selectedShop = value; 
                OnPropertyChanged("SelectedShop");
                OnPropertyChanged("SaleReceipts");
                logger?.LogInformation("Selected shop was updated.\n");
            }
        }

        public SaleReceipt SelectedSaleReceipt
        {
            get { return selectedSaleReceipt; }
            set 
            { 
                selectedSaleReceipt = value; 
                OnPropertyChanged("SelectedSaleReceipt");
                OnPropertyChanged("SaleReceiptPositions");
                logger?.LogInformation("Selected sale receipt was updated.\n");
            }
        }

        public Product SelectedSaleReceiptPosition
        {
            get { return selectedSaleReceiptPosition; }
            set 
            { 
                selectedSaleReceiptPosition = value; 
                OnPropertyChanged("SelectedSaleReceiptPosition");
                logger?.LogInformation("Selected sale receipt position was updated.\n");
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

        public IEnumerable<SaleReceipt> SaleReceipts
        {
            get
            {
                if (selectedShop == null)
                    return null;

                var saleReceiptsInShop = saleReceipts.GetAllFromShop(selectedShop);

                if (saleReceiptsInShop != null)
                    foreach (var sr in saleReceiptsInShop)
                    {
                        var positions = saleReceiptPositions.GetAllFromSaleReceipt(sr);
                        sr.SummaryCost = positions.Sum(x => x.Cost);
                    }

                return saleReceiptsInShop;
            }
        }

        public IEnumerable <Product> SaleReceiptPositions
        {
            get
            {
                return selectedSaleReceipt == null ? null : saleReceiptPositions.GetAllFromSaleReceipt(selectedSaleReceipt);
            }
        }

        RelayCommand addSRCommand;
        public RelayCommand AddSRCommand
        {
            get
            {
                return addSRCommand ??= new RelayCommand(obj => 
                {
                    AddSaleReceiptWindow wnd = new AddSaleReceiptWindow();

                    if (wnd.ShowDialog() == true)
                    {
                        SaleReceipt sr = wnd.NewSaleReceipt;

                        if (sr != null)
                        {
                            sr.ShopId = selectedShop.Id;
                            AddSaleReceipt(sr);
                        }    
                    }
                });
            }
        }

        RelayCommand addSRPCommand;
        public RelayCommand AddSRPCommand
        {
            get
            {
                return addSRPCommand ??= new RelayCommand(obj =>
                {
                    AddSaleReceiptPositionWindow wnd = new AddSaleReceiptPositionWindow(new PgSQLProductsRepository().GetAllFromShop(SelectedShop));

                    if (wnd.ShowDialog() == true)
                    {
                        Product prod = wnd.SelectedProduct;

                        if (prod != null)
                        {
                            int id = availavilities.GetAll().Where(x => x.ProductId == prod.Id && x.ShopId == selectedShop.Id).First().Id;
                            AddSaleReceiptPosition(new SaleReceiptPosition(id, selectedSaleReceipt.Id));
                        }
                    }
                });
            }
        }

        RelayCommand deleteSRCommand;
        public RelayCommand DeleteSRCommand
        {
            get
            {
                return deleteSRCommand ??= new RelayCommand(obj =>
                {
                    SaleReceipt sr = obj as SaleReceipt;

                    if (sr != null)
                        DeleteSaleReceipt(sr);
                }, obj => saleReceipts.GetAll()?.Count() > 0);
            }
        }

        RelayCommand deleteSRPCommand;
        public RelayCommand DeleteSRPCommand
        {
            get
            {
                return deleteSRPCommand ??= new RelayCommand(obj =>
                {
                    Product prod = obj as Product;

                    if (prod != null)
                    {
                        int id = availavilities.GetAll().Where(x => x.ProductId == prod.Id && x.ShopId == selectedShop.Id).First().Id;
                        DeleteSaleReceiptPosition(saleReceiptPositions.GetAll().Where(x => x.AvailabilityId == id).First());
                    }
                }, obj => saleReceiptPositions.GetAll()?.Count() > 0);
            }
        }

        public void AddSaleReceipt(SaleReceipt receipt)
        {
            try
            {
                saleReceipts.Create(receipt);
                logger?.LogInformation(string.Format("Sale receipt with id = {0} was added.\n", receipt.Id));
                OnPropertyChanged("SaleReceipts");
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
                logger?.LogError(e.Message);
            }
        }

        public void AddSaleReceiptPosition(SaleReceiptPosition pos)
        {
            try
            {
                saleReceiptPositions.Create(pos);
                logger?.LogInformation(string.Format("Sale receipt position with id = {0} was added.\n", pos.Id));
                OnPropertyChanged("SaleReceiptPositions");
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
                logger?.LogError(e.Message);
            }
        }

        public void DeleteSaleReceipt(SaleReceipt receipt)
        {
            try
            {
                saleReceipts.Delete(receipt);
                logger?.LogInformation(string.Format("Sale receipt with id = {0} was deleted.\n", receipt.Id));
                OnPropertyChanged("SaleReceipts");
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
                logger?.LogError(e.Message);
            }
        }

        public void DeleteSaleReceiptPosition(SaleReceiptPosition pos)
        {
            try
            {
                saleReceiptPositions.Delete(pos);
                logger?.LogInformation(string.Format("Sale receipt position with id = {0} was deleted.\n", pos.Id));
                OnPropertyChanged("SaleReceiptPositions");
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
