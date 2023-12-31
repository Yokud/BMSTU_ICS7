namespace COCOMO_var1
{
	/// <summary>
	/// Декомпозиция работ по созданию ПО
	/// </summary>
	class Decompose
	{
		private readonly double workTotal;

		public double AnalysisWork { get => workTotal * analysisCoef; }
		public double ProjectingWork { get => workTotal * projectingCoef; }
		public double ProgrammingWork { get => workTotal * programmingCoef; }
		public double TestingWork { get => workTotal * testingCoef; }
		public double VerificationWork { get => workTotal * verificationCoef; }
		public double ChancelleryWork { get => workTotal * chancelleryCoef; }
		public double QaWork { get => workTotal * qaCoef; }
		public double ManualWork { get => workTotal * manualCoef; }

		private const double analysisCoef = .04;
		private const double projectingCoef = .12;
		private const double programmingCoef = .44;
		private const double testingCoef = .06;
		private const double verificationCoef = .14;
		private const double chancelleryCoef = .07;
		private const double qaCoef = .07;
		private const double manualCoef = .06;

		public Decompose(double workTotal)
		{
			this.workTotal = workTotal;
		}
	}
}
