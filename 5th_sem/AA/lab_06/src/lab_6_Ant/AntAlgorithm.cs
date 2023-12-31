using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab_6_Ant
{    
    class AntAlgorithm
    {
        public static readonly Random r = new Random();
        static readonly double eps = 1e-6; 
        
        /// <summary>
        /// Нахождение кратчайшего маршрута муравьиным алгоритмом
        /// </summary>
        /// <param name="map">Граф</param>
        /// <param name="nIter">Количество дней</param>
        /// <param name="alpha">Параметр влияния длины пути</param>
        /// <param name="beta">Параметр влияния феромона</param>
        /// <param name="Q">Количество феромона, переносимого муравьем</param>
        /// <param name="ro">Коэффициент испарения феромона</param>
        /// <returns></returns>
        public static Path GetShortestPath(Map map, int nIter, double alpha, double beta, double Q, double ro)
        {
            Path minPath = new Path(int.MaxValue);
            int n = map.n;
            double[][] pheromones = Program.InitMatr(n, 0.1);

            List<Ant> ants;
            for (int t = 0; t < nIter; t++) // цикл по дням
            {
                ants = InitAnts(map, n);

                // Построение маршрута колонии; n-1 т.к. 1й город известен
                for (int i = 0; i < n - 1; i++)
                {
                    double[][] pheromonesIter = Program.InitMatr(n, (double)0); // временная матрица, колония проходит один шаг

                    // Цикл по муравьям
                    for (int j = 0; j < ants.Count(); j++) 
                    {
                        double sumChance = 0, chance;
                        Ant curAnt = ants[j];
                        int curCity = curAnt.path.route.Last();
                        // Расчет sumChance
                        for (int cityId = 0; cityId < n; cityId++) 
                        {
                            if (curAnt.visited[cityId] == false) // есть непосещенные города
                            {
                                sumChance += Math.Pow(pheromones[curCity][cityId], alpha) * Math.Pow(1.0 / (map.distance[curCity][cityId]), beta); // сумма вероятностей посещения всех городов
                            }
                        }

                        // Выбор следующего города муравья
                        double x = r.NextDouble();
                        int k = 0;
                        for (; x > 0; k++)
                        {
                            if (curAnt.visited[k] == false)
                            {
                                chance = Math.Pow(pheromones[curCity][k], alpha) * Math.Pow(1.0 / (map.distance[curCity][k]), beta); // шанс выбрать город
                                chance /= sumChance;
                                x -= chance;
                            }
                        }
                        k--;
                        ants[j].VisitedTown(k);
                        pheromonesIter[curCity][k] += Q / map.distance[curCity][k];
                        pheromonesIter[k][curCity] += Q / map.distance[curCity][k];
                    }

                    // Испарение феромонов
                    for (int ii = 0; ii < n; ii++)
                        for (int j = 0; j < n; j++)
                        {
                            pheromones[ii][j] = pheromones[j][ii] = (1 - ro) * pheromones[ii][j] + pheromonesIter[ii][j];

                            if (pheromones[ii][j] < eps)
                                pheromones[ii][j] = pheromones[j][ii] = eps;
                        }
                }
                
                // Находим минимальные пути этого дня
                foreach (Ant a in ants)
                {
                    a.VisitedTown(a.iStartTown);
                    if (a.GetDistance() < minPath.distance)
                    {
                        minPath = a.path;
                    }
                }                
            }
            return minPath;
        }

        public static List<Ant> InitAnts(Map m, int n)
        {
            List<Ant> ants = new List<Ant>();
            for (int i = 0; i < n; i++)
            {
                ants.Add(new Ant(m, 1));
            }
            return ants;
        }
    }


    class Ant
    {
        public Path path;
        public bool[] visited;
        public int iStartTown;

        public Ant(Map m, int iStartTown)
        {
            path = new Path(m, iStartTown);
            visited = new bool[m.n];
            visited[iStartTown] = true;
            this.iStartTown = iStartTown;
        }

        public void VisitedTown(int i)
        {
            path.AddVertex(i);
            visited[i] = true;
        }

        public int GetDistance()
        {
            return path.distance;
        }
    }
}
