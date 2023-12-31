using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace UI
{
    /// <summary>
    /// Логика взаимодействия для SetLimitWindow.xaml
    /// </summary>
    public partial class SetLimitWindow : Window
    {
        public int VisWidth { get; private set; }
        public int VisHeight { get; private set; }

        public SetLimitWindow()
        {
            InitializeComponent();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (((MainWindow)Owner).Map == null)
                    throw new Exception("Настройки карты высот ещё не заданы!");

                VisWidth = int.Parse(VisWidth_textbox.Text);
                if (VisWidth <= 0 || VisWidth > ((MainWindow)Owner).Map.Width)
                    throw new Exception("Ширина видимой части должна быть больше нуля и не превышать размера карты высот!");

                VisHeight = int.Parse(VisHeight_textbox.Text);
                if (VisHeight <= 0 || VisHeight > ((MainWindow)Owner).Map.Height)
                    throw new Exception("Высота видимой части должна быть больше нуля и не превышать размера карты высот!");

                DialogResult = true;
            }
            catch (Exception exc)
            {
                MessageBox.Show(exc.Message);
            }
        }
    }
}
