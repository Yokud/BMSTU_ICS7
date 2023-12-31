namespace QueueModeling
{
    public partial class Form1 : Form
    {
        double a, b, lambda, prob;
        int requests;

        public Form1()
        {
            InitializeComponent();
        }

        private void StartButton_Click(object sender, EventArgs e)
        {
            a = double.Parse(ATextBox.Text, System.Globalization.CultureInfo.InvariantCulture);
            b = double.Parse(BTextBox.Text, System.Globalization.CultureInfo.InvariantCulture);
            lambda = double.Parse(LambdaTextBox.Text, System.Globalization.CultureInfo.InvariantCulture);

            requests = int.Parse(CountTextBox.Text);
            prob = double.Parse(ProbTextBox.Text, System.Globalization.CultureInfo.InvariantCulture);

            (double, double) withoutInverseDeltaT = SimulateWithoutInverseConnectionDeltaTMethod();
            (double, double) withInverseDeltaT = SimulateWithInverseConnectionDeltaTMethod();

            (double, double) withoutInverseEvent = SimulateWithoutInverseConnectionEventMethod();
            (double, double) withInverseEvent = SimulateWithInverseConnectionEventMethod();

            label6.Text = withoutInverseDeltaT.Item2.ToString();
            label7.Text = withInverseDeltaT.Item1.ToString();
            label8.Text = withInverseDeltaT.Item2.ToString();

            label9.Text = withoutInverseEvent.Item2.ToString();
            label10.Text = withInverseEvent.Item1.ToString();
            label11.Text = withInverseEvent.Item2.ToString();
        }

        (double, double) SimulateWithInverseConnectionDeltaTMethod()
        {
            Processor processor = new Processor(lambda, prob);
            RequestsGenerator generator = new RequestsGenerator(a, b);

            return new Simulator(processor, generator).SimulateUsingDeltaTMethod(requests);
        }

        (double, double) SimulateWithoutInverseConnectionDeltaTMethod()
        {
            Processor processor = new(lambda, 0);
            RequestsGenerator generator = new(a, b);

            return new Simulator(processor, generator).SimulateUsingDeltaTMethod(requests);
        }

        (double, double) SimulateWithInverseConnectionEventMethod()
        {
            Processor processor = new(lambda, prob);
            RequestsGenerator generator = new(a, b);

            return new Simulator(processor, generator).SimulateUsingEventMethod(requests);
        }

        (double, double) SimulateWithoutInverseConnectionEventMethod()
        {
            Processor processor = new(lambda, 0);
            RequestsGenerator generator = new(a, b);

            return new Simulator(processor, generator).SimulateUsingEventMethod(requests);
        }
    }
}