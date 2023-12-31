using DataBaseUI.DB;
using DataBaseUI.SysEntities;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DataBaseUI.Models
{
    public class PgSQLAvailabilityRepository : IAvailabilityRepository
    {
        SpsrLtDbContext db;
        IEnumerable<Availability> availabilities;

        ILogger logger;

        public PgSQLAvailabilityRepository(ILogger logger = null)
        {
            db = new SpsrLtDbContext();
            if (db.IsUser || db.IsAnalyst || db.IsAdmin)
            {
                availabilities = new ObservableCollection<Availability>();
                db.Availabilities.Load();
                foreach (var avail in db.Availabilities)
                    ((ObservableCollection<Availability>)availabilities).Add(new Availability(avail.Id, avail.Shopid, avail.Productid));
            }
            this.logger = logger;
        }

        public PgSQLAvailabilityRepository(SpsrLtDbContext spsr, ILogger logger = null)
        {
            db = spsr;
            if (db.IsUser || db.IsAnalyst || db.IsAdmin)
            {
                availabilities = new ObservableCollection<Availability>();
                db.Availabilities.Load();
                foreach (var avail in db.Availabilities)
                    ((ObservableCollection<Availability>)availabilities).Add(new Availability(avail.Id, avail.Shopid, avail.Productid));
            }
            this.logger = logger;
        }

        public void Create(Availability item)
        {
            if (db.IsAdmin)
            {
                try
                {
                    db.Availabilities.Add(new EFAvailability() { Id = db.Availabilities.Count() != 0 ? db.Availabilities.Max(x => x.Id) + 1 : 0, Shopid = item.ShopId, Productid = item.ProductId });
                    db.SaveChanges();
                    item.Id = db.Availabilities.Max(x => x.Id);
                    ((ObservableCollection<Availability>)availabilities).Add(item);

                    logger?.LogInformation(string.Format("Availability with id = {0} was added.\n", item.Id));
                }
                catch (Exception e)
                {
                    Trace.WriteLine(e.Message);
                    logger?.LogError(e.Message);
                }
            }
        }

        public void Delete(Availability item)
        {
            if (db.IsAdmin)
            {
                try
                {
                    db.Availabilities.Remove(db.Availabilities.Find(item.Id));
                    db.SaveChangesAsync();
                    ((ObservableCollection<Availability>)availabilities).Remove(item);

                    logger?.LogInformation(string.Format("Availability with id = {0} was deleted.\n", item.Id));
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

        public Availability Get(int id)
        {
            if (db.IsUser || db.IsAnalyst || db.IsAdmin)
            {
                try
                {
                    var elem = db.Availabilities.Find(id);

                    if (elem != null)
                        return new Availability(elem.Id, elem.Shopid, elem.Productid);
                    else
                        throw new Exception("Can\'t find availability.\n");
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

        public IEnumerable<Availability> GetAll()
        {
            if (db.IsUser || db.IsAnalyst || db.IsAdmin)
            {
                return availabilities;
            }

            return null;
        }

        public void Save()
        {
            db.SaveChangesAsync();
        }

        public void Update(Availability item)
        {
            if (db.IsAdmin)
            {
                try
                {
                    var avail = db.Availabilities.Find(item.Id);

                    avail.Shopid = item.ShopId;
                    avail.Productid = item.ProductId;

                    db.Availabilities.Update(avail);
                    db.SaveChanges();

                    for (int i = 0; i < availabilities.Count(); i++)
                        if (((ObservableCollection<Availability>)availabilities)[i].Id == item.Id)
                        {
                            ((ObservableCollection<Availability>)availabilities)[i].ShopId = item.ShopId;
                            ((ObservableCollection<Availability>)availabilities)[i].ProductId = item.ProductId;
                            break;
                        }

                    logger?.LogInformation(string.Format("Availability with id = {0} was updated.\n", item.Id));
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
