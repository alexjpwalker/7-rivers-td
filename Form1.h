#pragma once

#pragma warning (disable: 4244)

#include "defines.h"
#include "strings.h"
#include "enemies.h"
#include "maps.h"
#include "turrets.h"
#include "waves.h"
#include "LoadDialog.h"
#include "LevelSelect.h"
#include "LevelEditor.h"

namespace RiversTD
{
	using namespace System;
	using namespace System::Windows;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;
	using namespace System::IO;
	using namespace System::Text;

	public __gc class Form1 : public System::Windows::Forms::Form
	{	
	public:
		Form1(void)
		{
			InitializeComponent();
			HealthBox->Text = INIT_HP.ToString();
			HealthBox->BackColor = Color::FromArgb(72,224,50);
			t_hp->BackColor = Color::FromArgb(72,224,50);
			GoldBox->Text = INIT_GOLD.ToString();
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
		int mx, my, gx, gy, sx, sy, ti; // mouse x/y, game area mouse x/y, turret selection x/y, turret index
		int px, py, eci, tei, eei; // proposed turret x/y, enemy current index, tower examine index, enemy examine index
		int eMax, tMax, wave, next, wi, gold, hp; // next = time until next enemy; wi = wave index
		double lp; // load progress
		char tv __gc[,];
		char Map __gc[];
		static bool FreezeCP = false;
		bool draw, paused;
		Bitmap * tiles, * top, * info, * bmp, * cpb;
		Turret * ts __gc[];
		static Enemy * es __gc[];
		LoadDialog * ld;
		LevelSelect * lsd;
		LevelEditor * led;
		static Drawing::Font * pf = new Drawing::Font(S"Copperplate Gothic Bold", 12);
		static Drawing::Font * pfs = new Drawing::Font(S"Copperplate Gothic Light", 9.5);
		static Random * r = new Random();
		StringFormat * sf;
		Pen * p, * p1, * p2, * p3;
		Object * obj;
		PaintEventArgs * pea;
		EventArgs * ea;
		MouseEventArgs * mea;
		SolidBrush * br;
		HatchBrush * hb, *hb2;
		FileStream * fs;
		StreamReader * sr;
		Turret * t_temp;
		Wave * CurrentWave;
		Waves * waves;
		WaveSequence * Sequence;

	private: System::Windows::Forms::Label *  StartGame;
	private: System::Windows::Forms::Panel *  ControlPanel;
	private: System::Windows::Forms::Panel *  GameArea;
	private: System::Windows::Forms::Timer *  GameLoop;
	private: System::Windows::Forms::Panel *  InfoPanel;
	private: System::Windows::Forms::Label *  HealthBox;
	private: System::Windows::Forms::Label *  t_hp;
	private: System::Windows::Forms::Label *  t_g;
	private: System::Windows::Forms::Label *  GoldBox;
	private: System::Windows::Forms::Label *  t_sp;
	private: System::Windows::Forms::Label *  SpeedLabel;
	private: System::Windows::Forms::Label *  t_next;
	private: System::Windows::Forms::Label *  NextWave;
	private: System::Windows::Forms::Label *  ThisWave;
	private: System::Windows::Forms::Label *  t_cur;
	private: System::Windows::Forms::Label *  StartEditor;
	private: System::Windows::Forms::OpenFileDialog *  LoadLevel;
	private: System::Windows::Forms::OpenFileDialog *  LoadWaves;
	private: System::ComponentModel::IContainer *  components;
	private:

		void InitializeComponent(void)
		{
			this->components = new System::ComponentModel::Container();
			this->StartGame = new System::Windows::Forms::Label();
			this->ControlPanel = new System::Windows::Forms::Panel();
			this->GameArea = new System::Windows::Forms::Panel();
			this->StartEditor = new System::Windows::Forms::Label();
			this->GameLoop = new System::Windows::Forms::Timer(this->components);
			this->InfoPanel = new System::Windows::Forms::Panel();
			this->ThisWave = new System::Windows::Forms::Label();
			this->t_cur = new System::Windows::Forms::Label();
			this->NextWave = new System::Windows::Forms::Label();
			this->t_next = new System::Windows::Forms::Label();
			this->SpeedLabel = new System::Windows::Forms::Label();
			this->t_sp = new System::Windows::Forms::Label();
			this->GoldBox = new System::Windows::Forms::Label();
			this->t_g = new System::Windows::Forms::Label();
			this->t_hp = new System::Windows::Forms::Label();
			this->HealthBox = new System::Windows::Forms::Label();
			this->LoadLevel = new System::Windows::Forms::OpenFileDialog();
			this->LoadWaves = new System::Windows::Forms::OpenFileDialog();
			this->GameArea->SuspendLayout();
			this->InfoPanel->SuspendLayout();
			this->SuspendLayout();
			// 
			// StartGame
			// 
			this->StartGame->BackColor = System::Drawing::Color::OliveDrab;
			this->StartGame->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->StartGame->Location = System::Drawing::Point(328, 280);
			this->StartGame->Name = S"StartGame";
			this->StartGame->Size = System::Drawing::Size(80, 23);
			this->StartGame->TabIndex = 0;
			this->StartGame->Text = S"Start game";
			this->StartGame->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->StartGame->Click += new System::EventHandler(this, StartGame_Click);
			this->StartGame->MouseEnter += new System::EventHandler(this, StartGame_MouseEnter);
			this->StartGame->MouseLeave += new System::EventHandler(this, StartGame_MouseLeave);
			// 
			// ControlPanel
			// 
			this->ControlPanel->BackColor = System::Drawing::Color::DimGray;
			this->ControlPanel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->ControlPanel->Location = System::Drawing::Point(736, 64);
			this->ControlPanel->Name = S"ControlPanel";
			this->ControlPanel->Size = System::Drawing::Size(192, 656);
			this->ControlPanel->TabIndex = 1;
			this->ControlPanel->MouseUp += new System::Windows::Forms::MouseEventHandler(this, ControlPanel_MouseUp);
			this->ControlPanel->Paint += new System::Windows::Forms::PaintEventHandler(this, ControlPanel_Paint);
			this->ControlPanel->MouseMove += new System::Windows::Forms::MouseEventHandler(this, ControlPanel_MouseMove);
			this->ControlPanel->MouseLeave += new System::EventHandler(this, ControlPanel_MouseLeave);
			this->ControlPanel->MouseDown += new System::Windows::Forms::MouseEventHandler(this, ControlPanel_MouseDown);
			// 
			// GameArea
			// 
			this->GameArea->Controls->Add(this->StartEditor);
			this->GameArea->Controls->Add(this->StartGame);
			this->GameArea->Location = System::Drawing::Point(0, 64);
			this->GameArea->Name = S"GameArea";
			this->GameArea->Size = System::Drawing::Size(736, 600);
			this->GameArea->TabIndex = 2;
			this->GameArea->MouseUp += new System::Windows::Forms::MouseEventHandler(this, GameArea_MouseUp);
			this->GameArea->MouseMove += new System::Windows::Forms::MouseEventHandler(this, GameArea_MouseMove);
			this->GameArea->MouseLeave += new System::EventHandler(this, GameArea_MouseLeave);
			this->GameArea->MouseDown += new System::Windows::Forms::MouseEventHandler(this, GameArea_MouseDown);
			// 
			// StartEditor
			// 
			this->StartEditor->BackColor = System::Drawing::Color::SeaGreen;
			this->StartEditor->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->StartEditor->Location = System::Drawing::Point(328, 320);
			this->StartEditor->Name = S"StartEditor";
			this->StartEditor->Size = System::Drawing::Size(80, 23);
			this->StartEditor->TabIndex = 1;
			this->StartEditor->Text = S"Level editor...";
			this->StartEditor->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->StartEditor->Click += new System::EventHandler(this, StartEditor_Click);
			// 
			// GameLoop
			// 
			this->GameLoop->Interval = 40;
			this->GameLoop->Tick += new System::EventHandler(this, GameLoop_Tick);
			// 
			// InfoPanel
			// 
			this->InfoPanel->BackColor = System::Drawing::SystemColors::ControlDark;
			this->InfoPanel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->InfoPanel->Controls->Add(this->ThisWave);
			this->InfoPanel->Controls->Add(this->t_cur);
			this->InfoPanel->Controls->Add(this->NextWave);
			this->InfoPanel->Controls->Add(this->t_next);
			this->InfoPanel->Controls->Add(this->SpeedLabel);
			this->InfoPanel->Controls->Add(this->t_sp);
			this->InfoPanel->Controls->Add(this->GoldBox);
			this->InfoPanel->Controls->Add(this->t_g);
			this->InfoPanel->Controls->Add(this->t_hp);
			this->InfoPanel->Controls->Add(this->HealthBox);
			this->InfoPanel->Dock = System::Windows::Forms::DockStyle::Top;
			this->InfoPanel->Location = System::Drawing::Point(0, 0);
			this->InfoPanel->Name = S"InfoPanel";
			this->InfoPanel->Size = System::Drawing::Size(920, 64);
			this->InfoPanel->TabIndex = 3;
			// 
			// ThisWave
			// 
			this->ThisWave->BackColor = System::Drawing::Color::LightGray;
			this->ThisWave->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->ThisWave->Font = new System::Drawing::Font(S"Copperplate Gothic Bold", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->ThisWave->Location = System::Drawing::Point(488, 8);
			this->ThisWave->Name = S"ThisWave";
			this->ThisWave->Size = System::Drawing::Size(160, 24);
			this->ThisWave->TabIndex = 9;
			this->ThisWave->Text = S"None";
			this->ThisWave->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->ThisWave->Click += new System::EventHandler(this, NextEnemy);
			// 
			// t_cur
			// 
			this->t_cur->BackColor = System::Drawing::Color::LightGray;
			this->t_cur->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->t_cur->Font = new System::Drawing::Font(S"Copperplate Gothic Bold", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->t_cur->Location = System::Drawing::Point(352, 8);
			this->t_cur->Name = S"t_cur";
			this->t_cur->Size = System::Drawing::Size(136, 24);
			this->t_cur->TabIndex = 8;
			this->t_cur->Text = S"Current (0)";
			this->t_cur->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->t_cur->Click += new System::EventHandler(this, NextEnemy);
			// 
			// NextWave
			// 
			this->NextWave->BackColor = System::Drawing::Color::LightGray;
			this->NextWave->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->NextWave->Font = new System::Drawing::Font(S"Copperplate Gothic Bold", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->NextWave->Location = System::Drawing::Point(488, 32);
			this->NextWave->Name = S"NextWave";
			this->NextWave->Size = System::Drawing::Size(160, 24);
			this->NextWave->TabIndex = 7;
			this->NextWave->Text = S"Normal";
			this->NextWave->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->NextWave->Click += new System::EventHandler(this, NextEnemy);
			// 
			// t_next
			// 
			this->t_next->BackColor = System::Drawing::Color::LightGray;
			this->t_next->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->t_next->Font = new System::Drawing::Font(S"Copperplate Gothic Bold", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->t_next->Location = System::Drawing::Point(352, 32);
			this->t_next->Name = S"t_next";
			this->t_next->Size = System::Drawing::Size(136, 24);
			this->t_next->TabIndex = 6;
			this->t_next->Text = S"Next Wave:";
			this->t_next->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->t_next->Click += new System::EventHandler(this, NextEnemy);
			// 
			// SpeedLabel
			// 
			this->SpeedLabel->BackColor = System::Drawing::Color::DarkBlue;
			this->SpeedLabel->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->SpeedLabel->Font = new System::Drawing::Font(S"Copperplate Gothic Bold", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->SpeedLabel->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->SpeedLabel->Location = System::Drawing::Point(776, 16);
			this->SpeedLabel->Name = S"SpeedLabel";
			this->SpeedLabel->Size = System::Drawing::Size(104, 24);
			this->SpeedLabel->TabIndex = 5;
			this->SpeedLabel->Text = S"Medium";
			this->SpeedLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->SpeedLabel->MouseDown += new System::Windows::Forms::MouseEventHandler(this, SpeedLabel_MouseDown);
			// 
			// t_sp
			// 
			this->t_sp->BackColor = System::Drawing::Color::DarkBlue;
			this->t_sp->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->t_sp->Font = new System::Drawing::Font(S"Copperplate Gothic Bold", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->t_sp->ForeColor = System::Drawing::SystemColors::ControlLightLight;
			this->t_sp->Location = System::Drawing::Point(688, 16);
			this->t_sp->Name = S"t_sp";
			this->t_sp->Size = System::Drawing::Size(88, 24);
			this->t_sp->TabIndex = 4;
			this->t_sp->Text = S"Speed:";
			this->t_sp->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// GoldBox
			// 
			this->GoldBox->BackColor = System::Drawing::Color::Gold;
			this->GoldBox->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->GoldBox->Font = new System::Drawing::Font(S"Copperplate Gothic Bold", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->GoldBox->Location = System::Drawing::Point(232, 16);
			this->GoldBox->Name = S"GoldBox";
			this->GoldBox->Size = System::Drawing::Size(88, 24);
			this->GoldBox->TabIndex = 3;
			this->GoldBox->Text = S"50";
			this->GoldBox->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// t_g
			// 
			this->t_g->BackColor = System::Drawing::Color::Gold;
			this->t_g->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->t_g->Font = new System::Drawing::Font(S"Copperplate Gothic Bold", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->t_g->Location = System::Drawing::Point(160, 16);
			this->t_g->Name = S"t_g";
			this->t_g->Size = System::Drawing::Size(72, 24);
			this->t_g->TabIndex = 2;
			this->t_g->Text = S"Gold:";
			this->t_g->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// t_hp
			// 
			this->t_hp->BackColor = System::Drawing::Color::LimeGreen;
			this->t_hp->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->t_hp->Font = new System::Drawing::Font(S"Copperplate Gothic Bold", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->t_hp->Location = System::Drawing::Point(40, 16);
			this->t_hp->Name = S"t_hp";
			this->t_hp->Size = System::Drawing::Size(48, 24);
			this->t_hp->TabIndex = 1;
			this->t_hp->Text = S"HP:";
			this->t_hp->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// HealthBox
			// 
			this->HealthBox->BackColor = System::Drawing::Color::LimeGreen;
			this->HealthBox->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->HealthBox->Font = new System::Drawing::Font(S"Copperplate Gothic Bold", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (System::Byte)0);
			this->HealthBox->Location = System::Drawing::Point(88, 16);
			this->HealthBox->Name = S"HealthBox";
			this->HealthBox->Size = System::Drawing::Size(48, 24);
			this->HealthBox->TabIndex = 0;
			this->HealthBox->Text = S"20";
			this->HealthBox->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// LoadLevel
			// 
			this->LoadLevel->Filter = S"Level File (*.txt)|*.txt|All Files (*.*)|*.*";
			// 
			// LoadWaves
			// 
			this->LoadWaves->Filter = S"WaveSequence File (*.txt)|*.txt|All Files (*.*)|*.*";
			// 
			// Form1
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(5, 13);
			this->BackColor = System::Drawing::Color::LightGreen;
			this->ClientSize = System::Drawing::Size(920, 664);
			this->Controls->Add(this->InfoPanel);
			this->Controls->Add(this->GameArea);
			this->Controls->Add(this->ControlPanel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->KeyPreview = true;
			this->MaximizeBox = false;
			this->Name = S"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = S"7 Rivers Tower Defence";
			this->KeyDown += new System::Windows::Forms::KeyEventHandler(this, Form1_KeyDown);
			this->Closing += new System::ComponentModel::CancelEventHandler(this, Form1_Closing);
			this->GameArea->ResumeLayout(false);
			this->InfoPanel->ResumeLayout(false);
			this->ResumeLayout(false);

		}	
	private: void SetInitialSettings()
		{
			ld->LoadMeter->Value = 1;
			ld->Details->Text = "Initializing variables";
			ld->Details->Refresh();
			tv = new char __gc[Maps::MW+8,Maps::MH+8];
			ts = new Turret * __gc[TMAX];
			es = new Enemy * __gc[EMAX];
			for (int i = 0; i < TMAX; i++)
				ts[i] = new Turret();
			for (int i = 0; i < EMAX; i++)
				es[i] = new Enemy();
			sf = new StringFormat();
			sf->Alignment = StringAlignment::Center;
			sf->LineAlignment = StringAlignment::Center;
			eMax = 40;
			tMax = 1;
			tei = -1; eei = -1;
			hp = INIT_HP;
			gold = INIT_GOLD;
			paused = false;
			Map = new char __gc[SSMAX];
			obj = new Object();
			pea = new PaintEventArgs(ControlPanel->CreateGraphics(), ControlPanel->ClientRectangle);
			ea = new EventArgs();
			mea = new MouseEventArgs(MouseButtons::Left, 1, 0, 0, 0);
			HealthBox->BackColor = Color::FromArgb(0,240,0);
			t_hp->BackColor = Color::FromArgb(0,240,0);
			HealthBox->Text = INIT_HP.ToString();
			GoldBox->Text = INIT_GOLD.ToString();
			ld->LoadMeter->Value = 3;
			ld->Details->Text = "Creating image templates";
			ld->Details->Refresh();
			bmp = new Bitmap(GameArea->Width, GameArea->Height);
			cpb = new Bitmap(ControlPanel->Width, ControlPanel->Height);
			p = new Pen(Color::Black);
			p1 = new Pen(Color::Gray, 1);
			p2 = new Pen(Color::Silver, 3);
			p3 = new Pen(Color::Red, 2);
			br = new SolidBrush(Color::Black);
			hb = new HatchBrush(HatchStyle::LargeConfetti, Color::DimGray, Color::Black);
			hb2 = new HatchBrush(HatchStyle::SmallConfetti, Color::DarkRed, Color::Black);
			t_temp = new Turret();
			ld->LoadMeter->Value = 7;
			ld->Details->Text = "Reading string tables";
			ld->Details->Refresh();
			Strings::Initialize();
		}
	private: void SetGold(int _g)
			 {
				 gold = _g;
				 GoldBox->Text = gold.ToString();
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
		case 1: case 2:
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
private: void DrawTiles(Graphics * g, char m __gc[])
{
	br->Color = GameArea->BackColor;
	Point pts[] = new Point[4];
	LinearGradientBrush * lg;
	Color fec; // Fading effect color
	ld->Details->Text = "Unpacking maps";
	ld->Details->Refresh();
	tv = Maps::ToGrid(m);
	for (int i = 0; i < Maps::MW; i++)
	{
		ld->Details->Text = String::Concat("Unpacking tiles: ", (i+1).ToString(), "/", (Maps::MW+1).ToString());
		ld->Details->Refresh();
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
				DrawTopLayer(Graphics::FromImage(top), tv[i,j], i, j);
				break;
			case 11: // TODO: River tiles (cases through to about 18 may be needed)
				break;
			default:
				if (MessageBox::Show(tv[i,j].ToString(), "Undefined tile") == DialogResult::OK)
					break;
			}
		}
		lp += 0.5;
		ld->LoadMeter->Value = lp;
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
		ld->Details->Text = String::Concat("Unpacking tiles: ", (i+1).ToString(), "/", (Maps::MW+1).ToString());
		ld->Details->Refresh();
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
				DrawTopLayer(Graphics::FromImage(top), tv[i,j], i, j);
				break;
			case 11: // TODO: River tiles (cases through to about 18 may be needed)
				break;
			default:
				if (MessageBox::Show(tv[i,j].ToString(), "Undefined tile") == DialogResult::OK)
					break;
			}
		}
	} 
}

	private: void InitializeGraphics(char m __gc[]) // Initializes all graphics from a selected map
			 {
				 Point loc = this->get_Location();
				 this->set_Location(Point(0,0));
				 ld->LoadMeter->Value = 18;
				 ld->Details->Text = "Initializing bitmaps";
				 ld->Details->Refresh();
				 Bitmap * bit = new Bitmap(GameArea->Width, GameArea->Height);
				 tiles = new Bitmap(GameArea->Width, GameArea->Height);
				 top = new Bitmap(GameArea->Width, GameArea->Height);
				 info = new Bitmap(160,260);
				 Graphics * g = Graphics::FromImage(bmp);
				 Graphics * gt = Graphics::FromImage(tiles);
				 Graphics * gf = Graphics::FromImage(bit);
				 Graphics * gi = Graphics::FromImage(info);
				 StartGame->Visible = false;
				 StartEditor->Visible = false;
				 ld->LoadMeter->Value = 21;
				 lp = 21;
				 DrawTiles(gt, m);
				 ld->Details->Text = "Initializing grid";
				 ld->Details->Refresh();
				 DrawGrid(gt);
				 ld->LoadMeter->Value = 28;
				 ld->Details->Text = "Initializing interfaces";
				 ld->Details->Refresh();
				 DrawInfoBox(gi);
				 ld->LoadMeter->Value = 31;
				 ld->Details->Text = "Initializing turrets";
				 ld->Details->Refresh();
				 Turrets::InitializeTurretImages();
				 ld->LoadMeter->Value = 34;
				 ld->Details->Text = "Initializing translucency";
				 ld->Details->Refresh();
				 g->DrawImage(top, 0, 0); // Add translucent layer
				 ld->LoadMeter->Value = 38;
				 ld->Details->Text = "Initializing tilesets";
				 ld->Details->Refresh();
				 gf->DrawImage(tiles,0,0);
				 ld->LoadMeter->Value = 41;
				 ld->Details->Text = "Initializing graphics";
				 ld->Details->Refresh();
				 gf->DrawImage(bmp,0,0);
				 GameArea->CreateGraphics()->DrawImage(bit, 0, 0);
				 this->set_Location(loc);
			 }
	private: void InitializeGraphics(void) // Updates tile graphics
			 {
				 Bitmap * bit = new Bitmap(GameArea->Width, GameArea->Height);
				 tiles = new Bitmap(GameArea->Width, GameArea->Height);
				 top = new Bitmap(GameArea->Width, GameArea->Height);
				 Graphics * g = Graphics::FromImage(bmp);
				 Graphics * gt = Graphics::FromImage(tiles);
				 Graphics * gf = Graphics::FromImage(bit);
				 DrawTiles(gt);
				 DrawGrid(gt);
				 g->DrawImage(top, 0, 0); // Add translucent layer
				 gf->DrawImage(tiles,0,0);
				 gf->DrawImage(bmp,0,0);
				 GameArea->CreateGraphics()->DrawImage(bit, 0, 0);
			 }

	private: void InitializeEnemy(int _wi, int _delay)
			 {
				 if (_wi >= Sequence->Count)
					 FinalizeGame(Strings::GameOver[VICTORY]);
				 else
				 {
					 CurrentWave = Sequence->GetWave(_wi);
					 eci = 0;
					 next = _delay;
					 ThisWave->Text = Strings::Enemy[Sequence->GetWave(wi)->Type];
					 ThisWave->BackColor = Strings::ColorCode[Sequence->GetWave(wi)->Type];
					 t_cur->BackColor = NextWave->BackColor;
					 wi++; // Conveniently assigns a human-readable wave number for this wave.
					 t_cur->Text = String::Concat("Current (", wi.ToString(), ")");
					 if (wi < Sequence->Count)
					 {
						 NextWave->Text = Strings::Enemy[Sequence->GetWave(wi)->Type];
						 NextWave->BackColor = Strings::ColorCode[Sequence->GetWave(wi)->Type];
						 t_next->BackColor = NextWave->BackColor;
					 }
					 else
					 {
						 NextWave->Text = Strings::Enemy[ETMAX-1];
						 NextWave->BackColor = Strings::ColorCode[ETMAX-1];
						 t_next->BackColor = NextWave->BackColor;
					 }
					 es = CurrentWave->EnemyList;
					 eMax = CurrentWave->Count;
				 }
			 }

	private: void FinalizeGame(String * s)
			 {
				 GameLoop->Enabled = false;
				 if (MessageBox::Show(s, "7 Rivers Tower Defence", MessageBoxButtons::OK, MessageBoxIcon::Information, MessageBoxDefaultButton::Button1) == DialogResult::OK)
				 {
					 Graphics * g = GameArea->CreateGraphics();
					 g->Clear(GameArea->BackColor);
				 }
				 else
					 this->Close();
				 StartGame->Visible = true;
				 StartEditor->Visible = true;
				 return;
			 }
	private: void FinalizeGame(void)
			 {
				 GameLoop->Enabled = false;
				 Graphics * g = GameArea->CreateGraphics();
				 g->Clear(GameArea->BackColor);
				 StartGame->Visible = true;
				 StartEditor->Visible = true;
				 return;
			 }
	private: void BuildTurret(int _ti, int _x, int _y)
			 {
				 int i = 0;
				 FreezeCP = false;
				 if (gold >= Turret::BuildCost(_ti))
					 SetGold(gold - Turret::BuildCost(_ti));
				 else
					 return;
				 for (i = 0; i < TMAX; i++)
				 {
					 if (ts[i]->Type == -1)
					 {
						 i = -i;
						 tMax++;
						 break;
					 }
				 }
				 if (i > 0)
				 {
					 GameLoop->Enabled = false;
					 if (MessageBox::Show("Turret limit reached!", "7 Towers TD", MessageBoxButtons::OK, MessageBoxIcon::Warning, MessageBoxDefaultButton::Button1) == DialogResult::OK)
					 {
						 GameLoop->Enabled = true;
						 return;
					 }
				 }
				 ts[-i] = new Turret(_ti, _x, _y, 1);
				 if (ts[-i]->Type != -1) // If it IS -1, it may as well not even have got created. So there.
					 tv[_x,_y] = -8;
			 }
	private: int CheckRange(int _ti)
			 {
				 for (int i = 0; i < eMax; i++)
				 {
					 if (es[i]->Type == -1)
						 continue;
					 if (Math::Pow(ts[_ti]->X*GS - es[i]->X, 2) + Math::Pow(ts[_ti]->Y*GS - es[i]->Y, 2) <= Math::Pow(ts[_ti]->Range, 2))
					 {
						 return i; // Returns the index of an enemy lying within a circle of radius [Range]
					 }
				 }
				 return -1;
			 }
	private: int CheckRange(int _ti, int _min)
			 {
				 for (int i = _min; i < eMax; i++)
				 {
					 if (es[i]->Type == -1)
						 continue;
					 if (Math::Pow(ts[_ti]->X*GS - es[i]->X, 2) + Math::Pow(ts[_ti]->Y*GS - es[i]->Y, 2) <= Math::Pow(ts[_ti]->Range, 2))
					 {
						 return i; // Returns the index of an enemy lying within a circle of radius [Range]
					 }
				 }
				 return -1;
			 }
	private: void ReduceHealth(int _dmg)
			{
				hp -= _dmg;
				HealthBox->Text = hp.ToString();
				HealthBox->BackColor = Color::FromArgb((28-hp)*9, Math::Sqrt(hp)*50, 50);
				t_hp->BackColor = HealthBox->BackColor;
				if (hp <= 0)
					FinalizeGame(Strings::GameOver[DEFEAT]);
			}
	private: void ShowInformation(Graphics * g, int _sx, int _sy)
			 {
				 int _ti = (_sy-1)*2 + _sx-1;
				 g->DrawImageUnscaled(info, 10, INFO_Y);
				 RectangleF rectft = RectangleF(10,10+INFO_Y,160,50);
				 RectangleF rectf = RectangleF(99+10, 94+INFO_Y, 50, 26);
				 RectangleF trec = RectangleF(10+10, 94+INFO_Y, 85, 26);
				 t_temp = new Turret(_ti, 0, 0, 0);
				 g->DrawString("Damage", pf, Brushes::Gray, trec, sf);
				 trec.Y += 30;
				 g->DrawString("Range", pf, Brushes::Gray, trec, sf);
				 trec.Y += 30;
				 g->DrawString("Delay", pf, Brushes::Gray, trec, sf);
				 g->DrawString(t_temp->Name, pf, Brushes::Silver, rectft, sf);
				 rectft.Y += 40;
				 g->DrawString(String::Concat("Cost: ", Turret::BuildCost(t_temp->Type).ToString()), pf, Brushes::Silver, rectft, sf);
				 g->DrawString(t_temp->Damage.ToString(), pf, Brushes::DarkGray, rectf, sf);
				 rectf.Y += 30;
				 g->DrawString(t_temp->Range.ToString(), pf, Brushes::DarkGray, rectf, sf);
				 rectf.Y += 30;
				 g->DrawString(t_temp->ShotDelay.ToString(), pf, Brushes::DarkGray, rectf, sf);
				 t_temp->Type = -1;
			 }
	private: void ShowInformation(Graphics * g, Turret * tu)
			 {
				 g->DrawImageUnscaled(info, 10, INFO_Y);
				 RectangleF rectft = RectangleF(10,10+INFO_Y,160,50);
				 RectangleF rectf = RectangleF(99+10, 94+INFO_Y, 50, 26);
				 RectangleF trec = RectangleF(10+10, 94+INFO_Y, 85, 26);
				 RectangleF rectf1 = RectangleF(15+10, 199+INFO_Y, 70, 30);
				 RectangleF rectf2 = RectangleF(95+10, 199+INFO_Y, 50, 30);
				 Drawing::Rectangle rect1 = Drawing::Rectangle(rectf1.Left, rectf1.Top, rectf1.Width, rectf1.Height);
				 Drawing::Rectangle rect2 = Drawing::Rectangle(rectf2.Left, rectf2.Top, rectf2.Width, rectf2.Height);
				 g->DrawString("Damage", pf, Brushes::Gray, trec, sf);
				 trec.Y += 30;
				 g->DrawString("Range", pf, Brushes::Gray, trec, sf);
				 trec.Y += 30;
				 g->DrawString("Delay", pf, Brushes::Gray, trec, sf);
				 g->DrawString(tu->Name, pf, Brushes::Silver, rectft, sf);
				 rectft.Y += 40;
				 if (tu->Level == MASTER)
					 g->DrawString(Strings::Special[tu->Type], pf, Brushes::Lime, rectft, sf);
				 else
					 g->DrawString(String::Concat("Level ", tu->Level.ToString()), pf, Brushes::Silver, rectft, sf);
				 g->DrawString(tu->Damage.ToString(), pf, Brushes::DarkGray, rectf, sf);
				 rectf.Y += 30;
				 g->DrawString(tu->Range.ToString(), pf, Brushes::DarkGray, rectf, sf);
				 rectf.Y += 30;
				 g->DrawString(tu->ShotDelay.ToString(), pf, Brushes::DarkGray, rectf, sf);
				 p->Color = Color::WhiteSmoke;
				 p->Width = 2;
				 g->DrawRectangle(p, rect1);
				 g->DrawRectangle(p, rect2);
				 g->DrawString(String::Concat("Upgrade (", tu->UpgradeCost.ToString(), ")"), pfs, Brushes::DarkGray, rectf1, sf);
				 g->DrawString(String::Concat("Sell (", tu->SellValue.ToString(), ")"), pfs, Brushes::DarkGray, rectf2, sf);
			 }
	private: void ShowInformation(Graphics * g, Enemy * en)
			 {
				 g->DrawImageUnscaled(info, 10, INFO_Y);
				 RectangleF rectft = RectangleF(10,10+INFO_Y,160,50);
				 RectangleF rectf = RectangleF(99+10, 94+INFO_Y, 50, 26);
				 RectangleF trec = RectangleF(10+10, 94+INFO_Y, 85, 26);
				 g->DrawString("HP", pf, Brushes::Gray, trec, sf);
				 trec.Y += 30;
				 g->DrawString("Speed", pf, Brushes::Gray, trec, sf);
				 trec.Y += 30;
				 g->DrawString("ID", pf, Brushes::Gray, trec, sf);
				 g->DrawString(en->Name, pf, Brushes::Silver, rectft, sf);
				 if (en->HP >= 1000)
					 g->DrawString(en->HP.ToString(), pfs, Brushes::DarkGray, rectf, sf);
				 else
					 g->DrawString(en->HP.ToString(), pf, Brushes::DarkGray, rectf, sf);
				 rectf.Y += 30;
				 g->DrawString((10*GS/en->Speed).ToString("G3"), pf, Brushes::DarkGray, rectf, sf);
				 rectf.Y += 30;
				 g->DrawString(eei.ToString(), pf, Brushes::DarkGray, rectf, sf);
				 p->Color = Color::Black;
				 p->Width = 1;
			 }
	private: void DrawInfoBox(Graphics * g)
			 {
				 HatchBrush * hb = new HatchBrush(HatchStyle::HorizontalBrick, Color::FromArgb(25,25,25), Color::Black);
				 LinearGradientBrush * lgb = new LinearGradientBrush(Point(10,10), Point(160,250), Color::FromArgb(100, Color::Silver), Color::FromArgb(100, Color::Black));
				 LinearGradientBrush * lg2 = new LinearGradientBrush(Point(0,0), Point(160,260), Color::Gray, Color::FromArgb(30,30,30));
				 LinearGradientBrush * lgs = new LinearGradientBrush(Point(16,16), Point(24,24), Color::LightGray, Color::Black);
				 Drawing::Rectangle rect = Drawing::Rectangle(10, 10, 140, 240);
				 Drawing::Rectangle rect2 = Drawing::Rectangle(0, 0, 160, 260);
				 g->FillRectangle(lg2, rect2);
				 g->DrawRectangle(Pens::Black, rect2);
				 g->DrawRectangle(Pens::Black, rect);
				 g->DrawLine(Pens::Black, Point(0,0), Point(10,10));
				 g->DrawLine(Pens::Black, Point(0,260), Point(10,250));
				 g->DrawLine(Pens::Black, Point(160,0), Point(150,10));
				 g->DrawLine(Pens::Black, Point(160,260), Point(150,250));
				 g->FillRectangle(hb, rect);
				 g->FillRectangle(lgb, rect);
				 g->FillEllipse(lgs, 16, 16, 8, 8);
				 lgs = new LinearGradientBrush(Point(15+122,15), Point(24+122,24), Color::LightGray, Color::Black);
				 g->FillEllipse(lgs, 16+122, 16, 8, 8);
				 lgs = new LinearGradientBrush(Point(10+122,10+222), Point(24+122,24+222), Color::LightGray, Color::Black);
				 g->FillEllipse(lgs, 16+122, 16+222, 8, 8);
				 lgs = new LinearGradientBrush(Point(14,14+222), Point(24,24+222), Color::LightGray, Color::Black);
				 g->FillEllipse(lgs, 16, 16+222, 8, 8);
				 g->DrawLine(Pens::DarkGray, 20, 50, 140, 50);
				 g->DrawLine(Pens::DarkGray, 20, 51, 139, 51);
				 g->DrawLine(Pens::Gray, 20, 52, 138, 52);
				 g->DrawLine(Pens::Gray, 20, 53, 137, 53);
				 g->DrawLine(Pens::DimGray, 20, 54, 136, 54);
				 g->DrawLine(Pens::DimGray, 20, 55, 135, 55);
				 for (int i = 90; i <= 180; i += 30)
				 {
					 g->DrawLine(Pens::DarkGray, 20, i, 139, i);
					 g->DrawLine(Pens::Gray, 20, i+1, 138, i+1);
					 g->DrawLine(Pens::Gray, 20, i+2, 137, i+2);
					 g->DrawLine(Pens::DimGray, 20, i+3, 136, i+3);
					 g->DrawLine(Pens::DimGray, 20, i+4, 135, i+4);
				 }
				 g->DrawLine(Pens::DarkGray, 95, 88, 95, 190);
				 g->DrawLine(Pens::DarkGray, 96, 88, 96, 189);
				 g->DrawLine(Pens::Gray, 97, 88, 97, 188);
				 g->DrawLine(Pens::Gray, 98, 88, 98, 187);
				 g->DrawLine(Pens::DimGray, 99, 88, 99, 186);
				 g->DrawLine(Pens::DimGray, 100, 88, 100, 185);
			 }
	private: System::Void StartGame_Click(System::Object *  sender, System::EventArgs *  e)
			 {
				 lsd = new LevelSelect(1, GameArea->Width, GameArea->Height);
				 if (lsd->ShowDialog() != DialogResult::OK)
					 return;
				 ld = new LoadDialog();
				 ld->Details->Text = "Initializing graphics";
				 ld->Show(); // Non-modal to keep Form1 initializing
				 ld->timer1->Tick += new System::EventHandler(this, InitializeGame);
				 ld->timer1->Enabled = true;
			 }

	private: System::Void InitializeGame(System::Object *  sender, System::EventArgs *  e)
			 {
				 ld->timer1->Enabled = false;
				 ld->Details->Text = "Initializing variables";
				 ld->Details->Refresh();
				 SetInitialSettings();
				 ld->Details->Refresh();
				 LoadLevel->InitialDirectory = Environment::CurrentDirectory;
				 String * file, * subfile, * filedir;
				 String * data __gc[];
				 bool loadfile = 1;
				 if (lsd->LevelIndex == 0)
				 {
					if (LoadLevel->ShowDialog() == DialogResult::OK)
					{
						try
						{
							fs = new FileStream(LoadLevel->FileName, FileMode::Open, FileAccess::Read);
							sr = new StreamReader(fs, Encoding::ASCII);
							file = sr->ReadToEnd();
							sr->Close();
							data = new String * __gc[4];
							data = file->Split(S","->ToCharArray(), 4);
							filedir = LoadLevel->FileName->Remove(LoadLevel->FileName->LastIndexOf("\\"), LoadLevel->FileName->Length - LoadLevel->FileName->LastIndexOf("\\"));
							subfile = String::Concat(filedir, "\\", data[0]); // data[0] is map file name
							if (!File::Exists(subfile))
							{
								subfile = String::Concat(filedir, "\\", data[0], data[2]);
								if (!File::Exists(subfile)) // data[2] is a standard extension
									throw new Exception("Map file failed to load!");
							}
							Map = Maps::FromFile(subfile, 0);
							subfile = String::Concat(filedir, "\\", data[1]); // data[1] is wave file name
							if (!File::Exists(subfile))
							{
								subfile = String::Concat(filedir, "\\", data[1], data[2]);
								if (!File::Exists(subfile)) // data[2] is a standard extension
									throw new Exception("Wave file failed to load!");
							}
						}
						catch (Exception * ex)
						{
							loadfile = 0;
							MessageBox::Show(ex->Message, this->Text, MessageBoxButtons::OK, MessageBoxIcon::Error);
							try
							{
								sr->Close();
							}
							catch (Exception * ex2)
							{
								MessageBox::Show(ex2->Message, this->Text, MessageBoxButtons::OK, MessageBoxIcon::Error);
							}
							Map = Maps::map1;
						}
					}
				 }
				 else
				 {
					 switch (lsd->LevelIndex)
					 {
					 case 1:
						 Map = Maps::map1;
						 loadfile = 0;
						 break;
					 case 2:
						 Map = Maps::map2;
						 loadfile = 0;
						 break;
					 case 3:
						 Map = Maps::map3;
						 loadfile = 0;
						 break;
					 case 4:
						 Map = Maps::map4;
						 loadfile = 0;
						 break;
					 case 5:
						 Map = Maps::map5;
						 loadfile = 0;
						 break;
					 case 6:
						 Map = Maps::map6;
						 loadfile = 0;
						 break;
					 default:
						 break;
					 }
				 }
				 if (Map->Length == 1)
				 {
					 ld->Close();
					 FinalizeGame();
					 return;
				 }
				 InitializeGraphics(Map);
				 ld->LoadMeter->Value = 50;
				 ld->Details->Text = "Initializing waves";
				 ld->Details->Refresh();
				 tMax = 1;
				 waves = new Waves();
				 if (loadfile)
					 this->Sequence = waves->get_FileSequence(subfile, Map, 0);
				 else
					 this->Sequence = Waves::get_Sequence(lsd->LevelIndex);
				 if (Sequence->Count == 0)
				 {
					 ld->Close();
					 FinalizeGame();
					 return;
				 }
				 ld->LoadMeter->Value = 95;
				 ld->Details->Text = "Initializing enemies";
				 ld->Details->Refresh();
				 wi = INIT_WAVE - 1;
				 InitializeEnemy(wi, 50);
				 GameLoop->Enabled = true;
				 ld->LoadMeter->Value = 100;
				 ld->Details->Text = "Initializing interfaces";
				 ld->Details->Refresh();
				 ControlPanel_Paint(obj, pea);
				 ld->Close();
			 }

	private: System::Void StartGame_MouseEnter(System::Object *  sender, System::EventArgs *  e)
			 {
				 StartGame->Font = new Drawing::Font(StartGame->Font, FontStyle::Bold);
			 }

	private: System::Void StartGame_MouseLeave(System::Object *  sender, System::EventArgs *  e)
			 {
				 StartGame->Font = new Drawing::Font(StartGame->Font, FontStyle::Regular);
			 }

private: System::Void GameLoop_Tick(System::Object *  sender, System::EventArgs *  e)
		 {
			 // ---- GameArea logic ----
			 if (GameLoop->Interval == FAST)
				 draw = !draw;
			 else
				 draw = 1;
			 Graphics * g = Graphics::FromImage(bmp);
			 if (draw)
			 {
				 g->Clear(GameArea->BackColor);
				 p->Color = Color::Black;
				 p->Width = 1;
				 br->Color = Color::Black;
				 g->DrawImage(tiles, 0, 0);
			 }
			 int cr;
			 // Spawn new enemies at appropriate times
			 if (eci < CurrentWave->Count)
				 next--;
			 if (next == 0)
			 {
				 es[eci]->Type = CurrentWave->Type;
				 next = es[eci]->Trigger;
				 eci++;
			 }
			 // Enemy logic
			 for (int i = 0; i < eMax; i++)
			 {
				 if (es[i]->Type == -1)
					 continue;
				 // Apply traits
				 switch (es[i]->Type)
				 {
				 case REGEN: // Regenerator
					 es[i]->HP++; // Limited in set method
					 break;
				 case REGEN_BOSS:
					 es[i]->HP += 2;
					 break;
				 case ERRATIC: // Erratic
				 case ERRATIC_BOSS:
					 if (es[i]->Speed > 1000)
					 {
						 es[i]->SpeedPhase--;
						 if (r->Next(0,ERR_RATE) == 0)
							 es[i]->Speed = es[i]->InitialSpeed;
					 }
					 else
					 {
						 if (r->Next(0,ERR_RATE) == 0)
							 es[i]->Speed = Int32::MaxValue;
					 }
				 }
				 if (draw)
					 es[i]->Draw(g);
				 switch (es[i]->Direction)
				 {
				 case 1:
					 es[i]->Y -= (double)GS/es[i]->Speed;
					 break;
				 case 2:
					 es[i]->X -= (double)GS/es[i]->Speed;
					 break;
				 case 3:
					 es[i]->Y += (double)GS/es[i]->Speed;
					 break;
				 case 4:
					 es[i]->X += (double)GS/es[i]->Speed;
					 break;
				 }
				 es[i]->SpeedPhase++;
				 if (draw) // The logic to limit phase bounds is conveniently in its set method :)
					 es[i]->Phase += 0.5; 
				 if (es[i]->Speed == es[i]->SpeedPhase)
				 {
					 es[i]->SpeedPhase = 0; // So this only happens every [speed] ticks.
					 if (tv[(es[i]->X+1)/GS, (es[i]->Y+1)/GS] == 2)
					 {
						 es[i]->Direction = es[i]->get_Path(es[i]->PathPoint);
						 es[i]->PathPoint++;
					 }
					 else if (tv[(es[i]->X+1)/GS, (es[i]->Y+1)/GS] > 6 && tv[(es[i]->X+1)/GS, (es[i]->Y+1)/GS] <= 10)
					 {
						 if (es[i]->Type >= BOSS)
							 ReduceHealth(BOSS_DAMAGE);
						 else
							 ReduceHealth(1);
						 es[i]->HP = 0;
						 es[i]->Type = -1;
						 if (eei == i)
							 eei = -1;
						 bool w_end = 1;
						 for (int j = 0; j < eMax; j++)
						 {
							 if (es[j]->HP > 0)
							 {
								 w_end = 0;
								 break;
							 }
						 }
						 if (w_end)
							 InitializeEnemy(wi, 1);
					 }
				 }
			 }
			 // Turret logic
			 for (int i = 0; i < tMax; i++)
			 {
				 if (ts[i]->Type == -1)
					 continue;
				 if (ts[i]->CurrentDelay != 0)
					 ts[i]->CurrentDelay--;
				 else
				 {
					 cr = CheckRange(i);
					 while (cr != -1) // Enemy targeted
					 {
						 es[cr]->HP -= ts[i]->Damage; // The logic to limit HP bounds is equally convenient!
						 p->Color = ts[i]->ShotColor;
						 p->Width = ts[i]->ShotWidth;
						 g->DrawLine(p, ts[i]->X*GS+GS/2, ts[i]->Y*GS+GS/2, (int)es[cr]->X+GS/2, (int)es[cr]->Y+GS/2);
						 ts[i]->CurrentDelay = ts[i]->ShotDelay;
						 if (ts[i]->Type == 3 && ts[i]->Level == MASTER)
						 {
							 ts[i]->ShotCount++;
							 if (ts[i]->ShotCount % 40 == 10)
								 ts[i]->ShotDelay = 12;
							 else if (ts[i]->ShotCount % 40 == 20)
								 ts[i]->ShotDelay = 28;
						 }
						 if (es[cr]->Type == -1)
						 {
							 SetGold(gold + es[cr]->Gold);
							 if (eei == cr)
								 eei = -1;
							 bool w_end = 1;
							 for (int j = 0; j < eMax; j++)
							 {
								if (es[j]->HP > 0)
								{
									w_end = 0;
									break;
								}
							 }
							 if (w_end)
							 {
								 InitializeEnemy(wi, RELAX);
							 }
						 }
						 if (ts[i]->Type == 2 && ts[i]->Level == MASTER)
							 cr = CheckRange(i, cr+1);
						 else
							 cr = -1;
					 }
				 }
				 // Draw turret
				 if (draw)
				 {
					g->DrawImage(ts[i]->Image, ts[i]->X*GS, ts[i]->Y*GS, GS, GS);
					for (int j = 1; j < ts[i]->Level; j++)
					{
			 // It's probably not obvious, so for the record, this creates one plus sign per level above 1.
						g->DrawLine(Pens::Black, ts[i]->X*GS+28, ts[i]->Y*GS+j*5, ts[i]->X*GS+30, ts[i]->Y*GS+j*5);
						g->DrawLine(Pens::Black, ts[i]->X*GS+29, ts[i]->Y*GS+j*5-1, ts[i]->X*GS+29, ts[i]->Y*GS+j*5+1);
					}	
				 }
			 }
			 // Draw predefined top-layer effects
			 if (draw)
				 g->DrawImage(top, 0, 0);
			 // Check turret placement if applicable and draw turret range
			 if (FreezeCP && gx != -64 && draw)
			 {
				 px = gx/GS;
				 py = gy/GS;
				 if (tv[px,py] == 0)
					 br->Color = Color::FromArgb(70, Color::RoyalBlue);
				 else
					 br->Color = Color::FromArgb(70, Color::Red);
				 g->FillRectangle(br, px*GS, py*GS, GS, GS);
				 p->Color = Color::FromArgb(220, Color::Lime);
				 p->Width = 2;
				 Turret * t_temp = new Turret(ti, 0, 0, 0);
				 g->DrawEllipse(p, (int)px*GS + GS/2 - t_temp->Range, (int)py*GS + GS/2 - t_temp->Range, (int)t_temp->Range*2, (int)t_temp->Range*2);
			 }
			 // Draw turret range if mouse is hovering over it
			 else if (gx != -64)
			 {
				 int j = 0;
				 px = gx/GS;
				 py = gy/GS;
				 if (tv[px,py] == -8)
				 {
					 for (j = 0; j < TMAX; j++)
					 {
						 if (ts[j]->X == px && ts[j]->Y == py)
							 break;
					 }
					 if (draw)
					 {
						 p->Color = Color::FromArgb(220, Color::Lime);
						 p->Width = 2;
						 g->DrawEllipse(p, (int)ts[j]->X*GS + GS/2 - ts[j]->Range, (int)ts[j]->Y*GS + GS/2 - ts[j]->Range, (int)ts[j]->Range*2, (int)ts[j]->Range*2);
					 }
				 }
			 }
			 GameArea->CreateGraphics()->DrawImage(bmp, 0, 0);
			 // ---- ControlPanel logic ----
			 if (mx > 34 && mx < 154 && my > 39 && my < 40+30*TTMAX)
			 {
				 sx = (int)(mx+26)/60;
				 sy = (int)(my+21)/60; 
			 }
			 else
				 sx = 0;
			 if (!FreezeCP && draw)
			 	 ControlPanel_Paint(obj, pea);
		 }

private: System::Void Form1_Closing(System::Object *  sender, System::ComponentModel::CancelEventArgs *  e)
		 {
			 GameLoop->Enabled = false;
		 }

private: System::Void ControlPanel_Paint(System::Object *  sender, System::Windows::Forms::PaintEventArgs *  e)
		 {
			 if (!GameLoop->Enabled || FreezeCP)
				 return;
			 Graphics * g = Graphics::FromImage(cpb);
			 g->Clear(ControlPanel->BackColor);
			 for (int i = 1; i <= TTMAX/2+1; i++)
				 g->DrawLine(p2, 34, i*60-21, 154, i*60-21);
			 for (int i = 1; i <= 3; i++)
				 g->DrawLine(p2, i*60-27, 40, i*60-27, 40+30*TTMAX); 
			 for (int i = 1; i <= TTMAX/2+1; i++)
				 g->DrawLine(p1, 34, i*60-20, 154, i*60-20); 
			 for (int i = 1; i <= 3; i++)
				 g->DrawLine(p1, i*60-26, 40, i*60-26, 40+30*TTMAX);
			 g->DrawImage(Turrets::MGTurret, Drawing::Rectangle(38, 44, 52, 52));
			 g->DrawImage(Turrets::SniperTurret, Drawing::Rectangle(38+60, 44, 52, 52));
			 g->DrawImage(Turrets::LaserTurret, Drawing::Rectangle(38, 44+60, 52, 52));
			 g->DrawImage(Turrets::PlasmaCannon, Drawing::Rectangle(38+60, 44+60, 52, 52));
			 if (sx > 0 && sy > 0 && tei == -1 && eei == -1)
			 {
				 ShowInformation(g, sx, sy);
				 g->DrawRectangle(p3, sx*60-25, sy*60-19, 56, 56);
			 }
			 else if (tei != -1)
			 {
				 ShowInformation(g, ts[tei]);
			 }
			 if (eei != -1)
			 {
				 ShowInformation(g, es[eei]);
			 }
			 e->Graphics->DrawImage(cpb, 0, 0);
		 }

private: System::Void ControlPanel_MouseMove(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
		 {
			 mx = e->X;
			 my = e->Y;
		 }

private: System::Void ControlPanel_MouseDown(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
		 {
			 if (e->Button != MouseButtons::Left)
				 return;
			 Graphics * g = ControlPanel->CreateGraphics();
			 Drawing::Rectangle rect_up = Drawing::Rectangle(15+10, 199+330, 70, 30);
			 Drawing::Rectangle rect_se = Drawing::Rectangle(95+10, 199+330, 50, 30);
			 GraphicsPath * gp = new GraphicsPath();
			 gp->AddRectangle(Drawing::Rectangle(mx-1, my-1, 3, 3));
			 Drawing::Region * re_up = new Drawing::Region(gp);
			 Drawing::Region * re_se = new Drawing::Region(gp);
			 re_up->Intersect(rect_up);
			 re_se->Intersect(rect_se);
			 int u_temp;
			 if ((tei != -1 && !re_up->IsEmpty(g)) || e->Delta == -10)
			 {
				 u_temp = ts[tei]->Upgrade(gold);
				 if (u_temp >= 0)
					 SetGold(u_temp);
				 eei = -1;
			 }
			 else if ((tei != -1 && !re_se->IsEmpty(g)) || e->Delta == -15)
			 {
				 SetGold(ts[tei]->Sell(gold));
				 tv[ts[tei]->X,ts[tei]->Y] = CHARRED; // Charred
				 InitializeGraphics();
				 FreezeCP = false;
				 ti = -1;
				 tei = -1;
				 eei = -1;
			 }
			 else if (tei != -1)
				 tei = -1;
			 else if (sx != 0 && !FreezeCP)
			 {
				 FreezeCP = true;
				 ti = (sy-1)*2 + sx-1;
			 }
			 else if (FreezeCP)
			 {
				 FreezeCP = false;
				 ti = -1;
			 }
			 // And if none of the above is true, this does absolutely NOTHING! (Which is a good thing.)
		 }

private: System::Void ControlPanel_MouseUp(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
		 {
			 if (sx != 0)
			 {
				 FreezeCP = true;
				 ti = (sy-1)*2 + sx-1;
			 }
		 }
private: System::Void GameArea_MouseMove(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
		 {
			 gx = e->X;
			 gy = e->Y;
		 }

private: System::Void GameArea_MouseLeave(System::Object *  sender, System::EventArgs *  e)
		 {
			 gx = -64;
			 gy = -64;
		 }

private: System::Void GameArea_MouseDown(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
		 {
			 if (!GameLoop->Enabled)
				 return;
			 if (FreezeCP && gx != -64 && tv[px,py] == 0 && e->Button == MouseButtons::Left)
			 {
				 BuildTurret(ti, px, py);
				 FreezeCP = false;
				 gx = -64;
				 ControlPanel_Paint(obj, pea);
			 }
			 else if (tv[px,py] == -8 && e->Button == MouseButtons::Left)
			 {
				 int j = 0;
				 for (j = 0; j < TMAX; j++)
				 {
					 if (ts[j]->X == px && ts[j]->Y == py)
						 break;
				 }
				 tei = j;
				 eei = -1;
				 ControlPanel_Paint(obj, pea);
			 }
			 else if (tv[px,py] > 0 && e->Button == MouseButtons::Left) // All path tiles are greater than 0
			 {
				 int j = 0;
				 for (j = 0; j <= eMax; j++)
				 {
					 if (j == eMax)
						 break;
					 if (es[j]->Intersects(GameArea->CreateGraphics(), e->X, e->Y))
						 break;
				 }
				 if (j != eMax)
					 eei = j;
				 tei = -1;
				 ControlPanel_Paint(obj, pea);
			 }
			 else
			 {
				 tei = -1;
				 eei = -1;
				 FreezeCP = false;
				 ControlPanel_Paint(obj, pea);
			 }
		 }

private: System::Void ControlPanel_MouseLeave(System::Object *  sender, System::EventArgs *  e)
		 {
			 if (!FreezeCP)
			 {
				 sx = 0;
				 ControlPanel_Paint(obj, pea);
			 }
		 }

private: System::Void GameArea_MouseUp(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
		 {
			 if (!GameLoop->Enabled)
				 return;
			 if (e->Button != MouseButtons::Left)
				 return;
			 if (tv[px,py] == -8)
			 {
				 int j = 0;
				 for (j = 0; j < TMAX; j++)
				 {
					 if (ts[j]->X == px && ts[j]->Y == py)
						 break;
				 }
				 tei = j;
				 eei = -1;
				 ControlPanel_Paint(obj, pea);
			 }
		 }

private: System::Void SpeedLabel_MouseDown(System::Object *  sender, System::Windows::Forms::MouseEventArgs *  e)
		 {
			 switch (GameLoop->Interval)
			 {
			 case FAST:
				 if (e->Button == MouseButtons::Left)
				 {
					 GameLoop->Interval = 60;
					 SpeedLabel->Text = "Slow";
				 }
				 else
				 {
					 GameLoop->Interval = 40;
					 SpeedLabel->Text = "Medium";
				 }
				 break;
			 case 40:
				 if (e->Button == MouseButtons::Left)
				 {
					 GameLoop->Interval = FAST;
					 SpeedLabel->Text = "Fast";
				 }
				 else
				 {
					 GameLoop->Interval = 60;
					 SpeedLabel->Text = "Slow";
				 }
				 break;
			 case 60:
				 if (e->Button == MouseButtons::Left)
				 {
					 GameLoop->Interval = 40;
					 SpeedLabel->Text = "Medium";
				 }
				 else
				 {
					 GameLoop->Interval = FAST;
					 SpeedLabel->Text = "Fast";
				 }
			 }
		 }

private: System::Void NextEnemy(System::Object *  sender, System::EventArgs *  e)
		 {
			 if (GameLoop->Enabled && eci < CurrentWave->Count)
				 next = 1;
		 }

private: System::Void Form1_KeyDown(System::Object *  sender, System::Windows::Forms::KeyEventArgs *  e)
		 {
			 switch (e->KeyValue)
			 {
			 case Forms::Keys::N:
				 NextEnemy(obj, ea);
				 break;
			 case Forms::Keys::U:
				 mea = new MouseEventArgs(MouseButtons::Left, 1, 0, 0, -10);
				 ControlPanel_MouseDown(obj, mea);
				 break;
			 case Forms::Keys::S:
				 mea = new MouseEventArgs(MouseButtons::Left, 1, 0, 0, -15);
				 ControlPanel_MouseDown(obj, mea);
				 break;
			 case Forms::Keys::P:
				 if (GameLoop->Enabled && !paused)
				 {
					 GameLoop->Enabled = false;
					 paused = true;
				 }
				 else if (paused)
				 {
					 GameLoop->Enabled = true;
					 paused = false;
				 } // Else do nothing whatsoever, etc. etc...
				 break;
			 }
		 }

private: System::Void StartEditor_Click(System::Object *  sender, System::EventArgs *  e)
		 {
			 led = new LevelEditor();
			 this->Hide();
			 led->ShowDialog();
			 this->Show();
		 }

};
}


