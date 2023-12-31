void LeastSquares(List<Point> points, int power, out List<double> coefs)
{
    int n = points.Count;                                                   (1)
    double[,] matrix = new double[power + 1, power + 2];                    (2)

    for (int k = 0; k <= power; k++)                                        (3)
    {
        double sum = 0;                                                     (4)
        for (int i = 0; i < n; i++)                                         (5)
            sum += points[i].p * Math.Pow(points[i].x, k) * points[i].y;    (6)
        matrix[k, power + 1] = sum;                                         (7)

        for (int m = 0; m <= power; m++)                                    (8)
        {
            sum = 0;                                                        (9)
            for (int i = 0; i < n; i++)                                     (10)
                sum += points[i].p * Math.Pow(points[i].x, k + m);          (11)
            matrix[k, m] = sum;                                             (12)
        }
    }

    double[] a = new double[power];                                         (13)

    for (int k = 1; k < power; k++)                                         (14)
        for (int j = k; j < power; j++)                                     (15)
        {
            double m = matrix[j, k - 1] / matrix[k - 1, k - 1];             (16)

            for (int i = 0; i < power + 1; i++)                             (17)
                matrix[j, i] -= m * matrix[k - 1, i];                       (18)
        }

    for (int i = power - 1; i >= 0; i--)                                    (19)
    {
        a[i] = matrix[i, power] / matrix[i, i];                             (20)

        for (int c = power - 1; c > i; c--)                                 (21)
            a[i] -= matrix[i, c] * a[c] / matrix[i, i];                     (22)
    }

    coefs = a.ToList();                                                     (23)
}