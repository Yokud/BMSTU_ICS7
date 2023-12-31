using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Data;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DataBaseUI.DB;
using DataBaseUI.SysEntities;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Logging;
using Npgsql;

namespace DataBaseUI.Models
{
    public class PgSQLCostStoryRepository : ICostStoryRepository
    {
        SpsrLtDbContext db;
        IEnumerable<CostStory> stories;

        ILogger logger;

        public PgSQLCostStoryRepository(ILogger logger = null)
        {
            db = new SpsrLtDbContext();
            if (db.IsAnalyst || db.IsAdmin)
            {
                stories = new ObservableCollection<CostStory>();
                db.CostStories.Load();

                foreach (var cs in db.CostStories)
                    ((ObservableCollection<CostStory>)stories).Add(new CostStory(cs.Id, cs.Year, cs.Month, cs.Cost, cs.Availabilityid));
            }
            this.logger = logger;
        }

        public PgSQLCostStoryRepository(SpsrLtDbContext spsr, ILogger logger = null)
        {
            db = spsr;
            if (db.IsAnalyst || db.IsAdmin)
            {
                stories = new ObservableCollection<CostStory>();
                db.CostStories.Load();

                foreach (var cs in db.CostStories)
                    ((ObservableCollection<CostStory>)stories).Add(new CostStory(cs.Id, cs.Year, cs.Month, cs.Cost, cs.Availabilityid));
            }
            this.logger = logger;
        }

        public void Create(CostStory item)
        {
            if (db.IsAdmin)
            {
                try
                {
                    db.CostStories.Add(new EFCostStory() { Id = db.CostStories.Count() != 0 ? db.CostStories.Max(x => x.Id) + 1 : 0, Year = item.Year, Month = item.Month, Availabilityid = item.AvailabilityId, Cost = item.Cost });
                    db.SaveChanges();
                    item.Id = db.CostStories.Max(x => x.Id);
                    ((ObservableCollection<CostStory>)stories).Add(item);

                    logger?.LogInformation(string.Format("Cost story with id = {0} was added.\n", item.Id));
                }
                catch (Exception e)
                {
                    Trace.WriteLine(e.Message);
                    logger?.LogError(e.Message);
                }
            }
        }

        public void Delete(CostStory item)
        {
            if (db.IsAdmin)
            {
                try
                {
                    db.CostStories.Remove(db.CostStories.Find(item.Id));
                    db.SaveChanges();
                    ((ObservableCollection<CostStory>)stories).Remove(item);
                    logger?.LogInformation(string.Format("Cost story with id = {0} was deleted.\n", item.Id));
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

        public CostStory Get(int id)
        {
            if (db.IsAnalyst || db.IsAdmin)
            {
                try
                {
                    var elem = db.CostStories.Find(id);

                    if (elem != null)
                        return new CostStory(elem.Id, elem.Year, elem.Month, elem.Cost, elem.Availabilityid);
                    else
                        throw new Exception("Can\'t find cost story elem.\n");
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

        public IEnumerable<CostStory> GetAll()
        {
            if (db.IsAnalyst || db.IsAdmin)
            {
                return stories;
            }

            return null;
        }

        public IEnumerable<CostStory> GetFullCostStory(Shop shop, Product product)
        {
            if (db.IsAnalyst || db.IsAdmin)
            {
                var conn = (NpgsqlConnection?)db.Database.GetDbConnection();
                if (conn.State != ConnectionState.Open)
                    conn.Open();

                string cmd = string.Format("select * from get_coststory_by_shopid_prodid({0}, {1})", shop.Id, product.Id);
                NpgsqlCommand command = new NpgsqlCommand(cmd, conn);

                ObservableCollection<CostStory> story = new ObservableCollection<CostStory>();

                using (NpgsqlDataReader reader = command.ExecuteReader())
                    while (reader.Read())
                        story.Add(new CostStory((int)reader.GetDouble(0), (int)reader.GetDouble(1), (int)reader.GetDouble(2), (int)reader.GetDouble(3), (int)reader.GetDouble(4)));

                conn.Close();
                return story;
            }

            return null;
        }

        public void Save()
        {
            db.SaveChanges();
        }

        public void Update(CostStory item)
        {
            if (db.IsAdmin)
            {
                try
                {
                    EFCostStory c = db.CostStories.Find(item.Id);

                    c.Year = item.Year;
                    c.Month = item.Month;
                    c.Cost = item.Cost;
                    c.Availabilityid = item.AvailabilityId;

                    db.CostStories.Update(c);
                    db.SaveChanges();

                    for (int i = 0; i < stories.Count(); i++)
                        if (((ObservableCollection<CostStory>)stories)[i].Id == item.Id)
                        {
                            ((ObservableCollection<CostStory>)stories)[i].Year = item.Year;
                            ((ObservableCollection<CostStory>)stories)[i].Month = item.Month;
                            ((ObservableCollection<CostStory>)stories)[i].Cost = item.Cost;
                            ((ObservableCollection<CostStory>)stories)[i].AvailabilityId = item.AvailabilityId;
                            break;
                        }

                    logger?.LogInformation(string.Format("Cost story with id = {0} was updated.\n", item.Id));
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
