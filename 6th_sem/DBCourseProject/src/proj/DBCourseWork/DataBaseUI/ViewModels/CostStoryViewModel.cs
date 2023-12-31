using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using DataBaseUI.DB;
using DataBaseUI.Models;
using DataBaseUI.SysEntities;
using TrendLineLib;
using OxyPlot;
using System.Windows;
using DataBaseUI.Views.DialogWindows.CostStoryView;
using Microsoft.Extensions.Logging;

namespace DataBaseUI.ViewModels
{
    internal class CostStoryViewModel : INotifyPropertyChanged
    {
        ICostStoryRepository costStories;
        IAvailabilityRepository availabilities;
        Shop selectedShop;
        Product selectedProduct;
        CostStory selectedCostStory;

        ILogger logger;

        BaseTrendLine trend;
        PlotModel trendLinePlot;
        int nextCostValue;
        string polString;

        bool isAdmin, isAnalyst;

        public CostStoryViewModel(SpsrLtDbContext dbContext, ILogger logger = null)
        {
            costStories = new PgSQLCostStoryRepository(dbContext, logger);
            availabilities = new PgSQLAvailabilityRepository(dbContext, logger);
            trend = new PolynomialTrendLine();
            this.logger = logger;
        }

        public IEnumerable<CostStory> ProductCostStory
        {
            get
            {
                return selectedShop != null && selectedProduct != null ? costStories.GetFullCostStory(selectedShop, selectedProduct) : null;
            }
        }

        public Shop SelectedShop
        {
            get { return selectedShop; }
            set
            {
                selectedShop = value;
                OnPropertyChanged("SelectedShop");
                logger?.LogInformation("Selected shop was updated.\n");
            }
        }

        public Product SelectedProduct
        {
            get { return selectedProduct; }
            set
            {
                selectedProduct = value;
                logger?.LogInformation("Selected product was updated.\n");
                OnPropertyChanged("SelectedProduct");
                OnPropertyChanged("ProductCostStory");
                OnPropertyChanged("TrendLinePlot");
            }
        }

        public CostStory SelectedCostStory
        {
            get => selectedCostStory;
            set
            {
                selectedCostStory = value;
                logger?.LogInformation("Selected cost story was updated.\n");
                OnPropertyChanged("SelectedCostStory");
            }
        }

        public bool IsAdmin
        {
            get => isAdmin;
            set
            {
                isAdmin = value;
                OnPropertyChanged("IsAdmin");
            }
        }

        public bool IsAnalyst
        {
            get => isAnalyst;
            set
            {
                isAnalyst = value;
                OnPropertyChanged("IsAnalyst");
            }
        }

        public PlotModel TrendLinePlot
        {
            get
            {
                if (ProductCostStory == null)
                    return null;

                trendLinePlot = new PlotModel();

                List<double> coefs = trend.GetCoefs(ProductCostStory);
                List<TrendLineLib.Point> points = trend.GetLinePoints(ProductCostStory);

                NextCostValue = (int)trend.F(ProductCostStory.Count() + 1);

                StringBuilder builder = new StringBuilder("y =");

                for (int i = coefs.Count - 1; i > -1; i--)
                {
                    char sign = coefs[i] >= 0 ? '+' : ' ';

                    builder.Append(string.Format(" {0}{1:f3}x^{2}", sign, coefs[i], i));
                }

                PolynomeString = builder.ToString();

                trendLinePlot.Title = "Тренд цены";

                var line = new OxyPlot.Series.LineSeries();
                var costPoints = new OxyPlot.Series.ScatterSeries();

                foreach (var p in points)
                    line.Points.Add(new DataPoint(p.X, p.Y));

                trendLinePlot.Series.Add(line);

                foreach (var p in CostStoryPoints.FromCostStory(ProductCostStory))
                    costPoints.Points.Add(new OxyPlot.Series.ScatterPoint(p.X, p.Y));

                trendLinePlot.Series.Add(costPoints);

                return trendLinePlot;
            }
        }

        public int NextCostValue
        {
            get
            { 
                return nextCostValue; 
            }
            set
            {
                nextCostValue = value;
                OnPropertyChanged("NextCostValue");
            }
        }

