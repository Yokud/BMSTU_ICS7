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
    public class PgSQLSaleReceiptPositionsRepository : ISaleReceiptPositionsRepository
    {
        SpsrLtDbContext db;
        IEnumerable<SaleReceiptPosition> saleReceiptPositions;

        ILogger logger;

        public PgSQLSaleReceiptPositionsRepository(ILogger logger = null)
        {
            db = new SpsrLtDbContext();
            if (db.IsAdmin)
            {
                saleReceiptPositions = new ObservableCollection<SaleReceiptPosition>();
                db.SaleReceiptPositions.Load();
                foreach (var srp in db.SaleReceiptPositions)
                    ((ObservableCollection<SaleReceiptPosition>)saleReceiptPositions).Add(new SaleReceiptPosition(srp.Id, srp.Availabilityid, srp.Salereceiptid));
            }
            this.logger = logger;
        }

        public PgSQLSaleReceiptPositionsRepository(SpsrLtDbContext spsr, ILogger logger = null)
        {
            db = spsr;
            if (db.IsAdmin)
            {
                saleReceiptPositions = new ObservableCollection<SaleReceiptPosition>();
                db.SaleReceiptPositions.Load();
                foreach (var srp in db.SaleReceiptPositions)
                    ((ObservableCollection<SaleReceiptPosition>)saleReceiptPositions).Add(new SaleReceiptPosition(srp.Id, srp.Availabilityid, srp.Salereceiptid));
            }
            this.logger = logger;
        }

        public void Create(SaleReceiptPosition item)
        {
            if (db.IsAdmin)
            {
                try
                {
                    db.SaleReceiptPositions.Add(new EFSaleReceiptPosition() { Id = db.SaleReceiptPositions.Count() != 0 ? db.SaleReceiptPositions.Max(x => x.Id) + 1 : 0, Availabilityid = item.AvailabilityId, Salereceiptid = item.SaleReceiptId });
                    db.SaveChanges();
                    item.Id = db.SaleReceiptPositions.Max(x => x.Id);
                    ((ObservableCollection<SaleReceiptPosition>)saleReceiptPositions).Add(item);

                    logger?.LogInformation(string.Format("Sale receipt position with id = {0} was added.\n", item.Id));
                }
                catch (Exception e)
                {
                    Trace.WriteLine(e.Message);
                    logger?.LogError(e.Message);
                }
            }
        }

        public void Delete(SaleReceiptPosition item)
        {
            if (db.IsAdmin)
            {
                try
                {
                    db.SaleReceiptPositions.Remove(db.SaleReceiptPositions.Find(item.Id));
                    db.SaveChanges();
                    ((ObservableCollection<SaleReceiptPosition>)saleReceiptPositions).Remove(item);

                    logger?.LogInformation(string.Format("Sale receipt position with id = {0} was deleted.\n", item.Id));
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

        public SaleReceiptPosition Get(int id)
        {
            if (db.IsAdmin)
            {
                try
                {
                    var elem = db.SaleReceiptPositions.Find(id);

                    if (elem != null)
                        return new SaleReceiptPosition(elem.Id, elem.Availabilityid, elem.Salereceiptid);
                    else
                        throw new Exception("Can\'t find sale receipt position.\n");
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

        public IEnumerable<SaleReceiptPosition> GetAll()
        {
            if (db.IsAdmin)
            {
                return saleReceiptPositions;
            }

            return null;
        }

        public IEnumerable<Product> GetAllFromSaleReceipt(SaleReceipt saleReceipt)
        {
            if (db.IsAdmin)
            {
                try
                {
                    var conn = (NpgsqlConnection?)db.Database.GetDbConnection();
                    if (conn.State != ConnectionState.Open)
                        conn.Open();
                    if (conn.State == ConnectionState.Executing)
                        conn.Wait();
                    string cmd = string.Format("select * from get_content_from_salereceipt({0})", saleReceipt.Id);
                    NpgsqlCommand command = new NpgsqlCommand(cmd, conn);
                    ObservableCollection<Product> products = new ObservableCollection<Product>();

                    using (NpgsqlDataReader reader = command.ExecuteReader())
                        while (reader.Read())
                            products.Add(new Product((int)reader.GetDouble(0), reader.GetString(1), reader.GetString(2), (int?)reader.GetDouble(3)));

                    conn.Close();
                    return products;
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

        public void Save()
        {
            db.SaveChanges();
        }

        public void Update(SaleReceiptPosition item)
        {
            if (db.IsAdmin)
            {
                try
                {
                    EFSaleReceiptPosition srp = db.SaleReceiptPositions.Find(item.Id);

                    srp.Salereceiptid = item.SaleReceiptId;
                    srp.Availabilityid = item.AvailabilityId;

                    db.SaleReceiptPositions.Update(srp);
                    db.SaveChanges();

                    for (int i = 0; i < saleReceiptPositions.Count(); i++)
                        if (((ObservableCollection<SaleReceiptPosition>)saleReceiptPositions)[i].Id == item.Id)
                        {
                            ((ObservableCollection<SaleReceiptPosition>)saleReceiptPositions)[i].AvailabilityId = item.AvailabilityId;
                            ((ObservableCollection<SaleReceiptPosition>)saleReceiptPositions)[i].SaleReceiptId = item.SaleReceiptId;
                            break;
                        }

                    logger?.LogInformation(string.Format("Sale receipt position with id = {0} was updated.\n", item.Id));
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
