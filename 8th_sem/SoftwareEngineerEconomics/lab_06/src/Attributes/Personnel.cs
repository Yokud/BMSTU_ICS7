namespace COCOMO.Attributes
{
	/// <summary>
	/// Атрибуты персонала
	/// </summary>
	public static class Personnel
	{
		/// <summary>
		/// Способности аналитика
		/// </summary>
		public static double ACAP(int level)
		{
            return (Ratings)level switch
            {
                Ratings.VeryLow => 1.46,
                Ratings.Low => 1.19,
                Ratings.Nominal => 1.0,
                Ratings.High => 0.86,
                Ratings.VeryHigh => 0.71,
                _ => 0,
            };
        }

		/// <summary>
		/// Знание приложений
		/// </summary>
		public static double AEXP(int level)
		{
            return (Ratings)level switch
            {
                Ratings.VeryLow => 1.29,
                Ratings.Low => 1.15,
                Ratings.Nominal => 1,
                Ratings.High => 0.91,
                Ratings.VeryHigh => 0.82,
                _ => 0,
            };
        }

		/// <summary>
		/// Способности программиста
		/// </summary>
		public static double PCAP(int level)
		{
            return (Ratings)level switch
            {
                Ratings.VeryLow => 1.42,
                Ratings.Low => 1.17,
                Ratings.Nominal => 1,
                Ratings.High => 0.86,
                Ratings.VeryHigh => 0.7,
                _ => 0,
            };
        }

		/// <summary>
		/// Знание виртуальной машины
		/// </summary>
		public static double VEXP(int level)
		{
            return (Ratings)level switch
            {
                Ratings.VeryLow => 1.21,
                Ratings.Low => 1.1,
                Ratings.Nominal => 1,
                Ratings.High => 0.9,
                _ => 0,
            };
        }

		/// <summary>
		/// Знание языка программирования
		/// </summary>
		public static double LEXP(int level)
		{
            return (Ratings)level switch
            {
                Ratings.VeryLow => 1.14,
                Ratings.Low => 1.07,
                Ratings.Nominal => 1,
                Ratings.High => 0.95,
                _ => 0,
            };
        }
	}
}