        public string PolynomeString
        {
            get
            {
                return polString;
            }
            set 
            { 
                polString = value; 
                OnPropertyChanged("PolynomeString"); 
            }
        }

        RelayCommand addCommand;
        public RelayCommand AddCommand
        {
            get
            {
                return addCommand ??= new RelayCommand(obj => 
                {
                    AddCostStoryWindow wnd = new AddCostStoryWindow();

                    if (wnd.ShowDialog() == true)
                    {
                        CostStory c = wnd.NewCostStory;

                        if (c != null)
                        {
                            c.AvailabilityId = availabilities.GetAll().Where(x => x.ShopId == selectedShop.Id && x.ProductId == selectedProduct.Id).First().Id;
                            AddCostStory(c);
                        }
                    }
                });
            }
        }

        RelayCommand deleteCommand;
        public RelayCommand DeleteCommand
        {
            get
            {
                return deleteCommand ??= new RelayCommand(obj =>
                {
                    CostStory c = obj as CostStory;

                    if (c != null)
                        DeleteCostStory(c);
                }, obj => costStories.GetAll()?.Count() > 0);
            }
        }

        RelayCommand updateCommand;
        public RelayCommand UpdateCommand
        {
            get
            {
                return updateCommand ??= new RelayCommand(obj =>
                {
                    UpdateCostStoryWindow wnd = new UpdateCostStoryWindow();

                    if (wnd.ShowDialog() == true)
                    {
                        CostStory c = obj as CostStory;

                        if (c != null)
                        {
                            c.Year = wnd.NewYear ?? c.Year;
                            c.Month = wnd.NewMonth ?? c.Month;
                            c.Cost = wnd.NewCost ?? c.Cost;

                            UpdateCostStory(c);
                        }
                    }
                });
            }
        }

        public void AddCostStory(CostStory costStory)
        {
            try
            {
                costStories.Create(costStory);
                logger?.LogInformation(string.Format("Cost story with id = {0} was added.\n", costStory.Id));
                OnPropertyChanged("ProductCostStory");
                OnPropertyChanged("TrendLinePlot");
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
                logger?.LogError(e.Message);
            }
        }

        public void DeleteCostStory(CostStory costStory)
        {
            try
            {
                costStories.Delete(costStory);
                logger?.LogInformation(string.Format("Cost story with id = {0} was deleted.\n", costStory.Id));
                OnPropertyChanged("ProductCostStory");
                OnPropertyChanged("TrendLinePlot");
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
                logger?.LogError(e.Message);
            }
        }

        public void UpdateCostStory(CostStory costStory)
        {
            try
            {
                costStories.Update(costStory);
                logger?.LogInformation(string.Format("Cost story with id = {0} was updated.\n", costStory.Id));
                OnPropertyChanged("ProductCostStory");
                OnPropertyChanged("TrendLinePlot");
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
                logger?.LogError(e.Message);
            }
        }

        public event PropertyChangedEventHandler? PropertyChanged;
        public void OnPropertyChanged([CallerMemberName] string prop = "")
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(prop));
        }
    }

    internal static class CostStoryPoints
    {
        public static IEnumerable<TrendLineLib.Point> FromCostStory(IEnumerable<CostStory> cs)
        {
            cs = cs.OrderBy(x => new DateOnly(x.Year, x.Month, 1));
            List<int> costs = cs.ToList().Select(x => x.Cost).ToList();
            List<DateOnly> dates = cs.Select(x => new DateOnly(x.Year, x.Month, 1)).ToList();

            List<TrendLineLib.Point> points = new List<TrendLineLib.Point>();

            for (int i = 0; i < Math.Max(costs.Count, dates.Count); i++)
            {
                points.Add(new TrendLineLib.Point(i + 1, costs[i]));
            }

            return points;
        }

        public static List<double> GetCoefs(this BaseTrendLine line, IEnumerable<CostStory> costStories)
        {
            var points = FromCostStory(costStories);

            return line.GetCoefs(points.ToList());
        }

        public static List<TrendLineLib.Point> GetLinePoints(this BaseTrendLine line, IEnumerable<CostStory> costStories)
        {
            var points = FromCostStory(costStories);

            return line.GetLinePoints(points);
        }
    }
}
