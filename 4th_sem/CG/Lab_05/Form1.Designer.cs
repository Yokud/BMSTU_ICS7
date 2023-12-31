
namespace Lab_05
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
            this.Canvas = new System.Windows.Forms.PictureBox();
            this.borderGrid = new System.Windows.Forms.DataGridView();
            this.start_x = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.start_y = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.end_x = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.end_y = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.checkSleep = new System.Windows.Forms.CheckBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.fillingColorBox = new System.Windows.Forms.PictureBox();
            this.borderColorBox = new System.Windows.Forms.PictureBox();
            this.buttonBG = new System.Windows.Forms.Button();
            this.bgColorBox = new System.Windows.Forms.PictureBox();
            this.buttonClearCanvas = new System.Windows.Forms.Button();
            this.buttonDraw = new System.Windows.Forms.Button();
            this.fillingColorDialog = new System.Windows.Forms.ColorDialog();
            this.borderColorDialog = new System.Windows.Forms.ColorDialog();
            this.bgColorDialog = new System.Windows.Forms.ColorDialog();
            this.buttonAsk = new System.Windows.Forms.Button();
            this.buttonClearList = new System.Windows.Forms.Button();
            this.Horizontal = new System.Windows.Forms.RadioButton();
            this.Vertical = new System.Windows.Forms.RadioButton();
            this.panel1 = new System.Windows.Forms.Panel();
            this.Standart = new System.Windows.Forms.RadioButton();
            this.buttonUpdateCanvas = new System.Windows.Forms.Button();
            this.buttonClosePol = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.Canvas)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.borderGrid)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.fillingColorBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.borderColorBox)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bgColorBox)).BeginInit();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // Canvas
            // 
            this.Canvas.BackColor = System.Drawing.Color.White;
            this.Canvas.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.Canvas.Location = new System.Drawing.Point(14, 14);
            this.Canvas.Name = "Canvas";
            this.Canvas.Size = new System.Drawing.Size(825, 740);
            this.Canvas.TabIndex = 0;
            this.Canvas.TabStop = false;
            this.Canvas.MouseClick += new System.Windows.Forms.MouseEventHandler(this.Canvas_MouseClick);
            this.Canvas.MouseMove += new System.Windows.Forms.MouseEventHandler(this.Canvas_MouseMove);
            // 
            // borderGrid
            // 
            this.borderGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.borderGrid.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.start_x,
            this.start_y,
            this.end_x,
            this.end_y});
            this.borderGrid.Location = new System.Drawing.Point(845, 36);
            this.borderGrid.Name = "borderGrid";
            this.borderGrid.RowHeadersWidth = 51;
            this.borderGrid.RowTemplate.Height = 24;
            this.borderGrid.Size = new System.Drawing.Size(554, 383);
            this.borderGrid.TabIndex = 1;
            // 
            // start_x
            // 
            this.start_x.HeaderText = "Начальный X";
            this.start_x.MinimumWidth = 6;
            this.start_x.Name = "start_x";
            this.start_x.Width = 125;
            // 
            // start_y
            // 
            this.start_y.HeaderText = "Начальный Y";
            this.start_y.MinimumWidth = 6;
            this.start_y.Name = "start_y";
            this.start_y.Width = 125;
            // 
            // end_x
            // 
            this.end_x.HeaderText = "Конечный X";
            this.end_x.MinimumWidth = 6;
            this.end_x.Name = "end_x";
            this.end_x.Width = 125;
            // 
            // end_y
            // 
            this.end_y.HeaderText = "Конечный Y";
            this.end_y.MinimumWidth = 6;
            this.end_y.Name = "end_y";
            this.end_y.Width = 125;
            // 
            // checkSleep
            // 
            this.checkSleep.AutoSize = true;
            this.checkSleep.Location = new System.Drawing.Point(1050, 444);
            this.checkSleep.Name = "checkSleep";
            this.checkSleep.Size = new System.Drawing.Size(187, 21);
            this.checkSleep.TabIndex = 2;
            this.checkSleep.Text = "Заполнять с задержкой";
            this.checkSleep.UseVisualStyleBackColor = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(846, 445);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(128, 17);
            this.label1.TabIndex = 3;
            this.label1.Text = "Цвет заполнения:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(885, 474);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(89, 17);
            this.label2.TabIndex = 4;
            this.label2.Text = "Цвет рёбер:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(846, 585);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(84, 17);
            this.label3.TabIndex = 5;
            this.label3.Text = "Цвет фона:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.BackColor = System.Drawing.Color.White;
            this.label4.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label4.Location = new System.Drawing.Point(845, 14);
            this.label4.Name = "label4";
            this.label4.Padding = new System.Windows.Forms.Padding(122, 2, 121, 2);
            this.label4.Size = new System.Drawing.Size(554, 23);
            this.label4.TabIndex = 6;
            this.label4.Text = "Список рёбер произвольного многоугольника";
            this.label4.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // fillingColorBox
            // 
            this.fillingColorBox.BackColor = System.Drawing.Color.Red;
            this.fillingColorBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.fillingColorBox.Location = new System.Drawing.Point(980, 445);
            this.fillingColorBox.Name = "fillingColorBox";
            this.fillingColorBox.Size = new System.Drawing.Size(50, 20);
            this.fillingColorBox.TabIndex = 7;
            this.fillingColorBox.TabStop = false;
            this.fillingColorBox.Click += new System.EventHandler(this.fillingColorBox_Click);
            // 
            // borderColorBox
            // 
            this.borderColorBox.BackColor = System.Drawing.Color.Black;
            this.borderColorBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.borderColorBox.Location = new System.Drawing.Point(980, 474);
            this.borderColorBox.Name = "borderColorBox";
            this.borderColorBox.Size = new System.Drawing.Size(50, 20);
            this.borderColorBox.TabIndex = 8;
            this.borderColorBox.TabStop = false;
            this.borderColorBox.Click += new System.EventHandler(this.borderColorBox_Click);
            // 
            // buttonBG
            // 
            this.buttonBG.Location = new System.Drawing.Point(992, 579);
            this.buttonBG.Name = "buttonBG";
            this.buttonBG.Size = new System.Drawing.Size(158, 28);
            this.buttonBG.TabIndex = 9;
            this.buttonBG.Text = "Изменить цвет фона";
            this.buttonBG.UseVisualStyleBackColor = true;
            this.buttonBG.Click += new System.EventHandler(this.buttonBG_Click);
            // 
            // bgColorBox
            // 
            this.bgColorBox.BackColor = System.Drawing.Color.White;
            this.bgColorBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.bgColorBox.Location = new System.Drawing.Point(936, 585);
            this.bgColorBox.Name = "bgColorBox";
            this.bgColorBox.Size = new System.Drawing.Size(50, 20);
            this.bgColorBox.TabIndex = 10;
            this.bgColorBox.TabStop = false;
            this.bgColorBox.Click += new System.EventHandler(this.bgColorBox_Click);
            // 
            // buttonClearCanvas
            // 
            this.buttonClearCanvas.Location = new System.Drawing.Point(1252, 514);
            this.buttonClearCanvas.Name = "buttonClearCanvas";
            this.buttonClearCanvas.Size = new System.Drawing.Size(147, 28);
            this.buttonClearCanvas.TabIndex = 11;
            this.buttonClearCanvas.Text = "Очистить полотно";
            this.buttonClearCanvas.UseVisualStyleBackColor = true;
            this.buttonClearCanvas.Click += new System.EventHandler(this.buttonClearCanvas_Click);
            // 
            // buttonDraw
            // 
            this.buttonDraw.Location = new System.Drawing.Point(936, 658);
            this.buttonDraw.Name = "buttonDraw";
            this.buttonDraw.Size = new System.Drawing.Size(152, 35);
            this.buttonDraw.TabIndex = 12;
            this.buttonDraw.Text = "Закрасить область";
            this.buttonDraw.UseVisualStyleBackColor = true;
            this.buttonDraw.Click += new System.EventHandler(this.buttonDraw_Click);
            // 
            // buttonAsk
            // 
            this.buttonAsk.Location = new System.Drawing.Point(1094, 726);
            this.buttonAsk.Name = "buttonAsk";
            this.buttonAsk.Size = new System.Drawing.Size(75, 27);
            this.buttonAsk.TabIndex = 13;
            this.buttonAsk.Text = "Справка";
            this.buttonAsk.UseVisualStyleBackColor = true;
            this.buttonAsk.Click += new System.EventHandler(this.buttonAsk_Click);
            // 
            // buttonClearList
            // 
            this.buttonClearList.Location = new System.Drawing.Point(1252, 443);
            this.buttonClearList.Name = "buttonClearList";
            this.buttonClearList.Size = new System.Drawing.Size(147, 48);
            this.buttonClearList.TabIndex = 14;
            this.buttonClearList.Text = "Очистить список\r\nрёбер";
            this.buttonClearList.UseVisualStyleBackColor = true;
            this.buttonClearList.Click += new System.EventHandler(this.buttonClearList_Click);
            // 
            // Horizontal
            // 
            this.Horizontal.AutoSize = true;
            this.Horizontal.Location = new System.Drawing.Point(3, 31);
            this.Horizontal.Name = "Horizontal";
            this.Horizontal.Size = new System.Drawing.Size(240, 21);
            this.Horizontal.TabIndex = 15;
            this.Horizontal.TabStop = true;
            this.Horizontal.Text = "Ввести горизонтальную прямую";
            this.Horizontal.UseVisualStyleBackColor = true;
            // 
            // Vertical
            // 
            this.Vertical.AutoSize = true;
            this.Vertical.Location = new System.Drawing.Point(4, 57);
            this.Vertical.Name = "Vertical";
            this.Vertical.Size = new System.Drawing.Size(226, 21);
            this.Vertical.TabIndex = 16;
            this.Vertical.TabStop = true;
            this.Vertical.Text = "Ввести вертикальную прямую";
            this.Vertical.UseVisualStyleBackColor = true;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.Standart);
            this.panel1.Controls.Add(this.Horizontal);
            this.panel1.Controls.Add(this.Vertical);
            this.panel1.Location = new System.Drawing.Point(1154, 627);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(245, 81);
            this.panel1.TabIndex = 17;
            // 
            // Standart
            // 
            this.Standart.AutoSize = true;
            this.Standart.Checked = true;
            this.Standart.Location = new System.Drawing.Point(4, 4);
            this.Standart.Name = "Standart";
            this.Standart.Size = new System.Drawing.Size(227, 21);
            this.Standart.TabIndex = 17;
            this.Standart.TabStop = true;
            this.Standart.Text = "Ввести произвольную прямую";
            this.Standart.UseVisualStyleBackColor = true;
            // 
            // buttonUpdateCanvas
            // 
            this.buttonUpdateCanvas.Location = new System.Drawing.Point(1230, 559);
            this.buttonUpdateCanvas.Name = "buttonUpdateCanvas";
            this.buttonUpdateCanvas.Size = new System.Drawing.Size(169, 62);
            this.buttonUpdateCanvas.TabIndex = 18;
            this.buttonUpdateCanvas.Text = "Синхронизировать \r\nполотно со списком \r\nрёбер";
            this.buttonUpdateCanvas.UseVisualStyleBackColor = true;
            this.buttonUpdateCanvas.Click += new System.EventHandler(this.buttonUpdateCanvas_Click);
            // 
            // buttonClosePol
            // 
            this.buttonClosePol.Location = new System.Drawing.Point(1050, 505);
            this.buttonClosePol.Name = "buttonClosePol";
            this.buttonClosePol.Size = new System.Drawing.Size(119, 37);
            this.buttonClosePol.TabIndex = 19;
            this.buttonClosePol.Text = "Замкнуть";
            this.buttonClosePol.UseVisualStyleBackColor = true;
            this.buttonClosePol.Click += new System.EventHandler(this.buttonClosePol_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1411, 764);
            this.Controls.Add(this.buttonClosePol);
            this.Controls.Add(this.buttonUpdateCanvas);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.buttonClearList);
            this.Controls.Add(this.buttonAsk);
            this.Controls.Add(this.buttonDraw);
            this.Controls.Add(this.buttonClearCanvas);
            this.Controls.Add(this.bgColorBox);
            this.Controls.Add(this.buttonBG);
            this.Controls.Add(this.borderColorBox);
            this.Controls.Add(this.fillingColorBox);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.checkSleep);
            this.Controls.Add(this.borderGrid);
            this.Controls.Add(this.Canvas);
            this.Name = "Form1";
            this.Text = "Алгоритм заполнения со списком рёбер и флагом";
            ((System.ComponentModel.ISupportInitialize)(this.Canvas)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.borderGrid)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.fillingColorBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.borderColorBox)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bgColorBox)).EndInit();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox Canvas;
        private System.Windows.Forms.DataGridView borderGrid;
        private System.Windows.Forms.DataGridViewTextBoxColumn start_x;
        private System.Windows.Forms.DataGridViewTextBoxColumn start_y;
        private System.Windows.Forms.DataGridViewTextBoxColumn end_x;
        private System.Windows.Forms.DataGridViewTextBoxColumn end_y;
        private System.Windows.Forms.CheckBox checkSleep;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.PictureBox fillingColorBox;
        private System.Windows.Forms.PictureBox borderColorBox;
        private System.Windows.Forms.Button buttonBG;
        private System.Windows.Forms.PictureBox bgColorBox;
        private System.Windows.Forms.Button buttonClearCanvas;
        private System.Windows.Forms.Button buttonDraw;
        private System.Windows.Forms.ColorDialog fillingColorDialog;
        private System.Windows.Forms.ColorDialog borderColorDialog;
        private System.Windows.Forms.ColorDialog bgColorDialog;
        private System.Windows.Forms.Button buttonAsk;
        private System.Windows.Forms.Button buttonClearList;
        private System.Windows.Forms.RadioButton Horizontal;
        private System.Windows.Forms.RadioButton Vertical;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.RadioButton Standart;
        private System.Windows.Forms.Button buttonUpdateCanvas;
        private System.Windows.Forms.Button buttonClosePol;
    }
}

