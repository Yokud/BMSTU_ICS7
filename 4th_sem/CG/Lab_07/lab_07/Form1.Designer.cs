namespace lab_07
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.canvasBase = new System.Windows.Forms.PictureBox();
            this.buttonClear = new System.Windows.Forms.Button();
            this.buttonCut = new System.Windows.Forms.Button();
            this.textBoxLeft = new System.Windows.Forms.TextBox();
            this.textBoxRight = new System.Windows.Forms.TextBox();
            this.textBoxUp = new System.Windows.Forms.TextBox();
            this.textBoxDown = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.buttonGetCutter = new System.Windows.Forms.Button();
            this.labelLocation = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.buttonInfo = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.canvasBase)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // canvasBase
            // 
            this.canvasBase.BackColor = System.Drawing.Color.White;
            this.canvasBase.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.canvasBase.Location = new System.Drawing.Point(19, 15);
            this.canvasBase.Margin = new System.Windows.Forms.Padding(4);
            this.canvasBase.MaximumSize = new System.Drawing.Size(1649, 907);
            this.canvasBase.Name = "canvasBase";
            this.canvasBase.Size = new System.Drawing.Size(1300, 700);
            this.canvasBase.TabIndex = 11;
            this.canvasBase.TabStop = false;
            this.canvasBase.MouseClick += new System.Windows.Forms.MouseEventHandler(this.canvasBase_MouseClick);
            this.canvasBase.MouseMove += new System.Windows.Forms.MouseEventHandler(this.canvasBase_MouseMove);
            // 
            // buttonClear
            // 
            this.buttonClear.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.buttonClear.Location = new System.Drawing.Point(1327, 64);
            this.buttonClear.Margin = new System.Windows.Forms.Padding(4);
            this.buttonClear.Name = "buttonClear";
            this.buttonClear.Size = new System.Drawing.Size(287, 31);
            this.buttonClear.TabIndex = 4;
            this.buttonClear.Text = "Очистить полотно";
            this.buttonClear.UseVisualStyleBackColor = true;
            this.buttonClear.Click += new System.EventHandler(this.buttonClear_Click);
            // 
            // buttonCut
            // 
            this.buttonCut.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.buttonCut.Location = new System.Drawing.Point(1327, 15);
            this.buttonCut.Margin = new System.Windows.Forms.Padding(4);
            this.buttonCut.Name = "buttonCut";
            this.buttonCut.Size = new System.Drawing.Size(287, 31);
            this.buttonCut.TabIndex = 2;
            this.buttonCut.Text = "Отсечь отрезки";
            this.buttonCut.UseVisualStyleBackColor = true;
            this.buttonCut.Click += new System.EventHandler(this.buttonCut_Click);
            // 
            // textBoxLeft
            // 
            this.textBoxLeft.Location = new System.Drawing.Point(104, 31);
            this.textBoxLeft.Margin = new System.Windows.Forms.Padding(4);
            this.textBoxLeft.Name = "textBoxLeft";
            this.textBoxLeft.Size = new System.Drawing.Size(132, 26);
            this.textBoxLeft.TabIndex = 9;
            // 
            // textBoxRight
            // 
            this.textBoxRight.Location = new System.Drawing.Point(104, 64);
            this.textBoxRight.Margin = new System.Windows.Forms.Padding(4);
            this.textBoxRight.Name = "textBoxRight";
            this.textBoxRight.Size = new System.Drawing.Size(132, 26);
            this.textBoxRight.TabIndex = 10;
            // 
            // textBoxUp
            // 
            this.textBoxUp.Location = new System.Drawing.Point(104, 97);
            this.textBoxUp.Margin = new System.Windows.Forms.Padding(4);
            this.textBoxUp.Name = "textBoxUp";
            this.textBoxUp.Size = new System.Drawing.Size(132, 26);
            this.textBoxUp.TabIndex = 11;
            // 
            // textBoxDown
            // 
            this.textBoxDown.Location = new System.Drawing.Point(104, 134);
            this.textBoxDown.Margin = new System.Windows.Forms.Padding(4);
            this.textBoxDown.Name = "textBoxDown";
            this.textBoxDown.Size = new System.Drawing.Size(132, 26);
            this.textBoxDown.TabIndex = 12;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.label1.Location = new System.Drawing.Point(25, 31);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(66, 20);
            this.label1.TabIndex = 13;
            this.label1.Text = "Левая:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.label2.Location = new System.Drawing.Point(15, 64);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(77, 20);
            this.label2.TabIndex = 14;
            this.label2.Text = "Правая:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.label3.Location = new System.Drawing.Point(7, 97);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(84, 20);
            this.label3.TabIndex = 15;
            this.label3.Text = "Верхняя:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.label4.Location = new System.Drawing.Point(12, 134);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(79, 20);
            this.label4.TabIndex = 16;
            this.label4.Text = "Нижняя:";
            // 
            // buttonGetCutter
            // 
            this.buttonGetCutter.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.buttonGetCutter.Location = new System.Drawing.Point(16, 191);
            this.buttonGetCutter.Margin = new System.Windows.Forms.Padding(4);
            this.buttonGetCutter.Name = "buttonGetCutter";
            this.buttonGetCutter.Size = new System.Drawing.Size(267, 31);
            this.buttonGetCutter.TabIndex = 17;
            this.buttonGetCutter.Text = "Задать отсекатель";
            this.buttonGetCutter.UseVisualStyleBackColor = true;
            this.buttonGetCutter.Click += new System.EventHandler(this.buttonGetCutter_Click);
            // 
            // labelLocation
            // 
            this.labelLocation.AutoSize = true;
            this.labelLocation.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(254)));
            this.labelLocation.Location = new System.Drawing.Point(1327, 129);
            this.labelLocation.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelLocation.Name = "labelLocation";
            this.labelLocation.Size = new System.Drawing.Size(46, 18);
            this.labelLocation.TabIndex = 19;
            this.labelLocation.Text = "label6";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.buttonGetCutter);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.textBoxDown);
            this.groupBox1.Controls.Add(this.textBoxLeft);
            this.groupBox1.Controls.Add(this.textBoxUp);
            this.groupBox1.Controls.Add(this.textBoxRight);
            this.groupBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(254)));
            this.groupBox1.Location = new System.Drawing.Point(1331, 186);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox1.Size = new System.Drawing.Size(295, 301);
            this.groupBox1.TabIndex = 20;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Границы отсекателя";
            // 
            // buttonInfo
            // 
            this.buttonInfo.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(254)));
            this.buttonInfo.Location = new System.Drawing.Point(1347, 684);
            this.buttonInfo.Margin = new System.Windows.Forms.Padding(4);
            this.buttonInfo.Name = "buttonInfo";
            this.buttonInfo.Size = new System.Drawing.Size(272, 31);
            this.buttonInfo.TabIndex = 21;
            this.buttonInfo.Text = "Информация о программе";
            this.buttonInfo.UseVisualStyleBackColor = true;
            this.buttonInfo.Click += new System.EventHandler(this.buttonInfo_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(254)));
            this.label5.Location = new System.Drawing.Point(8, 240);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(280, 51);
            this.label5.TabIndex = 18;
            this.label5.Text = "Внимание: ввод отсекателя удаляет все \r\nотрезки на полотне. \r\nВведите отсекатель " +
    "в первую очередь.";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1635, 738);
            this.Controls.Add(this.buttonInfo);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.labelLocation);
            this.Controls.Add(this.canvasBase);
            this.Controls.Add(this.buttonClear);
            this.Controls.Add(this.buttonCut);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.MaximumSize = new System.Drawing.Size(1994, 974);
            this.MinimumSize = new System.Drawing.Size(794, 420);
            this.Name = "Form1";
            this.Text = "Отсечение отрезков";
            ((System.ComponentModel.ISupportInitialize)(this.canvasBase)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.PictureBox canvasBase;
        private System.Windows.Forms.Button buttonClear;
        private System.Windows.Forms.Button buttonCut;
        private System.Windows.Forms.TextBox textBoxLeft;
        private System.Windows.Forms.TextBox textBoxRight;
        private System.Windows.Forms.TextBox textBoxUp;
        private System.Windows.Forms.TextBox textBoxDown;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button buttonGetCutter;
        private System.Windows.Forms.Label labelLocation;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button buttonInfo;
        private System.Windows.Forms.Label label5;
    }
}

