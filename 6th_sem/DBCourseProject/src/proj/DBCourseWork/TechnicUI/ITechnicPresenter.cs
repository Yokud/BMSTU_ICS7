using DataBaseUI.Models;
using DataBaseUI.SysEntities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TechnicUI
{
    public interface ITechnicPresenter
    {
        IShopsRepository Shops { get; set; }
        IProductsRepository Products { get; set; }
        ISaleReceiptsRepository SaleReceipts { get; set; }
        ISaleReceiptPositionsRepository SaleReceiptPositions { get; set; }
        ICostsRepository Costs { get; set; }
        ICostStoryRepository CostStories { get; set; }
        IAvailabilityRepository Availabilityies { get; set; }

        ITechnicView View { get; set; }

        void AddShop(Shop item);
        void DeleteShop(Shop item);
        void UpdateShop(Shop item);
        void GetShop(int id);
        void GetAllShops();

        void AddProduct(Product item);
        void DeleteProduct(Product item);
        void UpdateProduct(Product item);
        void GetProduct(int id);
        void GetAllProducts();

        void AddAvailability(Availability item);
        void DeleteAvailability(Availability item);
        void UpdateAvailability(Availability item);
        void GetAvailability(int id);
        void GetAllAvailabilities();

        void AddSaleReceipt(SaleReceipt item);
        void DeleteSaleReceipt(SaleReceipt item);
        void UpdateSaleReceipt(SaleReceipt item);
        void GetSaleReceipt(int id);
        void GetAllSaleReceipts();

        void AddSaleReceiptPosition(SaleReceiptPosition item);
        void DeleteSaleReceiptPosition(SaleReceiptPosition item);
        void UpdateSaleReceiptPosition(SaleReceiptPosition item);
        void GetSaleReceiptPosition(int id);
        void GetAllSaleReceiptPositions();

        void AddCost(Cost item);
        void DeleteCost(Cost item);
        void UpdateCost(Cost item);
        void GetCost(int id);
        void GetAllCosts();

        void AddCostStory(CostStory item);
        void DeleteCostStory(CostStory item);
        void UpdateCostStory(CostStory item);
        void GetCostStory(int id);
        void GetAllCostStories();
    }
}
