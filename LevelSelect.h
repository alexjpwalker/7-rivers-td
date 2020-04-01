#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace RiversTD
{
	public __gc class LevelSelect : public System::Windows::Forms::Form
	{
	public: 
		LevelSelect(int _i, int width, int height)
		{
			InitializeComponent();
			LevelIndex = _i;
			br = new SolidBrush(Color::LightGreen);
			tv = new char __gc[Maps::MW+8,Maps::MH+8];
			bmp = new Bitmap(width, height);
			hb = new HatchBrush(HatchStyle::LargeConfetti, Color::DimGray, Color::Black);
			hb2 = new HatchBrush(HatchStyle::SmallConfetti, Color::DarkRed, Color::Black);
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
	public:
		int LevelIndex;
	private:
		SolidBrush * br;
		HatchBrush * hb, *hb2;
		char tv __gc[,];
		Bitmap * bmp;
	private: System::Windows::Forms::PictureBox *  LevelPreview;
	private: System::Windows::Forms::Button *  button1;
	private: System::Windows::Forms::Label *  label1;
	private: System::Windows::Forms::Button *  button2;
	private: System::Windows::Forms::ImageList *  imageList1;
	private: System::Windows::Forms::Button *  button3;

	private: System::ComponentModel::IContainer *  components;

	private:
		void InitializeComponent(void)
		{
			this->components = new System::ComponentModel::Container();
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(RiversTD::LevelSelect));
			this->LevelPreview = new System::Windows::Forms::PictureBox();
			this->button1 = new System::Windows::Forms::Button();
			this->label1 = new System::Windows::Forms::Label();
			this->button2 = new System::Windows::Forms::Button();
			this->imageList1 = new System::Windows::Forms::ImageList(this->components);
			this->button3 = new System::Windows::Forms::Button();
			this->SuspendLayout();
			// 
			// LevelPreview
			// 
			this->LevelPreview->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->LevelPreview->Cursor = System::Windows::Forms::Cursors::Hand;
			this->LevelPreview->Location = System::Drawing::Point(80, 24);
			this->LevelPreview->Name = S"LevelPreview";
			this->LevelPreview->Size = System::Drawing::Size(560, 432);
			this->LevelPreview->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->LevelPreview->TabIndex = 0;
			this->LevelPreview->TabStop = false;
			this->LevelPreview->Click += new System::EventHandler(this, LevelPreview_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(304, 488);
			this->button1->Name = S"button1";
			this->button1->Size = System::Drawing::Size(104, 23);
			this->button1->TabIndex = 6;
			this->button1->Text = S"Custom Level...";
			this->button1->Click += new System::EventHandler(this, button1_Click);
			// 
			// label1
			// 
			this->label1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->label1->Font = new System::Drawing::Font(S"Copperplate Gothic Bold", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->label1->Location = System::Drawing::Point(80, 456);
			this->label1->Name = S"label1";
			this->label1->Size = System::Drawing::Size(560, 23);
			this->label1->TabIndex = 7;
			this->label1->Text = S"Level 1: 20 Waves";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// button2
			// 
			this->button2->Enabled = false;
			this->button2->ImageIndex = 1;
			this->button2->ImageList = this->imageList1;
			this->button2->Location = System::Drawing::Point(32, 216);
			this->button2->Name = S"button2";
			this->button2->Size = System::Drawing::Size(32, 40);
			this->button2->TabIndex = 8;
			this->button2->Click += new System::EventHandler(this, button2_Click);
			// 
			// imageList1
			// 
			this->imageList1->ImageSize = System::Drawing::Size(16, 23);
			this->imageList1->ImageStream = (__try_cast<System::Windows::Forms::ImageListStreamer *  >(resources->GetObject(S"imageList1.ImageStream")));
			this->imageList1->TransparentColor = System::Drawing::Color::White;
			// 
			// button3
			// 
			this->button3->ImageIndex = 0;
			this->button3->ImageList = this->imageList1;
			this->button3->Location = System::Drawing::Point(656, 216);
			this->button3->Name = S"button3";
			this->button3->Size = System::Drawing::Size(32, 40);
			this->button3->TabIndex = 9;
			this->button3->Click += new System::EventHandler(this, button3_Click);
			// 
			// LevelSelect
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(722, 520);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->LevelPreview);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = S"LevelSelect";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = S"Level Select";
			this->Load += new System::EventHandler(this, LevelSelect_Load);
			this->ResumeLayout(false);

		}		
private: void DrawGrid(Graphics * g)
			 {
				 Pen * p = new Pen(Color::Black, 1.5);
				 for (int i = 0; i <= AS; i += GS)
				 {
					 g->DrawLine(p, Point(i, 0), Point(i, AS));
					 g->DrawLine(p, Point(0, i), Point(AS, i));
				 } 
			 }
private: void DrawTopLayer(Graphics * g, char _tv, int i, int j)
	{
		Point pts[] = new Point[4];
		LinearGradientBrush * lg;
		Color fec; // Fading effect color
		if (_tv <= 6)
			fec = Color::Lime;
		else
			fec = Color::DarkRed;
		switch (_tv) // For all tiles inherited from enemy path
		{
		case 1: case 2:
			break;
		case 3: case 7:
			pts[0] = Point(i*GS,(j+1-FD)*GS); // [0] is the TRANSPARENT end
			pts[1] = Point(i*GS,j*GS);
			lg = new LinearGradientBrush(pts[0], pts[1], Color::FromArgb(0, fec), Color::FromArgb(200, fec));
			g->FillRectangle(lg, i*GS, j*GS, GS, GS*GSM);
			break;
		case 4: case 8:
			pts[0] = Point((i+1-FD)*GS,j*GS);
			pts[1] = Point(i*GS,j*GS);
			lg = new LinearGradientBrush(pts[0], pts[1], Color::FromArgb(0, fec), Color::FromArgb(200, fec));
			g->FillRectangle(lg, i*GS, j*GS, GS*GSM, GS);
			break;
		case 5: case 9:
			pts[0] = Point(i*GS,(j+FD)*GS);
			pts[1] = Point(i*GS,(j+1)*GS);
			lg = new LinearGradientBrush(pts[0], pts[1], Color::FromArgb(0, fec), Color::FromArgb(200, fec));
			g->FillRectangle(lg, i*GS, (j+FD)*GS, GS, GS*GSM);
			break;
		case 6: case 10:
			pts[0] = Point((i+FD)*GS,j*GS);
			pts[1] = Point(i*GS+GS,j*GS);
			lg = new LinearGradientBrush(pts[0], pts[1], Color::FromArgb(0, fec), Color::FromArgb(200, fec));
			g->FillRectangle(lg, (i+FD)*GS, j*GS, GS*GSM, GS);
			break;
		}
	}
private: void DrawTiles(Graphics * g, char m __gc[])
{
	Point pts[] = new Point[4];
	LinearGradientBrush * lg;
	tv = Maps::ToGrid(m);
	for (int i = 0; i < Maps::MW; i++)
	{
		for (int j = 0; j < Maps::MH; j++)
		{
			switch (tv[i,j])
			{
			case 0:
			case -8: // Turret spot -8
				g->FillRectangle(br, i*GS, j*GS, GS, GS);
				break;
			case CHARRED: // Charred
				g->FillRectangle(hb, i*GS+3, j*GS+3, GS-6, GS-6);
				g->FillEllipse(hb2, i*GS+1, j*GS+1, GS-2, GS-2);
				break;
			case 1: case 2: case 3: case 4: case 5: case 6: // SU 3 - SL 4 - SD 5 - SR 6
			case 7: case 8: case 9: case 10: // FU 7 - FL 8 - FD 9 - FR 10
				pts[0] = Point(i*GS,j*GS);
				pts[1] = Point(i*GS+GS,j*GS+GS);
				lg = new LinearGradientBrush(pts[0], pts[1], Color::LightGray, Color::DarkGray);
				g->FillRectangle(lg, i*GS, j*GS, GS, GS);
				DrawTopLayer(g, tv[i,j], i, j);
				break;
			case 11: // TODO: River tiles (cases through to about 18 may be needed)
				break;
			default:
				if (MessageBox::Show(tv[i,j].ToString(), "Undefined tile") == DialogResult::OK)
					break;
			}
		}
	}
	DrawGrid(g);
}
	private: void PreviewMap(int mi)
			 {
				 Graphics * g = Graphics::FromImage(bmp);
				 switch (mi)
				 {
				 case 1:
					 DrawTiles(g, Maps::map1);
					 button2->Enabled = false;
					 label1->Text = "Level 1: 20 Waves";
					 break;
				 case 2:
					 DrawTiles(g, Maps::map2);
					 button2->Enabled = true;
					 label1->Text = "Level 2: 30 Waves";
					 break;
				 case 3:
					 DrawTiles(g, Maps::map3);
					 label1->Text = "Level 3";
					 break;
				 case 4:
					 DrawTiles(g, Maps::map4);
					 label1->Text = "Level 4";
					 break;
				 case 5:
					 DrawTiles(g, Maps::map5);
					 button3->Enabled = true;
					 label1->Text = "Level 5";
					 break;
				 case 6:
					 DrawTiles(g, Maps::map6);
					 button3->Enabled = false;
					 label1->Text = "Level 6";
					 break;
				 default:
					 return;
				 }
				 LevelPreview->Image = dynamic_cast<Image*>(bmp);
			 }
	private: System::Void LevelSelect_Load(System::Object *  sender, System::EventArgs *  e)
			 {
				 Graphics * g = Graphics::FromImage(bmp);
				 DrawTiles(g, Maps::map1);
				 LevelPreview->Image = dynamic_cast<Image*>(bmp);
			 }

private: System::Void LevelPreview_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 this->DialogResult = DialogResult::OK;
		 }

private: System::Void button1_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 LevelIndex = 0;
			 this->DialogResult = DialogResult::OK;
		 }

private: System::Void button3_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 LevelIndex++;
			 PreviewMap(LevelIndex);
		 }

private: System::Void button2_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 LevelIndex--;
			 PreviewMap(LevelIndex);
		 }

};
}