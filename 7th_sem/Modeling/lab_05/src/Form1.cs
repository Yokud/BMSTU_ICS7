namespace InformationCentre
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Client client = new Client();
            client.amountOfProccessedNeeded = int.Parse(textBox1.Text);
            client.timeOfCome = int.Parse(textBox2.Text);
            client.timeDelta = int.Parse(textBox3.Text);

            Operator operator1 = new Operator();
            operator1.timeOfService = int.Parse(textBox4.Text);
            operator1.timeDelta = int.Parse(textBox7.Text);

            Operator operator2 = new Operator();
            operator2.timeOfService = int.Parse(textBox5.Text);
            operator2.timeDelta = int.Parse(textBox8.Text);

            Operator operator3 = new Operator();
            operator3.timeOfService = int.Parse(textBox6.Text);
            operator3.timeDelta = int.Parse(textBox9.Text);

            Computer computer1 = new Computer(int.Parse(textBox10.Text));
            Computer computer2 = new Computer(int.Parse(textBox11.Text));

            SimulationParameters parameters = new SimulationParameters(client, operator1, operator2, operator3, computer1, computer2);

            Results results = Results.DoSimulate(parameters);

            CountOfD.Text = results.numberOfDenials.ToString();
            Prob.Text = results.probabilityOfDenial.ToString();
        }
    }
}