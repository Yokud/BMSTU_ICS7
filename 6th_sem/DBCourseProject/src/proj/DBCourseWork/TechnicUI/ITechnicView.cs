using DataBaseUI.SysEntities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TechnicUI
{
    public interface ITechnicView
    {
        delegate void AddShopDel(Shop shop);
        event AddShopDel AddShopEvent;

        delegate void DeleteShopDel(Shop shop);
        event DeleteShopDel DeleteShopEvent;

        delegate void UpdateShopDel(Shop shop);
        event UpdateShopDel UpdateShopEvent;

        delegate void GetShopDel(int id);
        event GetShopDel GetShopEvent;

        delegate void GetAllShopsDel();
        event GetAllShopsDel GetAllShopsEvent;

        void AddShop();
        void DeleteShop();
        void UpdateShop();
        void GetShop();
        void GetAllShops();


        delegate void AddProductDel(Product product);
        event AddProductDel AddProductEvent;

        delegate void DeleteProductDel(Product prodcut);
        event DeleteProductDel DeleteProductEvent;

        delegate void UpdateProductDel(Product product);
        event UpdateProductDel UpdateProductEvent;

        delegate void GetProductDel(int id);
        event GetProductDel GetProductEvent;

        delegate void GetAllProductsDel();
        event GetAllProductsDel GetAllProductsEvent;

        void AddProduct();
        void DeleteProduct();
        void UpdateProduct();
        void GetProduct();
        void GetAllProducts();


        delegate void AddAvailabilityDel(Availability availability);
        event AddAvailabilityDel AddAvailabilityEvent;

        delegate void DeleteAvailabilityDel(Availability availability);
        event DeleteAvailabilityDel DeleteAvailabilityEvent;

        delegate void UpdateAvailabilityDel(Availability availability);
        event UpdateAvailabilityDel UpdateAvailabilityEvent;

        delegate void GetAvailabilityDel(int id);
        event GetAvailabilityDel GetAvailabilityEvent;

        delegate void GetAllAvailabilitiesDel();
        event GetAllAvailabilitiesDel GetAllAvailabilitiesEvent;

        void AddAvailability();
        void DeleteAvailability();
        void UpdateAvailability();
        void GetAvailability();
        void GetAllAvailabilities();


        delegate void AddSaleReceiptDel(SaleReceipt sr);
        event AddSaleReceiptDel AddSaleReceiptEvent;

        delegate void DeleteSaleReceiptDel(SaleReceipt sr);
        event DeleteSaleReceiptDel DeleteSaleReceiptEvent;

        delegate void UpdateSaleReceiptDel(SaleReceipt sr);
        event UpdateSaleReceiptDel UpdateSaleReceiptEvent;

        delegate void GetSaleReceiptDel(int id);
        event GetSaleReceiptDel GetSaleReceiptEvent;

        delegate void GetAllSaleReceiptsDel();
        event GetAllSaleReceiptsDel GetAllSaleReceiptsEvent;

        void AddSaleReceipt();
        void DeleteSaleReceipt();
        void UpdateSaleReceipt();
        void GetSaleReceipt();
        void GetAllSaleReceipts();


        delegate void AddSaleReceiptPositionDel(SaleReceiptPosition srp);
        event AddSaleReceiptPositionDel AddSaleReceiptPositionEvent;

        delegate void DeleteSaleReceiptPositionDel(SaleReceiptPosition srp);
        event DeleteSaleReceiptPositionDel DeleteSaleReceiptPositionEvent;

        delegate void UpdateSaleReceiptPositionDel(SaleReceiptPosition srp);
        event UpdateSaleReceiptPositionDel UpdateSaleReceiptPositionEvent;

        delegate void GetSaleReceiptPositionDel(int id);
        event GetSaleReceiptPositionDel GetSaleReceiptPositionEvent;

        delegate void GetAllSaleReceiptPositionsDel();
        event GetAllSaleReceiptPositionsDel GetAllSaleReceiptPositionsEvent;

        void AddSaleReceiptPosition();
        void DeleteSaleReceiptPosition();
        void UpdateSaleReceiptPosition();
        void GetSaleReceiptPosition();
        void GetAllSaleReceiptPositions();


        delegate void AddCostDel(Cost cost);
        event AddCostDel AddCostEvent;

        delegate void DeleteCostDel(Cost cost);
        event DeleteCostDel DeleteCostEvent;

        delegate void UpdateCostDel(Cost cost);
        event UpdateCostDel UpdateCostEvent;

        delegate void GetCostDel(int id);
        event GetCostDel GetCostEvent;

        delegate void GetAllCostsDel();
        event GetAllCostsDel GetAllCostsEvent;

        void AddCost();
        void DeleteCost();
        void UpdateCost();
        void GetCost();
        void GetAllCosts();


        delegate void AddCostStoryDel(CostStory costStory);
        event AddCostStoryDel AddCostStoryEvent;

        delegate void DeleteCostStoryDel(CostStory costStory);
        event DeleteCostStoryDel DeleteCostStoryEvent;

        delegate void UpdateCostStoryDel(CostStory costStory);
        event UpdateCostStoryDel UpdateCostStoryEvent;

        delegate void GetCostStoryDel(int id);
        event GetCostStoryDel GetCostStoryEvent;

        delegate void GetAllCostStoriesDel();
        event GetAllCostStoriesDel GetAllCostStoriesEvent;
        void AddCostStory();
        void DeleteCostStory();
        void UpdateCostStory();
        void GetCostStory();
        void GetAllCostStories();

        void Show(string message);
    }
}
