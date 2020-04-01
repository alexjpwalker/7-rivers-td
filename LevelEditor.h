#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Drawing::Drawing2D;

namespace RiversTD
{
	public __gc class LevelEditor : public System::Windows::Forms::Form
	{
	public: 
		LevelEditor(void)
		{
			InitializeComponent();
			tpi = new Bitmap(TilePanel->Width, TilePanel->Height);
			bmp = new Bitmap(TilePanel->Width, TilePanel->Height);
			area = new Bitmap(GameArea->Width, GameArea->Height);
			br = new SolidBrush(GameArea->BackColor);
			tv = new char __gc[Maps::MW+8, Maps::MH+8];
			Paths = new char __gc[MPC,MPL];
			for (int i = 0; i < MPC; i++)
			{
				for (int j = 0; j < MPL; j++)
					Paths[i,j] = -1;
			}
			Map = new char __gc[MLMAX];
			sf = new StringFormat();
			sf->Alignment = StringAlignment::Center;
			sf->LineAlignment = StringAlignment::Center;
			MD = false;
			obj = new Object();
			pea = new PaintEventArgs(TilePanel->CreateGraphics(), TilePanel->ClientRectangle);
			gpea = new PaintEventArgs(GameArea->CreateGraphics(), GameArea->ClientRectangle);
			hb = new HatchBrush(HatchStyle::LargeConfetti, Color::DimGray, Color::Black);
			hb2 = new HatchBrush(HatchStyle::SmallConfetti, Color::DarkRed, Color::Black);
			ti = 0; pap = 0; pc = 0;
			WaveFile = String::Empty;
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
	private:
		Bitmap * tpi, * area, * bmp;
		SolidBrush * br;
		char tv __gc[,];
		char Map __gc[];
		char Paths __gc[,];
		int ti, sx, sy, pap, pc, px, py, cp, mpei; // tile index - x,y - path add phase - path count - path point x,y - current point - path editing index
		int seq; // sequence length
		bool MD; // mouse down
		StringFormat * sf;
		Object * obj;
		Waves * waves;
		PaintEventArgs * pea, * gpea;
		HatchBrush * hb, *hb2;
		String * WaveFile;

	private: System::Windows::Forms::Panel *  GameArea;
	private: System::Windows::Forms::Panel *  TilePanel;
	private: System::Windows::Forms::SaveFileDialog *  SaveLevel;
	private: System::Windows::Forms::OpenFileDialog *  LoadLevel;
	private: System::Windows::Forms::Button *  AddPath;
	private: System::Windows::Forms::MainMenu *  mainMenu1;
	private: System::Windows::Forms::MenuItem *  mFile;
	private: System::Windows::Forms::MenuItem *  NewMap;
	private: System::Windows::Forms::MenuItem *  mOpen;
	private: System::Windows::Forms::MenuItem *  SaveMap;
	private: System::Windows::Forms::MenuItem *  SaveAs;
	private: System::Windows::Forms::MenuItem *  Exit;
	private: System::Windows::Forms::MenuItem *  mEdit;
	private: System::Windows::Forms::MenuItem *  mAddPath;
	private: System::Windows::Forms::MenuItem *  menuItem9;
	private: System::Windows::Forms::MenuItem *  FillArea;
	private: System::Windows::Forms::MenuItem *  OpenMap;
	private: System::Windows::Forms::MenuItem *  OpenWaves;
	private: System::Windows::Forms::Label *  WaveHeader;
	private: System::Windows::Forms::OpenFileDialog *  LoadWaves;
	private: System::Windows::Forms::StatusBar *  Status;
	private: System::Windows::Forms::Label *  t_path;
	private: System::Windows::Forms::Label *  PathHeader;
	private: System::Windows::Forms::NumericUpDown *  Path;
	private: System::Windows::Forms::MenuItem *  SaveMapOnly;

	System::ComponentModel::Container* components;

		void InitializeComponent(void)
		{
			this->GameArea = new System::Windows::Forms::Panel();
			this->TilePanel = new System::Windows::Forms::Panel();
			this->SaveLevel = new System::Windows::Forms::SaveFileDialog();
			this->LoadLevel = new System::Windows::Forms::OpenFileDialog();
			this->AddPath = new System::Windows::Forms::Button();
			this->mainMenu1 = new System::Windows::Forms::MainMenu();
			this->mFile = new System::Windows::Forms::MenuItem();
			this->NewMap = new System::Windows::Forms::MenuItem();
			this->mOpen = new System::Windows::Forms::MenuItem();
			this->OpenMap = new System::Windows::Forms::MenuItem();
			this->OpenWaves = new System::Windows::Forms::MenuItem();
			this->SaveMap = new System::Windows::Forms::MenuItem();
			this->SaveAs = new System::Windows::Forms::MenuItem();
			this->Exit = new System::Windows::Forms::MenuItem();
			this->mEdit = new System::Windows::Forms::MenuItem();
			this->mAddPath = new System::Windows::Forms::MenuItem();
			this->menuItem9 = new System::Windows::Forms::MenuItem();
			this->FillArea = new System::Windows::Forms::MenuItem();
			this->WaveHeader = new System::Windows::Forms::Label();
			this->LoadWaves = new System::Windows::Forms::OpenFileDialog();
			this->Status = new System::Windows::Forms::StatusBar();
			this->Path = new System::Windows::Forms::NumericUpDown();
			this->t_path = new System::Windows::Forms::Label();
			this->PathHeader = new System::Windows::Forms::Label();
			this->SaveMapOnly = new System::Windows::Forms::MenuItem();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->Path))->BeginInit();
			this->SuspendLayout();
			// 
			// GameArea
			// 
			this->GameArea->BackColor = System::Drawing::Color::LightGreen;
			this->GameArea->Location = System::Drawing::Point(0, 0);
			this->GameArea->Name = S"GameArea";
			this->GameArea->Size = System::Drawing::Size(736, 600);
			this->GameArea->TabIndex = 2;
			this->GameArea->MouseUp += new System::Windows::Forms::MouseEventHandler(this, GameArea_MouseUp);
			this->GameArea->Paint += new System::Windows::Forms::PaintEventHandler(this, GameArea_Paint);
			this->GameArea->MouseMove += new System::Windows::Forms::MouseEventHandler(this, GameArea_MouseMove);
			this->GameArea->MouseDown += new System::Windows::Forms::MouseEventHandler(this, GameArea_MouseDown);
			// 
			// TilePanel
			// 
			this->TilePanel->Location = System::Drawing::Point(768, 240);
			this->TilePanel->Name = S"TilePanel";
			this->TilePanel->Size = System::Drawing::Size(97, 129);
			this->TilePanel->TabIndex = 3;
			this->TilePanel->Paint += new System::Windows::Forms::PaintEventHandler(this, TilePanel_Paint);
			this->TilePanel->MouseDown += new System::Windows::Forms::MouseEventHandler(this, TilePanel_MouseDown);
			// 
			// SaveLevel
			// 
			this->SaveLevel->Filter = S"Level File (*.txt)|*.txt|All Files (*.*)|*.*";
			// 
			// LoadLevel
			// 
			this->LoadLevel->Filter = S"Level File (*.txt)|*.txt|All Files (*.*)|*.*";
			// 
			// AddPath
			// 
			this->AddPath->Location = System::Drawing::Point(776, 392);
			this->AddPath->Name = S"AddPath";
			this->AddPath->TabIndex = 4;
			this->AddPath->Text = S"Add path";
			this->AddPath->Click += new System::EventHandler(this, mAddPath_Click);
			// 
			// mainMenu1
			// 
			System::Windows::Forms::MenuItem* __mcTemp__1[] = new System::Windows::Forms::MenuItem*[2];
			__mcTemp__1[0] = this->mFile;
			__mcTemp__1[1] = this->mEdit;
			this->mainMenu1->MenuItems->AddRange(__mcTemp__1);
			// 
			// mFile
			// 
			this->mFile->Index = 0;
			System::Windows::Forms::MenuItem* __mcTemp__2[] = new System::Windows::Forms::MenuItem*[6];
			__mcTemp__2[0] = this->NewMap;
			__mcTemp__2[1] = this->mOpen;
			__mcTemp__2[2] = this->SaveMap;
			__mcTemp__2[3] = this->SaveMapOnly;
			__mcTemp__2[4] = this->SaveAs;
			__mcTemp__2[5] = this->Exit;
			this->mFile->MenuItems->AddRange(__mcTemp__2);
			this->mFile->Text = S"&File";
			// 
			// NewMap
			// 
			this->NewMap->Index = 0;
			this->NewMap->Shortcut = System::Windows::Forms::Shortcut::CtrlN;
			this->NewMap->Text = S"&New";
			// 
			// mOpen
			// 
			this->mOpen->Index = 1;
			System::Windows::Forms::MenuItem* __mcTemp__3[] = new System::Windows::Forms::MenuItem*[2];
			__mcTemp__3[0] = this->OpenMap;
			__mcTemp__3[1] = this->OpenWaves;
			this->mOpen->MenuItems->AddRange(__mcTemp__3);
			this->mOpen->Shortcut = System::Windows::Forms::Shortcut::CtrlO;
			this->mOpen->Text = S"&Open";
			// 
			// OpenMap
			// 
			this->OpenMap->Index = 0;
			this->OpenMap->Text = S"&Map...";
			// 
			// OpenWaves
			// 
			this->OpenWaves->Index = 1;
			this->OpenWaves->Text = S"&Waves...";
			this->OpenWaves->Click += new System::EventHandler(this, OpenWaves_Click);
			// 
			// SaveMap
			// 
			this->SaveMap->Index = 2;
			this->SaveMap->Shortcut = System::Windows::Forms::Shortcut::CtrlS;
			this->SaveMap->Text = S"&Save";
			this->SaveMap->Click += new System::EventHandler(this, SaveMap_Click);
			// 
			// SaveAs
			// 
			this->SaveAs->Index = 4;
			this->SaveAs->Shortcut = System::Windows::Forms::Shortcut::CtrlShiftS;
			this->SaveAs->Text = S"&Save As...";
			// 
			// Exit
			// 
			this->Exit->Index = 5;
			this->Exit->Shortcut = System::Windows::Forms::Shortcut::AltF4;
			this->Exit->Text = S"E&xit";
			// 
			// mEdit
			// 
			this->mEdit->Index = 1;
			System::Windows::Forms::MenuItem* __mcTemp__4[] = new System::Windows::Forms::MenuItem*[3];
			__mcTemp__4[0] = this->mAddPath;
			__mcTemp__4[1] = this->menuItem9;
			__mcTemp__4[2] = this->FillArea;
			this->mEdit->MenuItems->AddRange(__mcTemp__4);
			this->mEdit->Text = S"&Edit";
			// 
			// mAddPath
			// 
			this->mAddPath->Index = 0;
			this->mAddPath->Text = S"Add &Path";
			this->mAddPath->Click += new System::EventHandler(this, mAddPath_Click);
			// 
			// menuItem9
			// 
			this->menuItem9->Index = 1;
			this->menuItem9->Text = S"-";
			// 
			// FillArea
			// 
			this->FillArea->Index = 2;
			this->FillArea->Text = S"&Fill Area";
			// 
			// WaveHeader
			// 
			this->WaveHeader->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->WaveHeader->Location = System::Drawing::Point(760, 48);
			this->WaveHeader->Name = S"WaveHeader";
			this->WaveHeader->Size = System::Drawing::Size(112, 23);
			this->WaveHeader->TabIndex = 5;
			this->WaveHeader->Text = S"Waves: 0";
			// 
			// LoadWaves
			// 
			this->LoadWaves->Filter = S"WaveSequence File (*.txt)|*.txt|All Files (*.*)|*.*";
			// 
			// Status
			// 
			this->Status->Location = System::Drawing::Point(0, 595);
			this->Status->Name = S"Status";
			this->Status->Size = System::Drawing::Size(888, 22);
			this->Status->TabIndex = 6;
			this->Status->Text = S"Ready";
			// 
			// Path
			// 
			this->Path->Location = System::Drawing::Point(808, 432);
			System::Int32 __mcTemp__5[] = new System::Int32[4];
			__mcTemp__5[0] = 9;
			__mcTemp__5[1] = 0;
			__mcTemp__5[2] = 0;
			__mcTemp__5[3] = 0;
			this->Path->Maximum = System::Decimal(__mcTemp__5);
			this->Path->Name = S"Path";
			this->Path->Size = System::Drawing::Size(40, 20);
			this->Path->TabIndex = 7;
			// 
			// t_path
			// 
			this->t_path->Location = System::Drawing::Point(768, 432);
			this->t_path->Name = S"t_path";
			this->t_path->Size = System::Drawing::Size(40, 16);
			this->t_path->TabIndex = 8;
			this->t_path->Text = S"Path";
			this->t_path->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// PathHeader
			// 
			this->PathHeader->Font = new System::Drawing::Font(S"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->PathHeader->Location = System::Drawing::Point(760, 80);
			this->PathHeader->Name = S"PathHeader";
			this->PathHeader->Size = System::Drawing::Size(112, 23);
			this->PathHeader->TabIndex = 9;
			this->PathHeader->Text = S"Paths: 0";
			// 
			// SaveMapOnly
			// 
			this->SaveMapOnly->Index = 3;
			this->SaveMapOnly->Text = S"Save &Map...";
			this->SaveMapOnly->Click += new System::EventHandler(this, SaveMapOnly_Click);
			// 
			// LevelEditor
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->ClientSize = System::Drawing::Size(888, 617);
			this->Controls->Add(this->PathHeader);
			this->Controls->Add(this->t_path);
			this->Controls->Add(this->Path);
			this->Controls->Add(this->Status);
			this->Controls->Add(this->WaveHeader);
			this->Controls->Add(this->AddPath);
			this->Controls->Add(this->TilePanel);
			this->Controls->Add(this->GameArea);
			this->Menu = this->mainMenu1;
			this->Name = S"LevelEditor";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = S"7 Rivers TD Level Editor";
			this->Load += new System::EventHandler(this, LevelEditor_Load);
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->Path))->EndInit();
			this->ResumeLayout(false);

		}		
