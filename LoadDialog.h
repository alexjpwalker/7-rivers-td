#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace RiversTD
{
	public __gc class LoadDialog : public System::Windows::Forms::Form
	{
	public: 
		LoadDialog(void)
		{
			InitializeComponent();
		}
        
	protected: 
		void Dispose(Boolean disposing)
		{
			if (disposing && components)
			{
				components->Dispose();
			}
			__super::Dispose(disposing);
		}
	public: System::Windows::Forms::ProgressBar *  LoadMeter;
	public: System::Windows::Forms::Button *  CancelButton;
	public: System::Windows::Forms::TextBox *  Details;
	public: System::Windows::Forms::Timer *  timer1;

	private: System::ComponentModel::IContainer *  components;

	private:


		void InitializeComponent(void)
		{
			this->components = new System::ComponentModel::Container();
			this->LoadMeter = new System::Windows::Forms::ProgressBar();
			this->CancelButton = new System::Windows::Forms::Button();
			this->Details = new System::Windows::Forms::TextBox();
			this->timer1 = new System::Windows::Forms::Timer(this->components);
			this->SuspendLayout();
			// 
			// LoadMeter
			// 
			this->LoadMeter->Location = System::Drawing::Point(64, 64);
			this->LoadMeter->Name = S"LoadMeter";
			this->LoadMeter->Size = System::Drawing::Size(176, 23);
			this->LoadMeter->TabIndex = 0;
			// 
			// CancelButton
			// 
			this->CancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->CancelButton->Enabled = false;
			this->CancelButton->Location = System::Drawing::Point(104, 104);
			this->CancelButton->Name = S"CancelButton";
			this->CancelButton->Size = System::Drawing::Size(88, 23);
			this->CancelButton->TabIndex = 1;
			this->CancelButton->Text = S"Cancel";
			this->CancelButton->Click += new System::EventHandler(this, CancelButton_Click);
			// 
			// Details
			// 
			this->Details->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->Details->Location = System::Drawing::Point(64, 24);
			this->Details->Name = S"Details";
			this->Details->ReadOnly = true;
			this->Details->Size = System::Drawing::Size(176, 22);
			this->Details->TabIndex = 2;
			this->Details->TabStop = false;
			this->Details->Text = S"";
			this->Details->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// timer1
			// 
			this->timer1->Interval = 1;
			// 
			// LoadDialog
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(292, 144);
			this->Controls->Add(this->Details);
			this->Controls->Add(this->CancelButton);
			this->Controls->Add(this->LoadMeter);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = S"LoadDialog";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = S"Loading, please wait...";
			this->ResumeLayout(false);

		}		
	private: System::Void CancelButton_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 this->Close();
			 }

};
}