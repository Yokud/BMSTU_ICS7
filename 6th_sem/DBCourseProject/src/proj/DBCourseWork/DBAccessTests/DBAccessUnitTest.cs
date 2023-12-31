using DataBaseUI.SysEntities;

namespace DBAccessTests
{
    public class DBAccessUnitTest
    {
        [Fact]
        public void TestShopsRepository()
        {
            PgSQLShopsRepository rep = new PgSQLShopsRepository();

            // Get
            Shop shop = rep.Get(1);
            Assert.Equal(shop.Name, "Похороны");

            // Create
            Shop newShop = new Shop("123", "123");
            rep.Create(newShop);
            Assert.Equal(rep.GetAll().Where(x => x.Name == "123").First().Name, "123");

            // Update
            newShop.Name = "456";
            rep.Update(newShop);
            Assert.Equal(rep.GetAll().Where(x => x.Name == "456").First().Name, "456");

            // Delete
            rep.Delete(newShop);
            Assert.Equal(rep.GetAll().Where(x => x.Name == "456").ToList(), new List<Shop>());
        }

        [Fact]
        public void TestProductsRepository()
        {
            PgSQLProductsRepository rep = new PgSQLProductsRepository();

            // Get
            Product prod = rep.Get(1);
            Assert.Equal(prod.Name, "Коляска Adamex Barletta 2 in 1");

            // Create
            Product newProd = new Product("123", "123");
            rep.Create(newProd);
            Assert.Equal(rep.GetAll().Where(x => x.Name == "123").First().Name, "123");

            // Update
            newProd.Name = "456";
            rep.Update(newProd);
            Assert.Equal(rep.GetAll().Where(x => x.Name == "456").First().Name, "456");

            // Delete
            rep.Delete(newProd);
            Assert.Equal(rep.GetAll().Where(x => x.Name == "456").ToList(), new List<Product>());
        }

        [Fact]
        public void TestSaleReceiptsRepository()
        {
            PgSQLSaleReceiptsRepository rep = new PgSQLSaleReceiptsRepository();

            // Get
            SaleReceipt sr = rep.Get(1);
            Assert.Equal(sr.Fio, "Полякова Ангелина Тимофеевна");

            // Create
            SaleReceipt newSr = new SaleReceipt("123", new DateOnly(1, 1, 1), 1);
            rep.Create(newSr);
            Assert.Equal(rep.GetAll().Where(x => x.Fio == "123").First().Fio, "123");

            // Update
            newSr.Fio = "456";
            rep.Update(newSr);
            Assert.Equal(rep.GetAll().Where(x => x.Fio == "456").First().Fio, "456");

            // Delete
            rep.Delete(newSr);
            Assert.Equal(rep.GetAll().Where(x => x.Fio == "456").ToList(), new List<SaleReceipt>());
        }

        [Fact]
        public void TestSaleReceiptPositionsRepository()
        {
            PgSQLSaleReceiptPositionsRepository rep = new PgSQLSaleReceiptPositionsRepository();

            // Get
            SaleReceiptPosition sr = rep.Get(1);
            Assert.Equal(sr.AvailabilityId, 6801);

            // Create
            SaleReceiptPosition newSr = new SaleReceiptPosition(123, 1);
            rep.Create(newSr);
            Assert.Equal(rep.GetAll().Where(x => x.Id == 10053).First().AvailabilityId, 123);

            // Update
            newSr.AvailabilityId = 456;
            rep.Update(newSr);
            Assert.Equal(rep.GetAll().Where(x => x.Id == 10053).First().AvailabilityId, 456);

            // Delete
            rep.Delete(newSr);
            Assert.Equal(rep.GetAll().Where(x => x.Id == 10053).ToList(), new List<SaleReceiptPosition>());
        }

        [Fact]
        public void TestCostsRepository()
        {
            PgSQLCostsRepository rep = new PgSQLCostsRepository();

            // Get
            Cost c = rep.Get(1);
            Assert.Equal(c.CostValue, 5652);
        }

        [Fact]
        public void TestCostStoriesRepository()
        {
            PgSQLCostStoryRepository rep = new PgSQLCostStoryRepository();

            // Get
            CostStory cs = rep.Get(1);
            Assert.Equal(cs.Cost, 5522);

            // Create
            CostStory newCs = new CostStory(2022, 1, 666, 123);
            rep.Create(newCs);
            Assert.Equal(rep.GetAll().Where(x => x.Id == 188893).First().AvailabilityId, 123);

            // Update
            newCs.AvailabilityId = 456;
            rep.Update(newCs);
            Assert.Equal(rep.GetAll().Where(x => x.Id == 188893).First().AvailabilityId, 456);

            // Delete
            rep.Delete(newCs);
            Assert.Equal(rep.GetAll().Where(x => x.Id == 188893).ToList(), new List<CostStory>());
        }
    }
}