using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using DataBaseUI.DB;
using DataBaseUI.SysEntities;

namespace DataBaseUI.Models
{
    public interface ISaleReceiptPositionsRepository : IRepository<SaleReceiptPosition>
    {
        IEnumerable<Product> GetAllFromSaleReceipt(SaleReceipt saleReceipt);
    }
}
