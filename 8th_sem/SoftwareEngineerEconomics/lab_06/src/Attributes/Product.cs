namespace COCOMO.Attributes
{
	/// <summary>
	/// Атрибуты программного продукта
	/// </summary>
	public static class Product
	{
		/// <summary>
		/// Требуемая надежность
		/// </summary>
		public static double RELY(int level)
		{
            return (Ratings)level switch
            {
                Ratings.VeryLow => 0.75,
                Ratings.Low => 0.86,
                Ratings.Nominal => 1,
                Ratings.High => 1.15,
                Ratings.VeryHigh => 1.4,
                _ => 0,
            };
        }

		/// <summary>
		/// Размер БД
		/// </summary>
		public static double DATA(int level)
		{
            return (Ratings)level switch
            {
                Ratings.Low => 0.94,
                Ratings.Nominal => 1,
                Ratings.High => 1.08,
                Ratings.VeryHigh => 1.16,
                _ => 0,
            };
        }

		/// <summary>
		/// Сложность продукта
		/// </summary>
		public static double CPLX(int level)
		{
            return (Ratings)level switch
            {
                Ratings.VeryLow => 0.7,
                Ratings.Low => 0.85,
                Ratings.Nominal => 1,
                Ratings.High => 1.15,
                Ratings.VeryHigh => 1.3,
                _ => 0,
            };
        }
	}
}