private: void DrawGrid(Graphics * g)
			 {
				 for (int i = 0; i <= AS; i += GS)
				 {
					 g->DrawLine(Pens::Black, Point(i, 0), Point(i, AS));
					 g->DrawLine(Pens::Black, Point(0, i), Point(AS, i));
				 } 
			 }
private: void DrawTopLayer(Graphics * g, char _tv, int i, int j)
	{
		SolidBrush * br = new SolidBrush(GameArea->BackColor);
		Point pts[] = new Point[4];
		LinearGradientBrush * lg;
		Color fec; // Fading effect color
		if (_tv <= 6)
			fec = Color::Lime;
		else
			fec = Color::DarkRed;
		switch (_tv) // For all tiles inherited from enemy path
		{
		case 1:
			break;
		case 2: // Path point - invisible in main app
			br->Color = Color::DimGray;
			g->FillRectangle(br, i*GS+4, j*GS+GS/2-2, GS-8, 4);
			g->FillRectangle(br, i*GS+GS/2-2, j*GS+4, 4, GS-8);
			break;
		case 3: case 7:
			pts[0] = Point(i*GS,(j+1-FDL)*GS); // [0] is the TRANSPARENT end
			pts[1] = Point(i*GS,j*GS);
			lg = new LinearGradientBrush(pts[0], pts[1], Color::FromArgb(0, fec), Color::FromArgb(200, fec));
			g->FillRectangle(lg, i*GS, j*GS, GS, GS*GSM);
			break;
		case 4: case 8:
			pts[0] = Point((i+1-FDL)*GS,j*GS);
			pts[1] = Point(i*GS,j*GS);
			lg = new LinearGradientBrush(pts[0], pts[1], Color::FromArgb(0, fec), Color::FromArgb(200, fec));
			g->FillRectangle(lg, i*GS, j*GS, GS*GSM, GS);
			break;
		case 5: case 9:
			pts[0] = Point(i*GS,(j+FDL)*GS);
			pts[1] = Point(i*GS,(j+1)*GS);
			lg = new LinearGradientBrush(pts[0], pts[1], Color::FromArgb(0, fec), Color::FromArgb(200, fec));
			g->FillRectangle(lg, i*GS, (j+FD)*GS, GS, GS*GSM);
			break;
		case 6: case 10:
			pts[0] = Point((i+FDL)*GS,j*GS);
			pts[1] = Point(i*GS+GS,j*GS);
			lg = new LinearGradientBrush(pts[0], pts[1], Color::FromArgb(0, fec), Color::FromArgb(200, fec));
			g->FillRectangle(lg, (i+FD)*GS, j*GS, GS*GSM, GS);
			break;
		}
	}
