﻿using AutoMapper;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.OpenApi.Models;
using mbti_web.Middleware;
using mbti_web.Services;
using mbti_web.Repository;
using Microsoft.AspNetCore.Authentication.JwtBearer;
using Microsoft.IdentityModel.Tokens;
using System.Text;
using Microsoft.AspNetCore.Server.IISIntegration;

namespace mbti_web
{
    public class Startup
    {
        public Startup(IConfiguration configuration)
        {
            Configuration = configuration;
        }

        public IConfiguration Configuration { get; }

        public virtual void ConfigureServices(IServiceCollection services)
        {
            services.AddMemoryCache();

            services.AddDbContext<mbti_dbContext>(opt =>
                opt.UseNpgsql(Configuration.GetConnectionString("DefaultConnection")), 
                ServiceLifetime.Transient);

            services.AddScoped<IRepositoryUser, RepositoryUser>();
            services.AddScoped<IRepositoryType, RepositoryType>();
            services.AddScoped<IRepositoryCharacter, RepositoryCharacter>();

            services.AddScoped<IUserService, UserService>();
            services.AddScoped<ITypeService, TypeService>();
            services.AddScoped<ICharacterService, CharacterService>();

            services.AddControllers();

            services.AddAutoMapper(typeof(UserProfile));
            services.AddAutoMapper(typeof(TypeProfile));
            services.AddAutoMapper(typeof(CharacterProfile));
            services.AddCors();

            #region swagger config       
            services.AddSwaggerGen(setup =>
            {
                setup.AddSecurityDefinition("Bearer", new OpenApiSecurityScheme()
                {
                    Name = "Authorization",
                    Type = SecuritySchemeType.ApiKey,
                    Scheme = "Bearer",
                    BearerFormat = "JWT",
                    In = ParameterLocation.Header,
                    Description = "JWT Authorization header using the Bearer scheme. \r\n\r\n Enter 'Bearer' [space] and then your token in the text input below.\r\n\r\nExample: \"Bearer 12345qwerty\"",
                });

                setup.AddSecurityRequirement(new OpenApiSecurityRequirement
                {
                    {
                          new OpenApiSecurityScheme
                            {
                                Reference = new OpenApiReference
                                {
                                    Type = ReferenceType.SecurityScheme,
                                    Id = "Bearer"
                                }
                            },
                            new string[] {}
                    }
                });
            });

            #endregion
        }

        public void Configure(IApplicationBuilder app, IWebHostEnvironment env)
        {

            app.UseRouting();
            app.UseSwagger();
            app.UseSwaggerUI();

            app.UseAuthentication();
            app.UseRouting();
            app.UseAuthorization();

            app.UseCors(x => x
                .AllowAnyOrigin()
                .AllowAnyMethod()
                .AllowAnyHeader());

            app.UseMiddleware<JwtMiddleware>();
            app.UseEndpoints(x => x.MapControllers());
        }
    }
}