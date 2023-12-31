using DataBaseUI.DB;
using DataBaseUI.SysEntities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace DataBaseUI.Models
{
    public interface ICostsRepository : IRepository<Cost>
    {
        Cost GetByShopProductCost(Shop shop, Product product);
    }
}
