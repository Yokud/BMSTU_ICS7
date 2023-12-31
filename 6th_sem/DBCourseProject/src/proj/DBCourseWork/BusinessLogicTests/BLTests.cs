namespace BusinessLogicTests
{
    public class BLTests
    {
        [Fact]
        public void TestLinearSpline()
        {
            List<Point> data = new List<Point>();
            data.Add(new Point(0, 0));
            data.Add(new Point(1, 1));
            data.Add(new Point(2, 1.5));
            data.Add(new Point(3, 2.2));
            data.Add(new Point(4, 3));
            data.Add(new Point(5, 5));

            BaseTrendLine line = new PolynomialTrendLine();
            var res = line.GetCoefs(data);
            Assert.Equal(res.Select(x => Math.Round(x, 3)), new List<double>() { -0.148, 0.906 });
        }

        [Fact]
        public void TestQuadraticSpline()
        {
            List<Point> data = new List<Point>();
            data.Add(new Point(0, 1));
            data.Add(new Point(1, 1));
            data.Add(new Point(2, 0.7));
            data.Add(new Point(3, 1));
            data.Add(new Point(4, 3));
            data.Add(new Point(5, 4));

            BaseTrendLine line = new PolynomialTrendLine();
            var res = line.GetCoefs(data);
            Assert.Equal(res.Select(x => Math.Round(x, 3)), new List<double>() { 1.107, -0.659, 0.254 });
        }

        [Fact]
        public void TestCubicSpline()
        {
            List<Point> data = new List<Point>();
            data.Add(new Point(0, 0));
            data.Add(new Point(1, 2));
            data.Add(new Point(2, 1));
            data.Add(new Point(3, 1.2));
            data.Add(new Point(4, 3));
            data.Add(new Point(5, 4));

            BaseTrendLine line = new PolynomialTrendLine();
            var res = line.GetCoefs(data);
            Assert.Equal(res.Select(x => Math.Round(x, 3)), new List<double>() { 0.24, 1.657, -0.737, 0.113 });
        }

        [Fact]
        public void TestDirectLine()
        {
            List<Point> data = new List<Point>();
            data.Add(new Point(0, 0));
            data.Add(new Point(1, 1));
            data.Add(new Point(2, 2));
            data.Add(new Point(3, 3));
            data.Add(new Point(4, 4));
            data.Add(new Point(5, 5));

            BaseTrendLine line = new PolynomialTrendLine();
            var res = line.GetCoefs(data);
            Assert.Equal(res.Select(x => Math.Round(x, 3)), new List<double>() { 0, 1 });
        }

        [Fact]
        public void TestMaxExtremums()
        {
            List<Point> data = new List<Point>();
            data.Add(new Point(0, 0));
            data.Add(new Point(1, -1));
            data.Add(new Point(2, 1));
            data.Add(new Point(3, -1));
            data.Add(new Point(4, 1));
            data.Add(new Point(5, -1));
            data.Add(new Point(6, 0));
            data.Add(new Point(7, -1));
            data.Add(new Point(8, 1));
            data.Add(new Point(9, -1));
            data.Add(new Point(10, 1));
            data.Add(new Point(11, -1));

            BaseTrendLine line = new PolynomialTrendLine();
            var res = line.GetCoefs(data);
            Assert.Equal(res.Select(x => Math.Round(x, 3)), new List<double>() { -0.108, -1.194, 1.180, -0.382, 0.053, -0.003, 0 });
        }

        [Fact]
        public void TestEmptyData()
        {
            List<Point> data = new List<Point>();

            BaseTrendLine line = new PolynomialTrendLine();
            var res = line.GetCoefs(data);
            Assert.Equal(res, null);
        }

        [Fact]
        public void TestNullData()
        {
            BaseTrendLine line = new PolynomialTrendLine();
            var res = line.GetCoefs(null);
            Assert.Equal(res, null);
        }
    }
}