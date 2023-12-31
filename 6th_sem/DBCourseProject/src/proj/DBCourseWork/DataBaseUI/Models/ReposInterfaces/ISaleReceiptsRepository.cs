using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DataBaseUI.DB;
using DataBaseUI.SysEntities;

namespace DataBaseUI.Models
{
    public interface ISaleReceiptsRepository : IRepository<SaleReceipt>
    {
        IEnumerable<SaleReceipt> GetAllFromShop(Shop shop);
    }
}
