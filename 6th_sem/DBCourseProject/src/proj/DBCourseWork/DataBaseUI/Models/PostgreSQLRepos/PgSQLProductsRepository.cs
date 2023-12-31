using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Data;
using System.Data.SqlClient;
using System.Diagnostics;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using DataBaseUI.DB;
using DataBaseUI.SysEntities;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Logging;
using Npgsql;

namespace DataBaseUI.Models
{
    public class PgSQLProductsRepository : IProductsRepository
    {
        SpsrLtDbContext db;
        IEnumerable<Product> products;

        ILogger logger;

        public PgSQLProductsRepository(ILogger logger = null)
        {
            db = new SpsrLtDbContext();
            if (db.IsUser || db.IsAnalyst || db.IsAdmin)
            {
                products = new ObservableCollection<Product>();
                db.Products.Load();
                foreach (var prod in db.Products)
                    ((ObservableCollection<Product>)products).Add(new Product(prod.Id, prod.Name, prod.Producttype));
            }
            this.logger = logger;
        }

        public PgSQLProductsRepository(SpsrLtDbContext spsr, ILogger logger = null)
        {
            db = spsr;
            if (db.IsUser || db.IsAnalyst || db.IsAdmin)
            {
                products = new ObservableCollection<Product>();
                db.Products.Load();
                foreach (var prod in db.Products)
                    ((ObservableCollection<Product>)products).Add(new Product(prod.Id, prod.Name, prod.Producttype));
            }
            this.logger = logger;
        }

        public void Create(Product item)
        {
            if (db.IsAdmin)
            {
                try
                {
                    db.Products.Add(new EFProduct() { Id = db.Products.Count() != 0 ? db.Products.Max(x => x.Id) + 1 : 0, Name = item.Name, Producttype = item.ProductType });
                    db.SaveChanges();
                    item.Id = db.Products.Max(x => x.Id);
                    ((ObservableCollection<Product>)products).Add(item);
                    logger?.LogInformation(string.Format("Product with id = {0} was added.\n", item.Id));
                }
                catch (Exception e)
                {
                    Trace.WriteLine(e.Message);
                    logger?.LogError(e.Message);
                }
            }
        }

        public void Delete(Product item)
        {
            if (db.IsAdmin)
            {
                try
                {
                    db.Products.Remove(db.Products.Find(item.Id));
                    db.SaveChanges();
                    ((ObservableCollection<Product>)products).Remove(item);
                    logger?.LogInformation(string.Format("Product with id = {0} was deleted.\n", item.Id));
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

        public Product Get(int id)
        {
            if (db.IsUser || db.IsAnalyst || db.IsAdmin)
            {
                try
                {
                    var elem = db.Products.Find(id);

                    if (elem != null)
                        return new Product(elem.Id, elem.Name, elem.Producttype);
                    else
                        throw new Exception("Can\'t find product.\n");
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

        public IEnumerable<Product> GetAll()
        {
            if (db.IsUser || db.IsAnalyst || db.IsAdmin)
            {
                return products;
            }

            return null;
        }

        public void Save()
        {
            db.SaveChanges();
        }

        public void Update(Product item)
        {
            if (db.IsAdmin)
            {
                try
                {
                    EFProduct product = db.Products.Find(item.Id);

                    product.Name = item.Name;
                    product.Producttype = item.ProductType;

                    db.Products.Update(product);
                    db.SaveChanges();

                    for (int i = 0; i < products.Count(); i++)
                        if (((ObservableCollection<Product>)products)[i].Id == item.Id)
                        {
                            ((ObservableCollection<Product>)products)[i].Name = item.Name;
                            ((ObservableCollection<Product>)products)[i].ProductType = item.ProductType;
                            break;
                        }
                    logger?.LogInformation(string.Format("Product with id = {0} was updated.\n", item.Id));
                }
                catch (Exception e)
                {
                    Trace.WriteLine(e.Message);
                    logger?.LogError(e.Message);
                }
            }
        }

        public IEnumerable<Product> GetAllFromShop(Shop shop)
        {
            if (db.IsUser || db.IsAnalyst || db.IsAdmin)
            {
                try
                {
                    var conn = (NpgsqlConnection?)db.Database.GetDbConnection();
                    if (conn.State != ConnectionState.Open)
                        conn.Open();
                    if (conn.State == ConnectionState.Executing)
                        conn.Wait();
                    string cmd = string.Format("select * from get_products_by_shopid({0})", shop.Id);
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
    }
}
