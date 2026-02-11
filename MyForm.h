#pragma once

namespace FormExplab4 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::Odbc; // Бібліотека для MySQL 

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

	private:
		// Оголошуємо компоненти 
		System::Windows::Forms::TextBox^ txtProc;
		System::Windows::Forms::TextBox^ txtHDD;
		System::Windows::Forms::TextBox^ txtRAM;
		System::Windows::Forms::TextBox^ txtPower;
		System::Windows::Forms::Button^ btnAdd;
		System::Windows::Forms::Label^ lblInfo;
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->txtProc = (gcnew System::Windows::Forms::TextBox());
			this->txtHDD = (gcnew System::Windows::Forms::TextBox());
			this->txtRAM = (gcnew System::Windows::Forms::TextBox());
			this->txtPower = (gcnew System::Windows::Forms::TextBox());
			this->btnAdd = (gcnew System::Windows::Forms::Button());
			this->lblInfo = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();

		
			this->lblInfo->AutoSize = true;
			this->lblInfo->Location = System::Drawing::Point(20, 15);
			this->lblInfo->Text = L"Облік аксесуарів (Вар. 24): Процесор, HDD, ОЗУ, БП";

			// Поля для введення даних [cite: 69]
			this->txtProc->Location = System::Drawing::Point(25, 45);
			this->txtProc->Size = System::Drawing::Size(230, 22);

			this->txtHDD->Location = System::Drawing::Point(25, 75);
			this->txtHDD->Size = System::Drawing::Size(230, 22);

			this->txtRAM->Location = System::Drawing::Point(25, 105);
			this->txtRAM->Size = System::Drawing::Size(230, 22);

			this->txtPower->Location = System::Drawing::Point(25, 135);
			this->txtPower->Size = System::Drawing::Size(230, 22);

			// Кнопка додавання 
			this->btnAdd->Location = System::Drawing::Point(25, 175);
			this->btnAdd->Size = System::Drawing::Size(120, 35);
			this->btnAdd->Text = L"Додати в БД";
			this->btnAdd->Click += gcnew System::EventHandler(this, &MyForm::btnAdd_Click);

			// Параметри вікна 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(320, 260);
			this->Controls->Add(this->lblInfo);
			this->Controls->Add(this->txtProc);
			this->Controls->Add(this->txtHDD);
			this->Controls->Add(this->txtRAM);
			this->Controls->Add(this->txtPower);
			this->Controls->Add(this->btnAdd);
			this->Name = L"MyForm";
			this->Text = L"Lab 4 - Accessories (Var 24)";
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion

		// Дія при натисканні на кнопку
	private: System::Void btnAdd_Click(System::Object^ sender, System::EventArgs^ e) {

		// 1. Перевірка, чи не порожні поля 
		if (this->txtProc->Text == "" || this->txtHDD->Text == "" || this->txtRAM->Text == "") {
			MessageBox::Show("Помилка: Заповніть усі поля!", "Error", MessageBoxButtons::OK);
			return;
		}

		try {
			// 2. З'єднання з MySQL 
			String^ connString = "Driver={MySQL ODBC 9.6 Unicode Driver};Server=localhost;Database=AccessoriesDB;User=root;Password=shepa2005;";

			OdbcConnection^ connection = gcnew OdbcConnection(connString);
			connection->Open();

			// 3. Команда для запису даних у таблицю 
			String^ sql = "INSERT INTO ComputerParts (processor_type, hdd_volume, ram_size, power_supply) VALUES ('"
				+ this->txtProc->Text + "', '"
				+ this->txtHDD->Text + "', '"
				+ this->txtRAM->Text + "', '"
				+ this->txtPower->Text + "')";

			OdbcCommand^ cmd = gcnew OdbcCommand(sql, connection);
			cmd->ExecuteNonQuery();

			MessageBox::Show("Запис успішно додано!", "OK", MessageBoxButtons::OK);
			connection->Close();
		}
		catch (Exception^ ex) {
			
			MessageBox::Show("Помилка БД: " + ex->Message, "Error", MessageBoxButtons::OK);
		}
	}
	};
}