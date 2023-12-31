namespace COCOMO.Attributes
{
	/// <summary>
	/// Атрибуты компьютера
	/// </summary>
	public static class Hardware
	{
		/// <summary>
		/// Ограничение времени выполнения
		/// </summary>
		public static double TIME(int level)
		{
            return (Ratings)level switch
            {
                Ratings.Nominal => 1,
                Ratings.High => 1.11,
                Ratings.VeryHigh => 1.5,
                _ => 0,
            };
        }

		/// <summary>
		/// Ограничение объема основной памяти
		/// </summary>
		public static double STOR(int level)
		{
            return (Ratings)level switch
            {
                Ratings.Nominal => 1,
                Ratings.High => 1.06,
                Ratings.VeryHigh => 1.21,
                _ => 0,
            };
        }

		/// <summary>
		/// Изменчивость виртуальной машины
		/// </summary>
		public static double VIRT(int level)
		{
            return (Ratings)level switch
            {
                Ratings.Low => 0.87,
                Ratings.Nominal => 1.0,
                Ratings.High => 1.15,
                Ratings.VeryHigh => 1.3,
                _ => 0,
            };
        }

		/// <summary>
		/// Время реакции компьютера
		/// </summary>
		public static double TURN(int level)
		{
            return (Ratings)level switch
            {
                Ratings.Low => 0.87,
                Ratings.Nominal => 1,
                Ratings.High => 1.07,
                Ratings.VeryHigh => 1.15,
                _ => 0,
            };
        }
	}
}
