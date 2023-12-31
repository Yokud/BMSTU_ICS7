using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.Extensions.Configuration;

namespace DataBaseUI.DB
{
    enum Roles
    {
        User,
        Analyst,
        Admin
    }

    public partial class SpsrLtDbContext : DbContext
    {
        public SpsrLtDbContext()
        {
        }

        public SpsrLtDbContext(DbContextOptions<SpsrLtDbContext> options)
            : base(options)
        {
        }

        public virtual DbSet<EFAvailability> Availabilities { get; set; } = null!;
        public virtual DbSet<EFCost> Costs { get; set; } = null!;
        public virtual DbSet<EFCostStory> CostStories { get; set; } = null!;
        public virtual DbSet<EFProduct> Products { get; set; } = null!;
        public virtual DbSet<EFSaleReceipt> SaleReceipts { get; set; } = null!;
        public virtual DbSet<EFSaleReceiptPosition> SaleReceiptPositions { get; set; } = null!;
        public virtual DbSet<EFShop> Shops { get; set; } = null!;

        Roles role;

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            if (!optionsBuilder.IsConfigured)
            {
                var config = new ConfigurationBuilder().SetBasePath(Directory.GetCurrentDirectory()).AddJsonFile("appsettings.json").Build();
                string connectionString = config.GetConnectionString("DefaultConnection");
                role = Roles.Admin;
                optionsBuilder.UseNpgsql(connectionString);
            }
        }

        public void ChangeConnection(string mode, string password)
        {
            IConfigurationRoot config;
            string connectionString;

            switch (mode.ToLower())
            {
                case "user":
                    config = new ConfigurationBuilder().SetBasePath(Directory.GetCurrentDirectory()).AddJsonFile("appsettings.json").Build();
                    connectionString = config.GetConnectionString("UserConnection");
                    Database.SetConnectionString(connectionString);
                    role = Roles.User;
                    break;

                case "analyst":
                    config = new ConfigurationBuilder().SetBasePath(Directory.GetCurrentDirectory()).AddJsonFile("appsettings.json").Build();
                    connectionString = config.GetConnectionString("AnalystConnection");

                    string actualPassword = connectionString.Split(';').Last().Split('=').Last();

                    if (password != actualPassword)
                        throw new Exception("Неверный пароль!");

                    Database.SetConnectionString(connectionString);
                    role = Roles.Analyst;
                    break;

                case "admin":
                    config = new ConfigurationBuilder().SetBasePath(Directory.GetCurrentDirectory()).AddJsonFile("appsettings.json").Build();
                    connectionString = config.GetConnectionString("AdminConnection");

                    actualPassword = connectionString.Split(';').Last().Split('=').Last();

                    if (password != actualPassword)
                        throw new Exception("Неверный пароль!");

                    Database.SetConnectionString(connectionString);
                    Database.OpenConnection();
                    role = Roles.Admin;
                    break;
            }
        }

        public bool IsUser
        {
            get => role == Roles.User;
        }

        public bool IsAnalyst
        {
            get => role == Roles.Analyst;
        }

        public bool IsAdmin
        {
            get => role == Roles.Admin;
        }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.Entity<EFAvailability>(entity =>
            {
                entity.ToTable("availability");

                entity.Property(e => e.Id).HasColumnName("id");

                entity.Property(e => e.Productid).HasColumnName("productid");

                entity.Property(e => e.Shopid).HasColumnName("shopid");

                entity.HasOne(d => d.Product)
                    .WithMany(p => p.Availabilities)
                    .HasForeignKey(d => d.Productid)
                    .HasConstraintName("availability_productid_fkey");

                entity.HasOne(d => d.Shop)
                    .WithMany(p => p.Availabilities)
                    .HasForeignKey(d => d.Shopid)
                    .HasConstraintName("availability_shopid_fkey");
            });

            modelBuilder.Entity<EFCost>(entity =>
            {
                entity.HasNoKey();

                entity.ToView("costs");

                entity.Property(e => e.Availabilityid).HasColumnName("availabilityid");

                entity.Property(e => e.CostValue).HasColumnName("cost");
            });

            modelBuilder.Entity<EFCostStory>(entity =>
            {
                entity.ToTable("coststory");

                entity.Property(e => e.Id).HasColumnName("id");

                entity.Property(e => e.Availabilityid).HasColumnName("availabilityid");

                entity.Property(e => e.Cost).HasColumnName("cost");

                entity.Property(e => e.Month).HasColumnName("month");

                entity.Property(e => e.Year).HasColumnName("year");

                entity.HasOne(d => d.Availability)
                    .WithMany(p => p.Coststories)
                    .HasForeignKey(d => d.Availabilityid)
                    .HasConstraintName("coststory_availabilityid_fkey");
            });

            modelBuilder.Entity<EFProduct>(entity =>
            {
                entity.ToTable("products");

                entity.Property(e => e.Id).HasColumnName("id");

                entity.Property(e => e.Name).HasColumnName("name");

                entity.Property(e => e.Producttype).HasColumnName("producttype");
            });

            modelBuilder.Entity<EFSaleReceipt>(entity =>
            {
                entity.ToTable("salereceipts");

                entity.Property(e => e.Id).HasColumnName("id");

                entity.Property(e => e.Dateofpurchase).HasColumnName("dateofpurchase");

                entity.Property(e => e.Fio).HasColumnName("fio");

                entity.Property(e => e.Shopid).HasColumnName("shopid");

                entity.HasOne(d => d.Shop)
                    .WithMany(p => p.Salereceipts)
                    .HasForeignKey(d => d.Shopid)
                    .HasConstraintName("salereceipts_shopid_fkey");
            });

            modelBuilder.Entity<EFSaleReceiptPosition>(entity =>
            {
                entity.ToTable("salereceiptpositions");

                entity.Property(e => e.Id).HasColumnName("id");

                entity.Property(e => e.Availabilityid).HasColumnName("availabilityid");

                entity.Property(e => e.Salereceiptid).HasColumnName("salereceiptid");

                entity.HasOne(d => d.Availability)
                    .WithMany(p => p.Salereceiptpositions)
                    .HasForeignKey(d => d.Availabilityid)
                    .HasConstraintName("salereceiptpositions_availabilityid_fkey");

                entity.HasOne(d => d.Salereceipt)
                    .WithMany(p => p.Salereceiptpositions)
                    .HasForeignKey(d => d.Salereceiptid)
                    .HasConstraintName("salereceiptpositions_salereceiptid_fkey");
            });

            modelBuilder.Entity<EFShop>(entity =>
            {
                entity.ToTable("shops");

                entity.Property(e => e.Id).HasColumnName("id");

                entity.Property(e => e.Description).HasColumnName("description");

                entity.Property(e => e.Name).HasColumnName("name");
            });

            OnModelCreatingPartial(modelBuilder);
        }

        partial void OnModelCreatingPartial(ModelBuilder modelBuilder);
    }
}
