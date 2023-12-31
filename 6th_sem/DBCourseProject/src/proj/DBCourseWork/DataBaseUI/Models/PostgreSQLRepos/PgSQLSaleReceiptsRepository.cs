using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DataBaseUI.DB;
using DataBaseUI.SysEntities;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Logging;

namespace DataBaseUI.Models
{
    public class PgSQLSaleReceiptsRepository : ISaleReceiptsRepository
    {
        SpsrLtDbContext db;
        IEnumerable<SaleReceipt> saleReceipts;

        ILogger logger;

        public PgSQLSaleReceiptsRepository(ILogger logger = null)
        {
            db = new SpsrLtDbContext();
            if (db.IsAdmin)
            {
                saleReceipts = new ObservableCollection<SaleReceipt>();
                db.SaleReceipts.Load();
                foreach (var sr in db.SaleReceipts)
                    ((ObservableCollection<SaleReceipt>)saleReceipts).Add(new SaleReceipt(sr.Id, sr.Fio, sr.Dateofpurchase, sr.Shopid));
            }
            this.logger = logger;
        }

        public PgSQLSaleReceiptsRepository(SpsrLtDbContext spsr, ILogger logger)
        {
            db = spsr;
            if (db.IsAdmin)
            {
                saleReceipts = new ObservableCollection<SaleReceipt>();
                db.SaleReceipts.Load();
                foreach (var sr in db.SaleReceipts)
                    ((ObservableCollection<SaleReceipt>)saleReceipts).Add(new SaleReceipt(sr.Id, sr.Fio, sr.Dateofpurchase, sr.Shopid));
            }
            this.logger = logger;
        }

        public void Create(SaleReceipt item)
        {
            if (db.IsAdmin)
            {
                try
                {
                    db.SaleReceipts.Add(new EFSaleReceipt() { Id = db.SaleReceipts.Count() != 0 ? db.SaleReceipts.Max(x => x.Id) + 1 : 0, Fio = item.Fio, Dateofpurchase = item.DateOfPurchase, Shopid = item.ShopId });
                    db.SaveChanges();
                    item.Id = db.SaleReceipts.Max(x => x.Id);
                    ((ObservableCollection<SaleReceipt>)saleReceipts).Add(item);

                    logger?.LogInformation(string.Format("Sale receipt with id = {0} was added.\n", item.Id));
                }
                catch (Exception e)
                {
                    Trace.WriteLine(e.Message);
                    logger?.LogError(e.Message);
                }
            }
        }

        public void Delete(SaleReceipt item)
        {
            if (db.IsAdmin)
            {
                try
                {
                    db.SaleReceipts.Remove(db.SaleReceipts.Find(item.Id));
                    db.SaveChanges();
                    ((ObservableCollection<SaleReceipt>)saleReceipts).Remove(item);
                    logger?.LogInformation(string.Format("Sale receipt with id = {0} was deleted.\n", item.Id));
                }
                catch (Exception e)
                {
                    Trace.WriteLine(e.Message);
                    logger?.LogError(e.Message);
                }
            }
        }

        public void Dispose()
        {
            db.Dispose();
        }

        public SaleReceipt Get(int id)
        {
            if (db.IsAdmin)
            {
                try
                {
                    var elem = db.SaleReceipts.Find(id);

                    if (elem != null)
                        return new SaleReceipt(elem.Id, elem.Fio, elem.Dateofpurchase, elem.Shopid);
                    else
                        throw new Exception("Can\'t find sale receipt.\n");
                }
                catch (Exception e)
                {
                    Trace.WriteLine(e.Message);
                    logger?.LogError(e.Message);
                    return null;
                }
            }

            return null;
        }

        public IEnumerable<SaleReceipt> GetAll()
        {
            if (db.IsAdmin)
            {
                return saleReceipts;
            }

            return null;
        }

        public IEnumerable<SaleReceipt> GetAllFromShop(Shop shop)
        {
            if (db.IsAdmin)
            {
                return saleReceipts.Where(x => x.ShopId == shop.Id);
            }
            return null;
        }

        public void Save()
        {
            db.SaveChanges();
        }

        public void Update(SaleReceipt item)
        {
            if (db.IsAdmin)
            {
                try
                {
                    EFSaleReceipt sr = db.SaleReceipts.Find(item.Id);

                    sr.Fio = item.Fio;
                    sr.Dateofpurchase = item.DateOfPurchase;
                    sr.Shopid = item.ShopId;

                    db.SaleReceipts.Update(sr);
                    db.SaveChanges();

                    for (int i = 0; i < saleReceipts.Count(); i++)
                        if (((ObservableCollection<SaleReceipt>)saleReceipts)[i].Id == item.Id)
                        {
                            ((ObservableCollection<SaleReceipt>)saleReceipts)[i].Fio = item.Fio;
                            ((ObservableCollection<SaleReceipt>)saleReceipts)[i].DateOfPurchase = item.DateOfPurchase;
                            ((ObservableCollection<SaleReceipt>)saleReceipts)[i].ShopId = item.ShopId;
                            break;
                        }

                    logger?.LogInformation(string.Format("Sale receipt with id = {0} was updated.\n", item.Id));
                }
                catch (Exception e)
                {
                    Trace.WriteLine(e.Message);
                    logger?.LogError(e.Message);
                }
            }
        }
    }
}
