using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using DataBaseUI.DB;
using DataBaseUI.SysEntities;
using System.Collections.ObjectModel;
using System.Diagnostics;
using Microsoft.Extensions.Logging;

namespace DataBaseUI.Models
{
    public class PgSQLShopsRepository : IShopsRepository
    {
        SpsrLtDbContext db;
        IEnumerable<Shop> shops;

        ILogger logger;

        public PgSQLShopsRepository(ILogger logger = null)
        {
            db = new SpsrLtDbContext();

            if (db.IsUser || db.IsAnalyst || db.IsAdmin)
            {
                shops = new ObservableCollection<Shop>();
                db.Shops.Load();
                foreach (var efshop in db.Shops)
                    ((ObservableCollection<Shop>)shops).Add(new Shop(efshop.Id, efshop.Name, efshop.Description));
            }
            this.logger = logger;
        }

        public PgSQLShopsRepository(SpsrLtDbContext spsr, ILogger logger = null)
        {
            db = spsr;
            if (db.IsUser || db.IsAnalyst || db.IsAdmin)
            {
                shops = new ObservableCollection<Shop>();
                db.Shops.Load();
                foreach (var efshop in db.Shops)
                    ((ObservableCollection<Shop>)shops).Add(new Shop(efshop.Id, efshop.Name, efshop.Description));
            }
            this.logger = logger;
        }

        public void Create(Shop item)
        {
            if (db.IsAdmin)
            {
                try
                {
                    db.Shops.Add(new EFShop() { Id = db.Shops.Count() != 0 ? db.Shops.Max(x => x.Id) + 1 : 0, Name = item.Name, Description = item.Description });
                    db.SaveChanges();
                    item.Id = db.Shops.Max(x => x.Id);
                    ((ObservableCollection<Shop>)shops).Add(item);

                    logger?.LogInformation(string.Format("Shop with id = {0} was added.\n", item.Id));
                }
                catch (Exception e)
                {
                    Trace.WriteLine(e.Message);
                    logger?.LogError(e.Message);
                }
            }
        }

        public void Delete(Shop item)
        {
            if (db.IsAdmin)
            {
                try
                {
                    db.Shops.Remove(db.Shops.Find(item.Id));
                    db.SaveChanges();
                    ((ObservableCollection<Shop>)shops).Remove(item);
                    logger?.LogInformation(string.Format("Shop with id = {0} was deleted.\n", item.Id));
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

        public Shop Get(int id)
        {
            if (db.IsUser || db.IsAnalyst || db.IsAdmin)
            {
                try
                {
                    var elem = db.Shops.Find(id);

                    if (elem != null)
                        return new Shop(elem.Id, elem.Name, elem.Description);
                    else
                        throw new Exception("Can\t find shop.\n");
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

        public IEnumerable<Shop> GetAll()
        {
            if (db.IsUser || db.IsAnalyst || db.IsAdmin)
            {
                return shops;
            }

            return null;
        }

        public void Save()
        {
            db.SaveChanges();
        }

        public void Update(Shop item)
        {
            if (db.IsAdmin)
            {
                try
                {
                    EFShop shop = db.Shops.Find(item.Id);

                    shop.Name = item.Name;
                    shop.Description = item.Description;

                    db.Shops.Update(shop);
                    db.SaveChanges();

                    for (int i = 0; i < shops.Count(); i++)
                        if (((ObservableCollection<Shop>)shops)[i].Id == item.Id)
                        {
                            ((ObservableCollection<Shop>)shops)[i].Name = item.Name;
                            ((ObservableCollection<Shop>)shops)[i].Description = item.Description;
                            break;
                        }

                    logger?.LogInformation(string.Format("Shop with id = {0} was updated.\n", item.Id));
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
