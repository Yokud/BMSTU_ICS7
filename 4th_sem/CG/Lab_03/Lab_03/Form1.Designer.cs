
namespace Lab_03
{
    partial class MainWindow
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.label1 = new System.Windows.Forms.Label();
            this.lineColor = new System.Windows.Forms.PictureBox();
            this.label2 = new System.Windows.Forms.Label();
            this.bgColor = new System.Windows.Forms.PictureBox();
            this.colorDialog1 = new System.Windows.Forms.ColorDialog();
            this.colorDialog2 = new System.Windows.Forms.ColorDialog();
            this.label3 = new System.Windows.Forms.Label();
            this.choiceAlg = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.S_length = new System.Windows.Forms.TextBox();
            this.S_angle = new System.Windows.Forms.TextBox();
            this.S_centre_x = new System.Windows.Forms.TextBox();
            this.S_centre_y = new System.Windows.Forms.TextBox();
            this.buttonSpectre = new System.Windows.Forms.Button();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.textStartP_Y = new System.Windows.Forms.TextBox();
            this.textStartP_X = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.textEndP_Y = new System.Windows.Forms.TextBox();
            this.textEndP_X = new System.Windows.Forms.TextBox();
            this.label14 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.button1 = new System.Windows.Forms.Button();
            this.buttonClear = new System.Windows.Forms.Button();
            this.buttonAsk = new System.Windows.Forms.Button();
            this.buttonCmpAlgs = new System.Windows.Forms.Button();
            this.buttonCompute = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.lineColor)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bgColor)).BeginInit();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackColor = System.Drawing.Color.White;
            this.pictureBox1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pictureBox1.Location = new System.Drawing.Point(15, 17);
            this.pictureBox1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(600, 600);
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(633, 16);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(93, 20);
            this.label1.TabIndex = 1;
            this.label1.Text = "Цвет линии:";
            // 
            // lineColor
            // 
            this.lineColor.BackColor = System.Drawing.Color.White;
            this.lineColor.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.lineColor.Location = new System.Drawing.Point(727, 18);
            this.lineColor.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.lineColor.Name = "lineColor";
            this.lineColor.Size = new System.Drawing.Size(54, 18);
            this.lineColor.TabIndex = 2;
            this.lineColor.TabStop = false;
            this.lineColor.Click += new System.EventHandler(this.pictureBox2_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(641, 55);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(85, 20);
            this.label2.TabIndex = 3;
            this.label2.Text = "Цвет фона:";
            // 
            // bgColor
            // 
            this.bgColor.BackColor = System.Drawing.Color.White;
            this.bgColor.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.bgColor.Location = new System.Drawing.Point(727, 57);
            this.bgColor.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.bgColor.Name = "bgColor";
            this.bgColor.Size = new System.Drawing.Size(54, 18);
            this.bgColor.TabIndex = 4;
            this.bgColor.TabStop = false;
            this.bgColor.Click += new System.EventHandler(this.pictureBox2_Click_1);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(633, 93);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(137, 20);
            this.label3.TabIndex = 5;
            this.label3.Text = "Выбор алгоритма:";
            // 
            // choiceAlg
            // 
            this.choiceAlg.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.choiceAlg.FormattingEnabled = true;
            this.choiceAlg.Items.AddRange(new object[] {
            "Библиотечный",
            "ЦДА",
            "Брезенхем(действ.)",
            "Брезенхем(целые)",
            "Брезенхем(без ступенч.)",
            "Ву"});
            this.choiceAlg.Location = new System.Drawing.Point(768, 90);
            this.choiceAlg.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.choiceAlg.Name = "choiceAlg";
            this.choiceAlg.Size = new System.Drawing.Size(181, 28);
            this.choiceAlg.TabIndex = 6;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(633, 162);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(145, 20);
            this.label4.TabIndex = 7;
            this.label4.Text = "Рисование спектра:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(655, 187);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(56, 20);
            this.label5.TabIndex = 8;
            this.label5.Text = "Длина:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(667, 226);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(44, 20);
            this.label6.TabIndex = 9;
            this.label6.Text = "Угол:";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(798, 186);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(55, 20);
            this.label7.TabIndex = 10;
            this.label7.Text = "Центр:";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(827, 208);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(19, 20);
            this.label8.TabIndex = 11;
            this.label8.Text = "x:";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(826, 246);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(19, 20);
            this.label9.TabIndex = 12;
            this.label9.Text = "y:";
            // 
            // S_length
            // 
            this.S_length.Font = new System.Drawing.Font("Segoe UI", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.S_length.Location = new System.Drawing.Point(709, 186);
            this.S_length.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.S_length.Name = "S_length";
            this.S_length.Size = new System.Drawing.Size(62, 25);
            this.S_length.TabIndex = 13;
            // 
            // S_angle
            // 
            this.S_angle.Font = new System.Drawing.Font("Segoe UI", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.S_angle.Location = new System.Drawing.Point(709, 225);
            this.S_angle.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.S_angle.Name = "S_angle";
            this.S_angle.Size = new System.Drawing.Size(62, 25);
            this.S_angle.TabIndex = 14;
            // 
            // S_centre_x
            // 
            this.S_centre_x.Font = new System.Drawing.Font("Segoe UI", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.S_centre_x.Location = new System.Drawing.Point(848, 206);
            this.S_centre_x.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.S_centre_x.Name = "S_centre_x";
            this.S_centre_x.Size = new System.Drawing.Size(62, 25);
            this.S_centre_x.TabIndex = 15;
            // 
            // S_centre_y
            // 
            this.S_centre_y.Font = new System.Drawing.Font("Segoe UI", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.S_centre_y.Location = new System.Drawing.Point(848, 243);
            this.S_centre_y.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.S_centre_y.Name = "S_centre_y";
            this.S_centre_y.Size = new System.Drawing.Size(62, 25);
            this.S_centre_y.TabIndex = 16;
            // 
            // buttonSpectre
            // 
            this.buttonSpectre.Location = new System.Drawing.Point(697, 279);
            this.buttonSpectre.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.buttonSpectre.Name = "buttonSpectre";
            this.buttonSpectre.Size = new System.Drawing.Size(156, 31);
            this.buttonSpectre.TabIndex = 17;
            this.buttonSpectre.Text = "Нарисовать спектр";
            this.buttonSpectre.UseVisualStyleBackColor = true;
            this.buttonSpectre.Click += new System.EventHandler(this.buttonSpectre_Click);
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(633, 334);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(145, 20);
            this.label10.TabIndex = 18;
            this.label10.Text = "Рисование отрезка:";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(647, 359);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(64, 20);
            this.label11.TabIndex = 19;
            this.label11.Text = "Начало:";
            // 
            // textStartP_Y
            // 
            this.textStartP_Y.Font = new System.Drawing.Font("Segoe UI", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.textStartP_Y.Location = new System.Drawing.Point(695, 420);
            this.textStartP_Y.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.textStartP_Y.Name = "textStartP_Y";
            this.textStartP_Y.Size = new System.Drawing.Size(62, 25);
            this.textStartP_Y.TabIndex = 23;
            // 
            // textStartP_X
            // 
            this.textStartP_X.Font = new System.Drawing.Font("Segoe UI", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.textStartP_X.Location = new System.Drawing.Point(695, 383);
            this.textStartP_X.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.textStartP_X.Name = "textStartP_X";
            this.textStartP_X.Size = new System.Drawing.Size(62, 25);
            this.textStartP_X.TabIndex = 22;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(672, 423);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(19, 20);
            this.label12.TabIndex = 21;
            this.label12.Text = "y:";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(673, 386);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(19, 20);
            this.label13.TabIndex = 20;
            this.label13.Text = "x:";
            // 
            // textEndP_Y
            // 
            this.textEndP_Y.Font = new System.Drawing.Font("Segoe UI", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.textEndP_Y.Location = new System.Drawing.Point(826, 417);
            this.textEndP_Y.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.textEndP_Y.Name = "textEndP_Y";
            this.textEndP_Y.Size = new System.Drawing.Size(62, 25);
            this.textEndP_Y.TabIndex = 28;
            // 
            // textEndP_X
            // 
            this.textEndP_X.Font = new System.Drawing.Font("Segoe UI", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point);
            this.textEndP_X.Location = new System.Drawing.Point(826, 380);
            this.textEndP_X.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.textEndP_X.Name = "textEndP_X";
            this.textEndP_X.Size = new System.Drawing.Size(62, 25);
            this.textEndP_X.TabIndex = 27;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(803, 420);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(19, 20);
            this.label14.TabIndex = 26;
            this.label14.Text = "y:";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(803, 383);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(19, 20);
            this.label15.TabIndex = 25;
            this.label15.Text = "x:";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(776, 359);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(56, 20);
            this.label16.TabIndex = 24;
            this.label16.Text = "Конец:";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(697, 460);
            this.button1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(168, 31);
            this.button1.TabIndex = 29;
            this.button1.Text = "Нарисовать отрезок";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // buttonClear
            // 
            this.buttonClear.Location = new System.Drawing.Point(736, 511);
            this.buttonClear.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.buttonClear.Name = "buttonClear";
            this.buttonClear.Size = new System.Drawing.Size(86, 51);
            this.buttonClear.TabIndex = 30;
            this.buttonClear.Text = "Очистка\r\nполотна";
            this.buttonClear.UseVisualStyleBackColor = true;
            this.buttonClear.Click += new System.EventHandler(this.buttonClear_Click);
            // 
            // buttonAsk
            // 
            this.buttonAsk.Location = new System.Drawing.Point(857, 13);
            this.buttonAsk.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.buttonAsk.Name = "buttonAsk";
            this.buttonAsk.Size = new System.Drawing.Size(86, 31);
            this.buttonAsk.TabIndex = 31;
            this.buttonAsk.Text = "Справка";
            this.buttonAsk.UseVisualStyleBackColor = true;
            this.buttonAsk.Click += new System.EventHandler(this.buttonAsk_Click);
            // 
            // buttonCmpAlgs
            // 
            this.buttonCmpAlgs.Location = new System.Drawing.Point(633, 570);
            this.buttonCmpAlgs.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.buttonCmpAlgs.Name = "buttonCmpAlgs";
            this.buttonCmpAlgs.Size = new System.Drawing.Size(130, 73);
            this.buttonCmpAlgs.TabIndex = 32;
            this.buttonCmpAlgs.Text = "Сравнить\r\nалгоритмы по\r\nбыстродействию";
            this.buttonCmpAlgs.UseVisualStyleBackColor = true;
            this.buttonCmpAlgs.Click += new System.EventHandler(this.buttonCmpAlgs_Click);
            // 
            // buttonCompute
            // 
            this.buttonCompute.Location = new System.Drawing.Point(809, 570);
            this.buttonCompute.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.buttonCompute.Name = "buttonCompute";
            this.buttonCompute.Size = new System.Drawing.Size(130, 73);
            this.buttonCompute.TabIndex = 33;
            this.buttonCompute.Text = "Исследовать\r\nалгоритм на\r\nступенчатость";
            this.buttonCompute.UseVisualStyleBackColor = true;
            this.buttonCompute.Click += new System.EventHandler(this.buttonCompute_Click);
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 20F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(955, 653);
            this.Controls.Add(this.buttonCompute);
            this.Controls.Add(this.buttonCmpAlgs);
            this.Controls.Add(this.buttonAsk);
            this.Controls.Add(this.buttonClear);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.textEndP_Y);
            this.Controls.Add(this.textEndP_X);
            this.Controls.Add(this.label14);
            this.Controls.Add(this.label15);
            this.Controls.Add(this.label16);
            this.Controls.Add(this.textStartP_Y);
            this.Controls.Add(this.textStartP_X);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.buttonSpectre);
            this.Controls.Add(this.S_centre_y);
            this.Controls.Add(this.S_centre_x);
            this.Controls.Add(this.S_angle);
            this.Controls.Add(this.S_length);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.choiceAlg);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.bgColor);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.lineColor);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.pictureBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.MaximizeBox = false;
            this.Name = "MainWindow";
            this.Text = "Построение отрезков";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.lineColor)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bgColor)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.PictureBox lineColor;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.PictureBox bgColor;
        private System.Windows.Forms.ColorDialog colorDialog1;
        private System.Windows.Forms.ColorDialog colorDialog2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox choiceAlg;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox S_length;
        private System.Windows.Forms.TextBox S_angle;
        private System.Windows.Forms.TextBox S_centre_x;
        private System.Windows.Forms.TextBox S_centre_y;
        private System.Windows.Forms.Button buttonSpectre;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox textStartP_Y;
        private System.Windows.Forms.TextBox textStartP_X;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.TextBox textEndP_Y;
        private System.Windows.Forms.TextBox textEndP_X;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button buttonClear;
        private System.Windows.Forms.Button buttonAsk;
        private System.Windows.Forms.Button buttonCmpAlgs;
        private System.Windows.Forms.Button buttonCompute;

        #endregion

        /*
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Button drawbutton;
        private System.Windows.Forms.ComboBox choiceAlg;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.PictureBox lineColor;
        private System.Windows.Forms.ColorDialog colorDialog1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.PictureBox bgColor;
        private System.Windows.Forms.ColorDialog colorDialog2;
        private System.Windows.Forms.TextBox textStartP_X;
        private System.Windows.Forms.TextBox textStartP_Y;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox textEndP_X;
        private System.Windows.Forms.TextBox textEndP_Y;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Button buttonClear;
        private System.Windows.Forms.Button buttonAsk;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.TextBox S_length;
        private System.Windows.Forms.TextBox S_angle;
        private System.Windows.Forms.TextBox S_centre_x;
        private System.Windows.Forms.TextBox S_centre_y;
        private System.Windows.Forms.Button buttonSpectre;
        private System.Windows.Forms.Button buttonCmpAlgs;
        private System.Windows.Forms.Button buttonCompute;
        */
    }
}