private: void DrawTiles(Graphics * g)
{
	br->Color = GameArea->BackColor;
	Point pts[] = new Point[4];
	LinearGradientBrush * lg;
	Color fec; // Fading effect color
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
			case -10: // Charred
				g->FillRectangle(br, i*GS, j*GS, GS, GS);
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
				break;
			}
		}
	} 
}
private: System::Void TilePanel_Paint(System::Object *  sender, System::Windows::Forms::PaintEventArgs *  e)
		{
			Graphics * g = Graphics::FromImage(bmp);
			g->DrawImageUnscaled(tpi, 0, 0);
			if (ti != -1)
				g->DrawRectangle(Pens::Red, sx*GS+1, sy*GS+1, GS-2, GS-2);
			e->Graphics->DrawImageUnscaled(bmp, 0, 0);
		}
private: System::Void GameArea_Paint(System::Object *  sender, System::Windows::Forms::PaintEventArgs *  e)
		{
			e->Graphics->DrawImageUnscaled(area, 0, 0);
		}
private: System::Void LevelEditor_Load(System::Object *  sender, System::EventArgs *  e)
	{
		LinearGradientBrush * lg = new LinearGradientBrush(Point(GS,0), Point(GS*2,GS), Color::LightGray, Color::DarkGray);
		Color fec; // Fading effect color
		Graphics * g = Graphics::FromImage(tpi);
		g->FillRectangle(br, 0, 0, GS, GS);
		g->FillRectangle(lg, GS, 0, GS, GS);
		lg = new LinearGradientBrush(Point(GS*2,0), Point(GS*3,GS), Color::LightGray, Color::DarkGray);
		g->FillRectangle(lg, GS*2, 0, GS, GS);
		for (int i = 0; i < 3; i++)
		{
			for (int j = 1; j < 4; j++)
			{
				lg = new LinearGradientBrush(Point(GS*i,GS*j), Point(GS*(i+1),GS*(j+1)), Color::LightGray, Color::DarkGray);
				g->FillRectangle(lg, GS*i, GS*j, GS, GS);
			}
		}
		g->FillRectangle(Brushes::Black, GS*2, GS*3, GS, GS);
		g->FillRectangle(hb, 2*GS+3, 3*GS+3, GS-6, GS-6);
		g->FillEllipse(hb2, 2*GS+1, 3*GS+1, GS-2, GS-2);
		for (int i = 0; i < 4; i++)
			g->DrawLine(Pens::Black, GS*i, 0, GS*i, GS*4);
		for (int i = 0; i < 5; i++)
			g->DrawLine(Pens::Black, 0, GS*i, GS*3, GS*i);
		int _tv = -1;
		Point pts[] = new Point[4];
		for (int j = 0; j < 4; j++)
		{
			for (int i = 0; i < 3; i++)
			{
				_tv++;
				if (_tv <= 6)
					fec = Color::Lime;
				else
					fec = Color::DarkRed;
				switch (_tv) // For all tiles inherited from enemy path
				{
				case 2:
					g->FillRectangle(Brushes::DimGray, i*GS+4, j*GS+GS/2-2, GS-8, 4);
					g->FillRectangle(Brushes::DimGray, i*GS+GS/2-2, j*GS+4, 4, GS-8);
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
				default:
					break;
				}
			}
		}
		g = Graphics::FromImage(area);
		DrawTiles(g);
		DrawGrid(g);
	}
