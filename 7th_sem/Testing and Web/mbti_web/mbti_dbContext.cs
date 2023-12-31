﻿using System;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata;
using mbti_web.Entities;
using Type = mbti_web.Entities.Type;

#nullable disable

namespace mbti_web
{
    public partial class mbti_dbContext : DbContext
    {
        public mbti_dbContext()
        {
        }

        public mbti_dbContext(DbContextOptions<mbti_dbContext> options)
            : base(options)
        {
        }

        public virtual DbSet<Character> Characters { get; set; }
        public virtual DbSet<Type> Types { get; set; }
        public virtual DbSet<User> Users { get; set; }

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder.HasAnnotation("Relational:Collation", "Russian_Russia.utf8");

            modelBuilder.Entity<Character>(entity =>
            {
                entity.HasKey(e => e.Characteruk)
                    .HasName("characters_pkey");

                entity.ToTable("characters");

                entity.Property(e => e.Characteruk)
                    .ValueGeneratedNever()
                    .HasColumnName("characteruk");

                entity.Property(e => e.Category)
                    .HasMaxLength(100)
                    .HasColumnName("category");

                entity.Property(e => e.Charactername)
                    .IsRequired()
                    .HasMaxLength(255)
                    .HasColumnName("charactername");

                entity.Property(e => e.Typeuk).HasColumnName("typeuk");

                /*entity.HasOne(d => d.TypeukNavigation)
                    .WithMany(p => p.Characters)
                    .HasForeignKey(d => d.Typeuk)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("characters_typeuk_fk");*/
            });

            modelBuilder.Entity<Type>(entity =>
            {
                entity.HasKey(e => e.Typeuk)
                    .HasName("types_pkey");

                entity.ToTable("types");

                entity.HasComment("Типы личности по MBTI");

                entity.Property(e => e.Typeuk)
                    .ValueGeneratedNever()
                    .HasColumnName("typeuk")
                    .HasComment("Идентификатор типа личности");

                entity.Property(e => e.Typedescription)
                    .HasColumnName("typedescription")
                    .HasComment("Описание типа личности");

                entity.Property(e => e.Typename)
                    .IsRequired()
                    .HasMaxLength(255)
                    .HasColumnName("typename")
                    .HasComment("Название типа личности");
            });

            modelBuilder.Entity<User>(entity =>
            {
                entity.HasKey(e => e.Useruk)
                    .HasName("users_pkey");

                entity.ToTable("users");

                entity.Property(e => e.Useruk)
                    .ValueGeneratedNever()
                    .HasColumnName("useruk");

                entity.Property(e => e.Dateofbirth)
                    .HasColumnType("date")
                    .HasColumnName("dateofbirth");

                entity.Property(e => e.Email)
                    .HasMaxLength(255)
                    .HasColumnName("email");

                entity.Property(e => e.Login)
                    .IsRequired()
                    .HasMaxLength(100)
                    .HasColumnName("login");

                entity.Property(e => e.Nickname)
                    .IsRequired()
                    .HasMaxLength(100)
                    .HasColumnName("nickname");

                entity.Property(e => e.Password)
                    .IsRequired()
                    .HasMaxLength(50)
                    .HasColumnName("password");

                entity.Property(e => e.Telagram)
                    .HasMaxLength(255)
                    .HasColumnName("telagram");

                entity.Property(e => e.Typeuk).HasColumnName("typeuk");

                /*entity.HasOne(d => d.TypeukNavigation)
                    .WithMany(p => p.Users)
                    .HasForeignKey(d => d.Typeuk)
                    .OnDelete(DeleteBehavior.ClientSetNull)
                    .HasConstraintName("users_typeuk_fk");*/
            });

            OnModelCreatingPartial(modelBuilder);
        }

        partial void OnModelCreatingPartial(ModelBuilder modelBuilder);
    }
}
