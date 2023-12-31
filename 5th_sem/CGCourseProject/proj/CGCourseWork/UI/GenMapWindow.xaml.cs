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
    /// Логика взаимодействия для GenMapWindow.xaml
    /// </summary>
    public partial class GenMapWindow : Window
    {
        public int MapWidth { get; private set; }
        public int MapHeight { get; private set; }
        public int Scale { get; private set; }
        public int Octaves { get; private set; }
        public float Lacunarity { get; private set; }
        public float Persistence { get; private set; }
        public int Seed { get; private set; }

        public bool oct, lac, pers, seed;
        public GenMapWindow()
        {
            InitializeComponent();         
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                MapWidth = int.Parse(Width_textbox.Text);
                if (MapWidth <= 0)
                    throw new Exception("Ширина карты не может быть меньше или равно нулю!");

                MapHeight = int.Parse(Height_textbox.Text);
                if (MapHeight <= 0)
                    throw new Exception("Высота карты не может быть меньше или равно нулю!");

                Scale = int.Parse(Scale_textbox.Text);
                if (Scale <= 0 || Scale > MapWidth || Scale > MapHeight)
                    throw new Exception("Масштаб карты может быть больше нуля и меньше сторон карты высот!");

                if (oct = Octs_textbox.Text != string.Empty)
                {
                    Octaves = int.Parse(Octs_textbox.Text);
                    if (Octaves <= 0)
                        throw new Exception("Количество октав карты не может быть меньше или равно нулю!");
                }
                if (lac = Lacun_textbox.Text != string.Empty)
                {
                    Lacunarity = float.Parse(Lacun_textbox.Text);
                    if (Lacunarity <= 0)
                        throw new Exception("Лакунарность не может быть меньше или равно нулю!");
                }
                if (pers = Pers_textbox.Text != string.Empty)
                {
                    Persistence = float.Parse(Pers_textbox.Text);
                    if (Persistence <= 0)
                        throw new Exception("Стойкость не может быть меньше или равно нулю!");
                }
                if (seed = Seed_textbox.Text != string.Empty)
                    Seed = int.Parse(Seed_textbox.Text);

                DialogResult = true;
                Close();
            }
            catch (Exception exc)
            {
                MessageBox.Show(exc.Message);
            }
        }
    }
}
