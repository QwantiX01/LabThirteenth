#pragma once

namespace LabThirteenth {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	int N = 0;
	double eps = 0.00001;
	double R = 0;
	double A[6][6];
	double C[6][6];
	double B[6];
	double X[6];

	bool Gauss(double A[6][6], double B[6], int N, double X[6])
	{
		const double eps = 1e-10;
		int index[6];
		double scale[6];

		for (int i = 1; i <= N; i++) {
			index[i] = i;
		}

		for (int i = 1; i <= N; i++) {
			double scalemax = 0;
			for (int j = 1; j <= N; j++) {
				scalemax = Math::Max(scalemax, Math::Abs(A[i][j]));
			}
			if (scalemax == 0) {
				return false;
			}
			scale[i] = scalemax;
		}

		for (int k = 1; k < N; k++) {
			double rmax = 0;
			int maxIndex = k;

			for (int i = k; i <= N; i++) {
				double r = Math::Abs(A[index[i]][k] / scale[index[i]]);
				if (r > rmax) {
					rmax = r;
					maxIndex = i;
				}
			}

			if (Math::Abs(A[index[maxIndex]][k]) < eps) {
				return false;
			}

			if (maxIndex != k) {
				int temp = index[k];
				index[k] = index[maxIndex];
				index[maxIndex] = temp;
			}

			for (int i = k + 1; i <= N; i++) {
				double mult = A[index[i]][k] / A[index[k]][k];
				A[index[i]][k] = mult;

				for (int j = k + 1; j <= N; j++) {
					A[index[i]][j] -= mult * A[index[k]][j];
				}

				B[index[i]] -= mult * B[index[k]];
			}
		}

		// Перевірка останнього діагонального елемента
		if (Math::Abs(A[index[N]][N]) < eps) {
			return false;
		}

		// Зворотній хід
		for (int k = N; k >= 1; k--) {
			double sum = 0;
			for (int j = k + 1; j <= N; j++) {
				sum += A[index[k]][j] * X[j];
			}
			X[k] = (B[index[k]] - sum) / A[index[k]][k];
		}

		return true;
	}
	bool makeTriangular(double A[6][6], double B[6], int N)
	{
		const double eps = 1e-10;  // Точність для перевірки на нуль

		for (int k = 1; k < N; k++) {
			if (Math::Abs(A[k][k]) < eps) {
				bool found = false;
				for (int i = k + 1; i <= N; i++) {
					if (Math::Abs(A[i][k]) > eps) {
						for (int j = k; j <= N; j++) {
							double temp = A[k][j];
							A[k][j] = A[i][j];
							A[i][j] = temp;
						}
						double temp = B[k];
						B[k] = B[i];
						B[i] = temp;
						found = true;
						break;
					}
				}
				if (!found) {
					return false;
				}
			}

			for (int i = k + 1; i <= N; i++) {
				double factor = A[i][k] / A[k][k];
				for (int j = k; j <= N; j++) {
					A[i][j] -= factor * A[k][j];
				}
				B[i] -= factor * B[k];
			}
		}

		if (Math::Abs(A[N][N]) < eps) {
			return false;
		}

		return true;
	}

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();

		}

	protected:
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::NumericUpDown^ numericUpDown1;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::DataGridView^ dataGridView2;
	private: System::Windows::Forms::DataGridView^ dataGridView3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::DataGridView^ dataGridView4;
	private: System::Windows::Forms::Button^ button4;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridView2 = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridView3 = (gcnew System::Windows::Forms::DataGridView());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->dataGridView4 = (gcnew System::Windows::Forms::DataGridView());
			this->button4 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView4))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Rubik", 14));
			this->label1->Location = System::Drawing::Point(12, 20);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(155, 24);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Розмір системи";
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Font = (gcnew System::Drawing::Font(L"Rubik", 14));
			this->numericUpDown1->Location = System::Drawing::Point(221, 18);
			this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 5, 0, 0, 0 });
			this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(63, 30);
			this->numericUpDown1->TabIndex = 1;
			this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
			this->numericUpDown1->ValueChanged += gcnew System::EventHandler(this, &MyForm::numericUpDown1_ValueChanged);
			// 
			// dataGridView1
			// 
			this->dataGridView1->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(197)),
				static_cast<System::Int32>(static_cast<System::Byte>(211)), static_cast<System::Int32>(static_cast<System::Byte>(232)));
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->ColumnHeadersVisible = false;
			this->dataGridView1->Location = System::Drawing::Point(16, 144);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersVisible = false;
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->Size = System::Drawing::Size(501, 218);
			this->dataGridView1->TabIndex = 2;
			// 
			// dataGridView2
			// 
			this->dataGridView2->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(197)),
				static_cast<System::Int32>(static_cast<System::Byte>(211)), static_cast<System::Int32>(static_cast<System::Byte>(232)));
			this->dataGridView2->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView2->ColumnHeadersVisible = false;
			this->dataGridView2->Location = System::Drawing::Point(544, 144);
			this->dataGridView2->Name = L"dataGridView2";
			this->dataGridView2->RowHeadersVisible = false;
			this->dataGridView2->RowTemplate->Height = 24;
			this->dataGridView2->Size = System::Drawing::Size(169, 218);
			this->dataGridView2->TabIndex = 3;
			// 
			// dataGridView3
			// 
			this->dataGridView3->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(197)),
				static_cast<System::Int32>(static_cast<System::Byte>(211)), static_cast<System::Int32>(static_cast<System::Byte>(232)));
			this->dataGridView3->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView3->ColumnHeadersVisible = false;
			this->dataGridView3->Location = System::Drawing::Point(732, 144);
			this->dataGridView3->Name = L"dataGridView3";
			this->dataGridView3->ReadOnly = true;
			this->dataGridView3->RowHeadersVisible = false;
			this->dataGridView3->RowTemplate->Height = 24;
			this->dataGridView3->Size = System::Drawing::Size(178, 218);
			this->dataGridView3->TabIndex = 4;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Rubik", 14));
			this->label2->Location = System::Drawing::Point(12, 104);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(108, 24);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Матриця A";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Rubik", 14));
			this->label3->Location = System::Drawing::Point(540, 104);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(93, 24);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Вектор X";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Rubik", 14));
			this->label4->Location = System::Drawing::Point(728, 104);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(94, 24);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Вектор B";
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(208)), static_cast<System::Int32>(static_cast<System::Byte>(232)),
				static_cast<System::Int32>(static_cast<System::Byte>(197)));
			this->button1->Font = (gcnew System::Drawing::Font(L"Rubik", 14));
			this->button1->Location = System::Drawing::Point(544, 473);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(182, 78);
			this->button1->TabIndex = 8;
			this->button1->Text = L"Розв\'язати";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(197)), static_cast<System::Int32>(static_cast<System::Byte>(211)),
				static_cast<System::Int32>(static_cast<System::Byte>(232)));
			this->button2->Font = (gcnew System::Drawing::Font(L"Rubik", 14));
			this->button2->Location = System::Drawing::Point(732, 557);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(178, 82);
			this->button2->TabIndex = 9;
			this->button2->Text = L"Очистити";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(128)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->button3->Font = (gcnew System::Drawing::Font(L"Rubik", 14));
			this->button3->Location = System::Drawing::Point(732, 473);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(178, 78);
			this->button3->TabIndex = 10;
			this->button3->Text = L"Завершити";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Rubik", 14));
			this->label5->Location = System::Drawing::Point(12, 381);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(108, 24);
			this->label5->TabIndex = 12;
			this->label5->Text = L"Матриця A";
			// 
			// dataGridView4
			// 
			this->dataGridView4->BackgroundColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(197)),
				static_cast<System::Int32>(static_cast<System::Byte>(211)), static_cast<System::Int32>(static_cast<System::Byte>(232)));
			this->dataGridView4->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView4->ColumnHeadersVisible = false;
			this->dataGridView4->Location = System::Drawing::Point(16, 421);
			this->dataGridView4->Name = L"dataGridView4";
			this->dataGridView4->RowHeadersVisible = false;
			this->dataGridView4->RowTemplate->Height = 24;
			this->dataGridView4->Size = System::Drawing::Size(501, 218);
			this->dataGridView4->TabIndex = 11;
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(208)), static_cast<System::Int32>(static_cast<System::Byte>(232)),
				static_cast<System::Int32>(static_cast<System::Byte>(197)));
			this->button4->Font = (gcnew System::Drawing::Font(L"Rubik", 14));
			this->button4->Location = System::Drawing::Point(544, 557);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(182, 82);
			this->button4->TabIndex = 13;
			this->button4->Text = L"Розв\'язати (прямий хід)";
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(166)), static_cast<System::Int32>(static_cast<System::Byte>(174)),
				static_cast<System::Int32>(static_cast<System::Byte>(191)));
			this->ClientSize = System::Drawing::Size(936, 666);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->dataGridView4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->dataGridView3);
			this->Controls->Add(this->dataGridView2);
			this->Controls->Add(this->dataGridView1);
			this->Controls->Add(this->numericUpDown1);
			this->Controls->Add(this->label1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView4))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void numericUpDown1_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		int shyr = dataGridView1->Width - 10;
		N = Convert::ToInt32(numericUpDown1->Value);

		dataGridView1->RowCount = N;
		dataGridView1->ColumnCount = N;
		dataGridView4->RowCount = N;
		dataGridView4->ColumnCount = N;
		dataGridView2->RowCount = N;
		dataGridView3->RowCount = N;

		for (int i = 0;i < N;i++)
		{
			dataGridView1->Columns[i]->Width = shyr / N;
		}

	}


	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		dataGridView3->ReadOnly = true;

		dataGridView1->AllowUserToAddRows = false;
		dataGridView2->AllowUserToAddRows = false;
		dataGridView3->AllowUserToAddRows = false;
		dataGridView4->AllowUserToAddRows = false;

		dataGridView1->ColumnCount = 1;
		dataGridView1->RowCount = 1;

		dataGridView2->ColumnCount = 1;
		dataGridView2->RowCount = 1;

		dataGridView3->ColumnCount = 1;
		dataGridView3->RowCount = 1;

		dataGridView4->ColumnCount = 1;
		dataGridView4->RowCount = 1;
	}

	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		Close();
	}

	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		for each (DataGridViewRow ^ row in dataGridView1->Rows) {
			for each (DataGridViewCell ^ cell in row->Cells) {
				cell->Value = nullptr;
			}
		}

		for each (DataGridViewRow ^ row in dataGridView2->Rows) {
			for each (DataGridViewCell ^ cell in row->Cells) {
				cell->Value = nullptr;
			}
		}

		for each (DataGridViewRow ^ row in dataGridView3->Rows) {
			for each (DataGridViewCell ^ cell in row->Cells) {
				cell->Value = nullptr;
			}
		}

		for each (DataGridViewRow ^ row in dataGridView4->Rows) {
			for each (DataGridViewCell ^ cell in row->Cells) {
				cell->Value = nullptr;
			}
		}

	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		int N = Convert::ToInt32(numericUpDown1->Value);

		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				A[i][j] = Convert::ToDouble(dataGridView1->Rows[i - 1]->Cells[j - 1]->Value);
			}
		}

		for (int j = 1; j <= N; j++) {
			B[j] = Convert::ToDouble(dataGridView2->Rows[j - 1]->Cells[0]->Value);
		}

		if (Gauss(A, B, N, X)) {
			for (int i = 1; i <= N; i++) {
				dataGridView3->Rows[i - 1]->Cells[0]->Value = Convert::ToString(X[i]);
			}
			MessageBox::Show(L"Розв'язок знайдено", L"Результат");
		}
		else {
			for (int i = 1; i <= N; i++) {
				dataGridView3->Rows[i - 1]->Cells[0]->Value = "?";
			}
			MessageBox::Show(L"Матриця коефіцієнтів системи є виродженою!");
			return;
		}
	}

	private: System::Void BClear_Click(System::Object^ sender, System::EventArgs^ e)
	{
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				dataGridView1->Rows[1]->Cells[i]->Value = "";

		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				dataGridView4->Rows[1]->Cells[i]->Value = "";

		for (int j = 0; j < N; j++)
		{
			dataGridView2->Rows[0]->Cells[j]->Value = "";
			dataGridView3->Rows[1]->Cells[j]->Value = "";
		}
	}

	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				C[i][j] = A[i][j];
			}
		}

		double tempB[6] = { 0 };
		for (int i = 1; i <= N; i++) {
			tempB[i] = 0;
		}

		if (makeTriangular(C, tempB, N)) {
			dataGridView4->Rows->Clear();

			for (int i = 0; i < N; i++) {
				dataGridView4->Rows->Add();
			}

			for (int i = 1; i <= N; i++) {
				for (int j = 1; j <= N; j++) {
					dataGridView4->Rows[i - 1]->Cells[j - 1]->Value = Convert::ToString(C[i][j]);
				}
			}
			MessageBox::Show(L"Матрицю успішно перетворено на трикутну");
		}
		else {
			MessageBox::Show(L"Матриця вироджена!");
		}
	}
	};
};

