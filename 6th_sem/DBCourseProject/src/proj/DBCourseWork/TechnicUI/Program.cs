using DataBaseUI.Models;
using System;

namespace TechnicUI
{
    internal class Program
    {
        static void Main(string[] args)
        {
            ConsoleTechnicView view = new ConsoleTechnicView();
            TechnicPresenter presenter = new TechnicPresenter(view, new PgSQLShopsRepository(),
                                                                    new PgSQLProductsRepository(),
                                                                    new PgSQLSaleReceiptsRepository(),
                                                                    new PgSQLSaleReceiptPositionsRepository(),
                                                                    new PgSQLCostsRepository(),
                                                                    new PgSQLCostStoryRepository(),
                                                                    new PgSQLAvailabilityRepository());

            view.StartUi();
        }
    }
}