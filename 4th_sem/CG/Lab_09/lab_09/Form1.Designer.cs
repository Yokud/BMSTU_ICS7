namespace lab_09
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
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.buttonAddDot = new System.Windows.Forms.Button();
            this.labelY = new System.Windows.Forms.Label();
            this.labelX = new System.Windows.Forms.Label();
            this.textBoxY = new System.Windows.Forms.TextBox();
            this.textBoxX = new System.Windows.Forms.TextBox();
            this.checkBoxFill = new System.Windows.Forms.CheckBox();
            this.radioButtonLines = new System.Windows.Forms.RadioButton();
            this.radioButtonCutter = new System.Windows.Forms.RadioButton();
            this.labelLocation = new System.Windows.Forms.Label();
            this.buttonCut = new System.Windows.Forms.Button();
            this.buttonClear = new System.Windows.Forms.Button();
            this.canvasBase = new System.Windows.Forms.PictureBox();
            this.colorDialog = new System.Windows.Forms.ColorDialog();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.canvasBase)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.buttonAddDot);
            this.groupBox1.Controls.Add(this.labelY);
            this.groupBox1.Controls.Add(this.labelX);
            this.groupBox1.Controls.Add(this.textBoxY);
            this.groupBox1.Controls.Add(this.textBoxX);
            this.groupBox1.Controls.Add(this.checkBoxFill);
            this.groupBox1.Controls.Add(this.radioButtonLines);
            this.groupBox1.Controls.Add(this.radioButtonCutter);
            this.groupBox1.Controls.Add(this.labelLocation);
            this.groupBox1.Controls.Add(this.buttonCut);
            this.groupBox1.Controls.Add(this.buttonClear);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Right;
            this.groupBox1.Location = new System.Drawing.Point(1225, 0);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.groupBox1.Size = new System.Drawing.Size(288, 930);
            this.groupBox1.TabIndex = 16;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Панель управления";
            // 
            // buttonAddDot
            // 
            this.buttonAddDot.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.buttonAddDot.Location = new System.Drawing.Point(1, 417);
            this.buttonAddDot.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.buttonAddDot.Name = "buttonAddDot";
            this.buttonAddDot.Size = new System.Drawing.Size(287, 28);
            this.buttonAddDot.TabIndex = 19;
            this.buttonAddDot.Text = "Добавить точку";
            this.buttonAddDot.UseVisualStyleBackColor = true;
            this.buttonAddDot.Click += new System.EventHandler(this.buttonAddDot_Click);
            // 
            // labelY
            // 
            this.labelY.AutoSize = true;
            this.labelY.Location = new System.Drawing.Point(159, 334);
            this.labelY.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelY.Name = "labelY";
            this.labelY.Size = new System.Drawing.Size(21, 17);
            this.labelY.TabIndex = 18;
            this.labelY.Text = "Y:";
            // 
            // labelX
            // 
            this.labelX.AutoSize = true;
            this.labelX.Location = new System.Drawing.Point(15, 330);
            this.labelX.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelX.Name = "labelX";
            this.labelX.Size = new System.Drawing.Size(21, 17);
            this.labelX.TabIndex = 17;
            this.labelX.Text = "X:";
            // 
            // textBoxY
            // 
            this.textBoxY.Location = new System.Drawing.Point(163, 353);
            this.textBoxY.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.textBoxY.Name = "textBoxY";
            this.textBoxY.Size = new System.Drawing.Size(109, 22);
            this.textBoxY.TabIndex = 16;
            // 
            // textBoxX
            // 
            this.textBoxX.Location = new System.Drawing.Point(13, 353);
            this.textBoxX.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.textBoxX.Name = "textBoxX";
            this.textBoxX.Size = new System.Drawing.Size(109, 22);
            this.textBoxX.TabIndex = 15;
            // 
            // checkBoxFill
            // 
            this.checkBoxFill.AutoSize = true;
            this.checkBoxFill.Location = new System.Drawing.Point(8, 545);
            this.checkBoxFill.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.checkBoxFill.Name = "checkBoxFill";
            this.checkBoxFill.Size = new System.Drawing.Size(85, 21);
            this.checkBoxFill.TabIndex = 10;
            this.checkBoxFill.Text = "Заливка";
            this.checkBoxFill.UseVisualStyleBackColor = true;
            // 
            // radioButtonLines
            // 
            this.radioButtonLines.AutoSize = true;
            this.radioButtonLines.Location = new System.Drawing.Point(12, 242);
            this.radioButtonLines.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.radioButtonLines.Name = "radioButtonLines";
            this.radioButtonLines.Size = new System.Drawing.Size(169, 21);
            this.radioButtonLines.TabIndex = 9;
            this.radioButtonLines.TabStop = true;
            this.radioButtonLines.Text = "Ввод многоугольника";
            this.radioButtonLines.UseVisualStyleBackColor = true;
            // 
            // radioButtonCutter
            // 
            this.radioButtonCutter.AutoSize = true;
            this.radioButtonCutter.Location = new System.Drawing.Point(12, 214);
            this.radioButtonCutter.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.radioButtonCutter.Name = "radioButtonCutter";
            this.radioButtonCutter.Size = new System.Drawing.Size(141, 21);
            this.radioButtonCutter.TabIndex = 8;
            this.radioButtonCutter.TabStop = true;
            this.radioButtonCutter.Text = "Ввод отсекателя";
            this.radioButtonCutter.UseVisualStyleBackColor = true;
            // 
            // labelLocation
            // 
            this.labelLocation.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.labelLocation.AutoSize = true;
            this.labelLocation.BackColor = System.Drawing.Color.Transparent;
            this.labelLocation.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.labelLocation.Location = new System.Drawing.Point(8, 146);
            this.labelLocation.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.labelLocation.Name = "labelLocation";
            this.labelLocation.Size = new System.Drawing.Size(53, 20);
            this.labelLocation.TabIndex = 3;
            this.labelLocation.Text = "label1";
            // 
            // buttonCut
            // 
            this.buttonCut.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.buttonCut.Location = new System.Drawing.Point(0, 35);
            this.buttonCut.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.buttonCut.Name = "buttonCut";
            this.buttonCut.Size = new System.Drawing.Size(287, 28);
            this.buttonCut.TabIndex = 2;
            this.buttonCut.Text = "Отсечь";
            this.buttonCut.UseVisualStyleBackColor = true;
            this.buttonCut.Click += new System.EventHandler(this.buttonCut_Click);
            // 
            // buttonClear
            // 
            this.buttonClear.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F);
            this.buttonClear.Location = new System.Drawing.Point(0, 81);
            this.buttonClear.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.buttonClear.Name = "buttonClear";
            this.buttonClear.Size = new System.Drawing.Size(287, 28);
            this.buttonClear.TabIndex = 4;
            this.buttonClear.Text = "Очистить";
            this.buttonClear.UseVisualStyleBackColor = true;
            this.buttonClear.Click += new System.EventHandler(this.buttonClear_Click);
            // 
            // canvasBase
            // 
            this.canvasBase.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.canvasBase.BackColor = System.Drawing.Color.White;
            this.canvasBase.Location = new System.Drawing.Point(1, 15);
            this.canvasBase.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.canvasBase.MaximumSize = new System.Drawing.Size(1649, 907);
            this.canvasBase.Name = "canvasBase";
            this.canvasBase.Size = new System.Drawing.Size(1216, 901);
            this.canvasBase.TabIndex = 15;
            this.canvasBase.TabStop = false;
            this.canvasBase.Click += new System.EventHandler(this.canvasBase_Click);
            this.canvasBase.MouseMove += new System.Windows.Forms.MouseEventHandler(this.canvasBase_MouseMove);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1513, 930);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.canvasBase);
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Name = "Form1";
            this.Text = "lab_09 Алгоритм отсечения Сазерленда-Ходжмана";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.canvasBase)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton radioButtonLines;
        private System.Windows.Forms.RadioButton radioButtonCutter;
        private System.Windows.Forms.Label labelLocation;
        private System.Windows.Forms.Button buttonCut;
        private System.Windows.Forms.Button buttonClear;
        private System.Windows.Forms.PictureBox canvasBase;
        private System.Windows.Forms.ColorDialog colorDialog;
        private System.Windows.Forms.CheckBox checkBoxFill;
        private System.Windows.Forms.Button buttonAddDot;
        private System.Windows.Forms.Label labelY;
        private System.Windows.Forms.Label labelX;
        private System.Windows.Forms.TextBox textBoxY;
        private System.Windows.Forms.TextBox textBoxX;
    }
}