private: System::Void GameArea_MouseDown(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
		 {
			 if (pap == 0)
			 {
				 MD = true;
				 GameArea_MouseMove(obj, e);
			 }
			 else if (pap == 1)
			 {
				 px = e->X/GS;
				 py = e->Y/GS;
				 Paths[(int)Path->Value, cp] = px;
				 Paths[(int)Path->Value, cp+1] = py;
				 cp += 2;
				 Status->Text = String::Concat("Select path point ", (cp-2).ToString());
				 RectangleF rectf = RectangleF(px*GS, py*GS, GS, GS);
				 GameArea->CreateGraphics()->DrawRectangle(Pens::Red, px*GS, py*GS, GS, GS);
				 GameArea->CreateGraphics()->DrawString("S", this->Font, Brushes::Red, rectf, sf);
				 pap = 2;
			 }
			 else if (pap == 2)
			 {
				 if (cp > MPL - 7)
				 {
					 pap = 0;
					 Paths[(int)Path->Value, cp] = e->X/GS;
					 Paths[(int)Path->Value, cp+1] = e->Y/GS;
					 Paths[(int)Path->Value, cp+2] = -1;
					 Paths[(int)Path->Value, 0] = cp+3;
					 Status->Text = "Maximum path length reached";
					 Path->Enabled = true;
					 pc++;
					 PathHeader->Text = String::Concat("Paths: ", pc.ToString());
					 return;
				 }
				 if (e->X/GS == px && e->Y/GS < py)
					 Paths[(int)Path->Value, cp] = 1;
				 else if (e->X/GS < px && e->Y/GS == py)
					 Paths[(int)Path->Value, cp] = 2;
				 else if (e->X/GS == px && e->Y/GS > py)
					 Paths[(int)Path->Value, cp] = 3;
				 else if (e->X/GS > px && e->Y/GS == py)
					 Paths[(int)Path->Value, cp] = 4;
				 else // Either path point is the same as last point, or it is relatively diagonal
					 return;
				 px = e->X/GS;
				 py = e->Y/GS;
				 GameArea->CreateGraphics()->DrawRectangle(Pens::Red, px*GS, py*GS, GS, GS);
				 RectangleF rectf = RectangleF(px*GS, py*GS, GS, GS);
				 GameArea->CreateGraphics()->DrawString((cp-2).ToString(), this->Font, Brushes::Red, rectf, sf);
				 cp++;
				 if (e->Button == MouseButtons::Left)
				 {
					 Status->Text = String::Concat("Select path point ", (cp-2).ToString());
					 return;
				 }
				 else
				 {
					 Paths[(int)Path->Value, cp] = e->X/GS;
					 Paths[(int)Path->Value, cp+1] = e->Y/GS;
					 Paths[(int)Path->Value, cp+2] = -1;
					 Paths[(int)Path->Value, 0] = cp+3;
					 Status->Text = "Ready";
					 Path->Enabled = true;
					 pap = 0;
					 pc++;
					 PathHeader->Text = String::Concat("Paths: ", pc.ToString());
				 }
			 }
		 }

private: System::Void GameArea_MouseUp(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
		 {
			 MD = false;
		 }

private: System::Void GameArea_MouseMove(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
		 {
			 Graphics * g;
			 if (!MD)
				 return;
			 if (ti == tv[e->X/GS,e->Y/GS])
				 return; // Not much point changing a tile value if it's already that value.
			 tv[e->X/GS,e->Y/GS] = ti;
			 Map[e->Y/GS*Maps::MW + e->X/GS] = ti;
			 g = Graphics::FromImage(area);
			 DrawTiles(g);
			 DrawGrid(g);
			 GameArea_Paint(obj, gpea);
		 }

private: System::Void TilePanel_MouseDown(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
		 {
			 if (pap != 0)
				 return;
			 sx = (int)e->X/GS;
			 sy = (int)e->Y/GS;
			 ti = sy*3 + sx;
			 if (ti > STD_TLIM)
			 {
				 switch (ti)
				 {
				 case 11: 
					 ti = CHARRED; 
					 break;
				 default:
					 ti = 0;
					 break;
				 }
			 }
			 TilePanel_Paint(obj, pea); // This function reads sx and sy. ti is read somewhere else.
		 }

private: System::Void OpenWaves_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 if (LoadWaves->ShowDialog() == DialogResult::OK)
			 {
				 waves = new Waves();
				 try
				 {
					 seq = waves->get_FileSequenceCount(LoadWaves->FileName, Map);
				 }
				 catch (Exception * ex)
				 {
					 MessageBox::Show(ex->Message, this->Text, MessageBoxButtons::OK, MessageBoxIcon::Error);
					 seq = 0;
				 }
				 WaveHeader->Text = String::Concat("Waves: ", seq.ToString());
				 if (seq > 0)
					 this->WaveFile = LoadWaves->FileName;
			 }
		 }

private: System::Void SaveMap_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 if (WaveFile->Length == 0)
			 {
				 MessageBox::Show("No wave sequence file defined for this level. Successfully load a WaveSequence file to save this level.", this->Text, MessageBoxButtons::OK, MessageBoxIcon::Warning);
				 return;
			 }
			 if (SaveLevel->ShowDialog() == DialogResult::OK)
			 {
				 FileStream * fs = new FileStream(SaveLevel->FileName, FileMode::Create, FileAccess::Write);
				 StreamWriter * sw = new StreamWriter(fs);
				 String * nameS = SaveLevel->FileName->Remove(0, SaveLevel->FileName->LastIndexOf("\\")+1);
				 String * nameL = SaveLevel->FileName;
				 if (nameS->EndsWith(".txt"))
				 {
					 nameS = nameS->Remove(nameS->Length - 4, 4);
					 nameL = nameL->Remove(nameL->Length - 4, 4);
				 }
				 nameS = String::Concat(nameS, "_Map");
				 nameL = String::Concat(nameL, "_Map.txt");
				 sw->Write(nameS);
				 sw->Write(",");
				 nameS = WaveFile->Remove(0, WaveFile->LastIndexOf("\\")+1);
				 if (nameS->EndsWith(".txt"))
					 nameS = nameS->Remove(nameS->Length - 4, 4);
				 sw->Write(nameS);
				 sw->Write(",");
				 sw->Write(".txt");
				 sw->Close();
				 fs = new FileStream(nameL, FileMode::Create, FileAccess::Write);
				 sw = new StreamWriter(fs);
				 StringWriter * stw = new StringWriter();
				 int ti = -1; // 1-dimensional tile index
				 for (int i = 0; i < Maps::MH; i++)
				 {
					 for (int j = 0; j < Maps::MW; j++)
					 {
						 ti++;
						 stw->Write(Map[ti].ToString());
						 if (Map[ti].ToString()->Length == 2)
							 stw->Write(",");
						 else
							 stw->Write(", ");
					 }
					 stw->WriteLine();
				 }
				 stw->WriteLine();
				 stw->Write(pc.ToString());
				 stw->WriteLine(",");
				 for (int i = 0; i < pc; i++)
				 {
					 if (Paths[i,0] == -1)
						 break; // Paths are stacked, so no higher order needs checking.
					 for (int j = 0; j < Paths->GetLength(1)-1; j++)
					 {
						 stw->Write(Paths[i,j].ToString());
						 if (Paths[i,j].ToString()->Length == 2)
							 stw->Write(",");
						 else
							 stw->Write(", ");
						 if (Paths[i,j] == -1)
							 break; // This actually continues to the next path.
					 }
				 }
				 String * s = stw->ToString();
				 sw->Write(s->TrimEnd(S","->ToCharArray()));
				 stw->Close();
				 sw->Close();
			 }
		 }

private: System::Void mAddPath_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 pap = 1;
			 cp = 1;
			 ti = -1;
			 if (Path->Value > 0)
			 {
				 while (Paths[(int)Path->Value-1, 0] == -1 && Path->Value > 0)
				 {
					 Path->Value--;
					 if (Path->Value == 0)
						 break;
				 }
			 }
			 for (int i = 0; i < MPL; i++)
				 Paths[(int)Path->Value, i] = -1;
			 Path->Enabled = false;
			 Status->Text = "Select start point";
		 }

private: System::Void SaveMapOnly_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 if (SaveLevel->ShowDialog() == DialogResult::OK)
			 {
				 FileStream * fs = new FileStream(SaveLevel->FileName, FileMode::Create, FileAccess::Write);
				 StreamWriter * sw = new StreamWriter(fs);
				 StringWriter * stw = new StringWriter();
				 int ti = -1; // 1-dimensional tile index
				 for (int i = 0; i < Maps::MH; i++)
				 {
					 for (int j = 0; j < Maps::MW; j++)
					 {
						 ti++;
						 stw->Write(Map[ti].ToString());
						 if (Map[ti].ToString()->Length == 2)
							 stw->Write(",");
						 else
							 stw->Write(", ");
					 }
					 stw->WriteLine();
				 }
				 stw->WriteLine();
				 String * s = stw->ToString();
				 sw->Write(s->TrimEnd(S","->ToCharArray()));
				 stw->Close();
				 sw->Close();
			 }
		 }

};
}