using DataBaseUI.Models;
using DataBaseUI.SysEntities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TechnicUI
{
    internal class TechnicPresenter : ITechnicPresenter
    {
        IShopsRepository shops;
        IProductsRepository products;
        ISaleReceiptsRepository saleReceipts;
        ISaleReceiptPositionsRepository saleReceiptPositions;
        ICostsRepository costs;
        ICostStoryRepository costStories;
        IAvailabilityRepository availabilityies;

        ITechnicView view;

        public TechnicPresenter(ITechnicView view, IShopsRepository shops, 
                                                    IProductsRepository products, 
                                                    ISaleReceiptsRepository saleReceipts, 
                                                    ISaleReceiptPositionsRepository saleReceiptPositions, 
                                                    ICostsRepository costs, 
                                                    ICostStoryRepository costStory, 
                                                    IAvailabilityRepository availability)
        {
            View = view;

            Shops = shops;
            Products = products;
            SaleReceipts = saleReceipts;
            SaleReceiptPositions = saleReceiptPositions;
            Costs = costs;
            CostStories = costStory;
            Availabilityies = availability;

            View.AddShopEvent += AddShop;
            View.DeleteShopEvent += DeleteShop;
            View.UpdateShopEvent += UpdateShop;
            View.GetShopEvent += GetShop;
            View.GetAllShopsEvent += GetAllShops;

            View.AddProductEvent += AddProduct;
            View.DeleteProductEvent += DeleteProduct;
            View.UpdateProductEvent += UpdateProduct;
            View.GetProductEvent += GetProduct;
            View.GetAllProductsEvent += GetAllProducts;

            View.AddAvailabilityEvent += AddAvailability;
            View.DeleteAvailabilityEvent += DeleteAvailability;
            View.UpdateAvailabilityEvent += UpdateAvailability;
            View.GetAllAvailabilitiesEvent += GetAllAvailabilities;
            View.GetAvailabilityEvent += GetAvailability;

            View.AddCostEvent += AddCost;
            View.DeleteCostEvent += DeleteCost;
            View.UpdateCostEvent += UpdateCost;
            View.GetCostEvent += GetCost;
            View.GetAllCostsEvent += GetAllCosts;

            View.AddCostStoryEvent += AddCostStory;
            View.DeleteCostStoryEvent += DeleteCostStory;
            View.UpdateCostStoryEvent += UpdateCostStory;
            View.GetCostStoryEvent += GetCostStory;
            View.GetAllCostStoriesEvent += GetAllCostStories;

            View.AddSaleReceiptEvent += AddSaleReceipt;
            View.DeleteSaleReceiptEvent += DeleteSaleReceipt;
            View.UpdateSaleReceiptEvent += UpdateSaleReceipt;
            View.GetSaleReceiptEvent += GetSaleReceipt;
            View.GetAllSaleReceiptsEvent += GetAllSaleReceipts;

            View.AddSaleReceiptPositionEvent += AddSaleReceiptPosition;
            View.DeleteSaleReceiptPositionEvent += DeleteSaleReceiptPosition;
            View.UpdateSaleReceiptPositionEvent += UpdateSaleReceiptPosition;
            View.GetSaleReceiptPositionEvent += GetSaleReceiptPosition;
            View.GetAllSaleReceiptPositionsEvent += GetAllSaleReceiptPositions;
        }

        public IShopsRepository Shops { get => shops; set => shops = value; }
        public IProductsRepository Products { get => products; set => products = value; }
        public ISaleReceiptsRepository SaleReceipts { get => saleReceipts; set => saleReceipts = value; }
        public ISaleReceiptPositionsRepository SaleReceiptPositions { get => saleReceiptPositions; set => saleReceiptPositions = value; }
        public ICostsRepository Costs { get => costs; set => costs = value; }
        public ICostStoryRepository CostStories { get => costStories; set => costStories = value; }
        public IAvailabilityRepository Availabilityies { get => availabilityies; set => availabilityies = value; }
        public ITechnicView View { get => view; set => view = value; }

        public void AddAvailability(Availability item)
        {
            availabilityies.Create(item);
            view.Show(string.Format("Предмет с Id = {0} был добавлен в репозиторий {1}", item.Id, nameof(availabilityies)));
        }

        public void AddCost(Cost item)
        {
            costs.Create(item);
            view.Show(string.Format("Предмет с Id = {0} был добавлен в репозиторий {1}", item.AvailabilityId, nameof(costs)));
        }

        public void AddCostStory(CostStory item)
        {
            costStories.Create(item);
            view.Show(string.Format("Предмет с Id = {0} был добавлен в репозиторий {1}", item.Id, nameof(costStories)));
        }

        public void AddProduct(Product item)
        {
            products.Create(item);
            view.Show(string.Format("Предмет с Id = {0} был добавлен в репозиторий {1}", item.Id, nameof(products)));
        }

        public void AddSaleReceipt(SaleReceipt item)
        {
            saleReceipts.Create(item);
            view.Show(string.Format("Предмет с Id = {0} был добавлен в репозиторий {1}", item.Id, nameof(saleReceipts)));
        }

        public void AddSaleReceiptPosition(SaleReceiptPosition item)
        {
            saleReceiptPositions.Create(item);
            view.Show(string.Format("Предмет с Id = {0} был добавлен в репозиторий {1}", item.Id, nameof(saleReceiptPositions)));
        }

        public void AddShop(Shop item)
        {
            shops.Create(item);
            view.Show(string.Format("Предмет с Id = {0} был добавлен в репозиторий {1}", item.Id, nameof(shops)));
        }

        public void DeleteAvailability(Availability item)
        {
            availabilityies.Delete(item);
            view.Show(string.Format("Предмет с Id = {0} был удалён из репозитория {1}", item.Id, nameof(availabilityies)));
        }

        public void DeleteCost(Cost item)
        {
            costs.Delete(item);
            view.Show(string.Format("Предмет с Id = {0} был удалён из репозитория {1}", item.AvailabilityId, nameof(costs)));
        }

        public void DeleteCostStory(CostStory item)
        {
            costStories.Delete(item);
            view.Show(string.Format("Предмет с Id = {0} был удалён из репозитория {1}", item.Id, nameof(costStories)));
        }

        public void DeleteProduct(Product item)
        {
            products.Delete(item);
            view.Show(string.Format("Предмет с Id = {0} был удалён из репозитория {1}", item.Id, nameof(products)));
        }

        public void DeleteSaleReceipt(SaleReceipt item)
        {
            saleReceipts.Delete(item);
            view.Show(string.Format("Предмет с Id = {0} был удалён из репозитория {1}", item.Id, nameof(saleReceipts)));
        }

        public void DeleteSaleReceiptPosition(SaleReceiptPosition item)
        {
            saleReceiptPositions.Delete(item);
            view.Show(string.Format("Предмет с Id = {0} был удалён из репозитория {1}", item.Id, nameof(saleReceiptPositions)));
        }

        public void DeleteShop(Shop item)
        {
            shops.Delete(item);
            view.Show(string.Format("Предмет с Id = {0} был удалён из репозитория {1}", item.Id, nameof(shops)));
        }

        public void GetAllAvailabilities()
        {
            var items = availabilityies.GetAll();
            StringBuilder builder = new StringBuilder("Таблица Availability:\n", 256);

            foreach (var item in items)
            {
                builder.AppendLine($"{item.Id} | {item.ProductId} | {item.ShopId} ");
            }

            view.Show(builder.ToString());
        }

        public void GetAllCosts()
        {
            var items = costs.GetAll();
            StringBuilder builder = new StringBuilder("Таблица Costs:\n", 256);

            foreach (var item in items)
            {
                builder.AppendLine($"{item.AvailabilityId} | {item.CostValue} ");
            }

            view.Show(builder.ToString());
        }

        public void GetAllCostStories()
        {
            var items = costStories.GetAll();
            StringBuilder builder = new StringBuilder("Таблица CostStory:\n", 256);

            foreach (var item in items)
            {
                builder.AppendLine($"{item.Id} | {item.Year} | {item.Month} | {item.Cost} | {item.AvailabilityId} ");
            }

            view.Show(builder.ToString());
        }

        public void GetAllProducts()
        {
            var items = products.GetAll();
            StringBuilder builder = new StringBuilder("Таблица Products:\n", 256);

            foreach (var item in items)
            {
                builder.AppendLine($"{item.Id} | {item.Name} | {item.ProductType} ");
            }

            view.Show(builder.ToString());
        }

        public void GetAllSaleReceiptPositions()
        {
            var items = saleReceiptPositions.GetAll();
            StringBuilder builder = new StringBuilder("Таблица SaleReceiptPositions:\n", 256);

            foreach (var item in items)
            {
                builder.AppendLine($"{item.Id} | {item.SaleReceiptId} | {item.AvailabilityId} ");
            }

            view.Show(builder.ToString());
        }

        public void GetAllSaleReceipts()
        {
            var items = saleReceipts.GetAll();
            StringBuilder builder = new StringBuilder("Таблица SaleReceipts:\n", 256);

            foreach (var item in items)
            {
                builder.AppendLine($"{item.Id} | {item.Fio} | {item.DateOfPurchase} | {item.ShopId} ");
            }

            view.Show(builder.ToString());
        }

        public void GetAllShops()
        {
            var items = shops.GetAll();
            StringBuilder builder = new StringBuilder("Таблица Shops:\n", 256);

            foreach (var item in items)
            {
                builder.AppendLine($"{item.Id} | {item.Name} | {item.Description} ");
            }

            view.Show(builder.ToString());
        }

        public void GetAvailability(int id)
        {
            var item = availabilityies.Get(id);
            
            view.Show($"{item.Id}, {item.ProductId}, {item.ShopId} ");
        }

        public void GetCost(int id)
        {
            var item = costs.Get(id);

            view.Show($"{item.AvailabilityId}, {item.CostValue} ");
        }

        public void GetCostStory(int id)
        {
            var item = costStories.Get(id);

            view.Show($"{item.Id}, {item.Year}, {item.Month}, {item.Cost}, {item.AvailabilityId} ");
        }

        public void GetProduct(int id)
        {
            var item = products.Get(id);

            view.Show($"{item.Id}, {item.Name}, {item.ProductType} ");
        }

        public void GetSaleReceipt(int id)
        {
            var item = saleReceipts.Get(id);

            view.Show($"{item.Id}, {item.Fio}, {item.DateOfPurchase}, {item.ShopId} ");
        }

        public void GetSaleReceiptPosition(int id)
        {
            var item = saleReceiptPositions.Get(id);

            view.Show($"{item.Id}, {item.SaleReceiptId}, {item.AvailabilityId} ");
        }

        public void GetShop(int id)
        {
            var item = shops.Get(id);

            view.Show($"{item.Id}, {item.Name}, {item.Description} ");
        }

        public void UpdateAvailability(Availability item)
        {
            availabilityies.Update(item);
            view.Show(string.Format("Предмет с Id = {0} был был обновлён в репозитории {1}", item.Id, nameof(availabilityies)));
        }

        public void UpdateCost(Cost item)
        {
            costs.Update(item);
            view.Show(string.Format("Предмет с Id = {0} был был обновлён в репозитории {1}", item.AvailabilityId, nameof(costs)));
        }

        public void UpdateCostStory(CostStory item)
        {
            costStories.Update(item);
            view.Show(string.Format("Предмет с Id = {0} был был обновлён в репозитории {1}", item.Id, nameof(costStories)));
        }

        public void UpdateProduct(Product item)
        {
            products.Update(item);
            view.Show(string.Format("Предмет с Id = {0} был был обновлён в репозитории {1}", item.Id, nameof(products)));
        }

        public void UpdateSaleReceipt(SaleReceipt item)
        {
            saleReceipts.Update(item);
            view.Show(string.Format("Предмет с Id = {0} был был обновлён в репозитории {1}", item.Id, nameof(saleReceipts)));
        }

        public void UpdateSaleReceiptPosition(SaleReceiptPosition item)
        {
            saleReceiptPositions.Update(item);
            view.Show(string.Format("Предмет с Id = {0} был был обновлён в репозитории {1}", item.Id, nameof(saleReceiptPositions)));
        }

        public void UpdateShop(Shop item)
        {
            shops.Update(item);
            view.Show(string.Format("Предмет с Id = {0} был был обновлён в репозитории {1}", item.Id, nameof(shops)));
        }
    }
}
