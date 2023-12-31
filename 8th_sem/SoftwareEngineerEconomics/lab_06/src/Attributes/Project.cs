namespace COCOMO.Attributes
{
	/// <summary>
	/// Атрибуты проекта
	/// </summary>
	public static class Project
	{
		/// <summary>
		/// Использование современных методов
		/// </summary>
		public static double MODP(int level)
		{
            return (Ratings)level switch
            {
                Ratings.VeryLow => 1.24,
                Ratings.Low => 1.1,
                Ratings.Nominal => 1,
                Ratings.High => .91,
                Ratings.VeryHigh => .82,
                _ => 0,
            };
        }

		/// <summary>
		/// Использование программных инструментов
		/// </summary>
		public static double TOOL(int level)
		{
            return (Ratings)level switch
            {
                Ratings.VeryLow => 1.24,
                Ratings.Low => 1.1,
                Ratings.Nominal => 1,
                Ratings.High => .91,
                Ratings.VeryHigh => .82,
                _ => 0,
            };
        }

		/// <summary>
		/// Требуемые сроки разработки
		/// </summary>
		public static double SCED(int level)
		{
            return (Ratings)level switch
            {
                Ratings.VeryLow => 1.23,
                Ratings.Low => 1.08,
                Ratings.Nominal => 1,
                Ratings.High => 1.04,
                Ratings.VeryHigh => 1.1,
                _ => 0,
            };
        }
	}
}
