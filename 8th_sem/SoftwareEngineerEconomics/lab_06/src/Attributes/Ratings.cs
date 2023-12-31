using System.ComponentModel;

namespace COCOMO.Attributes
{
	public enum Ratings
	{
		[Description("Очень низкий")]
		VeryLow = -2,
		[Description("Низкий")]
		Low = -1,
		[Description("Номинальный")]
		Nominal = 0,
		[Description("Высокий")]
		High = 1,
		[Description("Очень высокий")]
		VeryHigh = 2,
		[Description("Экстра высокий")]
		ExtraHigh = 3
	}
}
