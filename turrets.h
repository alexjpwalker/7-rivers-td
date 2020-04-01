using namespace System;
using namespace System::Drawing;
using namespace System::Drawing::Drawing2D;

namespace RiversTD
{
	public __gc __sealed class Turrets
	{
	public:
		static void InitializeTurretImages()
		{
			//
			// MG Turret
			//
			Graphics * g; GraphicsPath * gp; LinearGradientBrush * lgb;
			t1 = new Bitmap(32, 32);
			// t1 = __try_cast<Bitmap*>(Image::FromFile(String::Concat(Environment::CurrentDirectory, "\\Merlin's Head.bmp")));
			g = Graphics::FromImage(t1);
			gp = new GraphicsPath();
			lgb = new LinearGradientBrush(Point(0,0), Point(32,32), Color::FromArgb(70,70,70), Color::FromArgb(20,20,20));
			gp->AddArc(6, 12, 20, 16, 0, 180);
			gp->AddLine(26, 20, 26, 14);
			gp->AddArc(6, 6, 20, 16, 0, 180);
			gp->AddLine(7, 15, 7, 20);
			g->FillPath(lgb, gp);
			lgb = new LinearGradientBrush(Point(0,0), Point(32,32), Color::FromArgb(10,10,10), Color::Gray);
			g->FillEllipse(lgb, 6, 6, 20, 16);
			//
			// Sniper Turret
			//
			t2 = new Bitmap(32, 32);
			g = Graphics::FromImage(t2);
			gp->Reset();
			lgb = new LinearGradientBrush(Point(0,0), Point(32,32), Color::FromArgb(70,70,70), Color::FromArgb(20,20,20));
			gp->AddArc(6, 12, 20, 16, 0, 180);
			gp->AddLine(26, 20, 26, 14);
			gp->AddArc(6, 6, 20, 16, 0, 180);
			gp->AddLine(7, 15, 7, 20);
			g->FillPath(lgb, gp);
			lgb = new LinearGradientBrush(Point(0,0), Point(32,32), Color::FromArgb(10,10,10), Color::Gray);
			g->FillEllipse(lgb, 6, 6, 20, 16);
			gp->Reset();
			lgb = new LinearGradientBrush(Point(6,6), Point(24,24), Color::FromArgb(100,100,100), Color::Black);
			gp->AddArc(10, 9, 12, 10, 0, 180);
			gp->AddLine(22, 14, 22, 10);
			gp->AddArc(10, 4, 12, 10, 0, 180);
			gp->AddLine(11, 11, 11, 14);
			g->FillPath(lgb, gp);
			lgb = new LinearGradientBrush(Point(6,6), Point(24,24), Color::Black, Color::Silver);
			g->FillEllipse(lgb, 10, 4, 12, 10);
			// 
			// Laser Turret
			//
			t3 = new Bitmap(32, 32);
			g = Graphics::FromImage(t3);
			gp = new GraphicsPath();
			lgb = new LinearGradientBrush(Point(0,0), Point(32,32), Color::FromArgb(120,70,70), Color::FromArgb(40,20,20));
			gp->AddArc(6, 12, 20, 16, 0, 180);
			gp->AddLine(26, 20, 26, 14);
			gp->AddArc(6, 6, 20, 16, 0, 180);
			gp->AddLine(7, 15, 7, 20);
			g->FillPath(lgb, gp);
			lgb = new LinearGradientBrush(Point(0,0), Point(32,32), Color::FromArgb(30,30,10), Color::Red);
			g->FillEllipse(lgb, 6, 6, 20, 16);
			//
			// Plasma Cannon
			//
			t4 = new Bitmap(32, 32);
			g = Graphics::FromImage(t4);
			gp->Reset();
			lgb = new LinearGradientBrush(Point(0,0), Point(32,32), Color::SteelBlue, Color::Black);
			gp->AddArc(6, 12, 20, 16, 0, 180);
			gp->AddLine(26, 20, 26, 14);
			gp->AddArc(6, 6, 20, 16, 0, 180);
			gp->AddLine(7, 15, 7, 20);
			g->FillPath(lgb, gp);
			lgb = new LinearGradientBrush(Point(0,0), Point(32,32), Color::Black, Color::SteelBlue);
			g->FillEllipse(lgb, 6, 6, 20, 16);
			gp->Reset();
			lgb = new LinearGradientBrush(Point(6,6), Point(24,24), Color::SteelBlue, Color::Black);
			gp->AddArc(10, 9, 12, 10, 0, 180);
			gp->AddLine(22, 14, 22, 10);
			gp->AddArc(10, 4, 12, 10, 0, 180);
			gp->AddLine(11, 11, 11, 14);
			g->FillPath(lgb, gp);
			lgb = new LinearGradientBrush(Point(4,4), Point(20,22), Color::SteelBlue, Color::Black);
			g->FillEllipse(lgb, 10, 4, 12, 10);
		}
	private:
		static Bitmap * t1, * t2, * t3, * t4;
	public:
		__property static Bitmap * get_MGTurret(){return t1;};
		__property static Bitmap * get_SniperTurret(){return t2;};
		__property static Bitmap * get_LaserTurret(){return t3;};
		__property static Bitmap * get_PlasmaCannon(){return t4;};
	};

	public __gc class Turret
	{
	public:
		Turret(void) // Creates a new undefined turret
		{
			t = -1;
			x = 0; y = 0; d = 0; r = 0; sd = 0; sdi = 0; a = 0; lv = 0;
		}
		Turret(int _t, int _x, int _y, bool warn) // Sets turret properties as default values
		{
			t = _t;
			x = _x;
			y = _y;
			a = 0; c = 0;
			lv = 1;
			switch (_t)
			{
			case -1: // Undefined
				d = 0;
				r = 0;
				sd = 0;
				sdi = 0;
				break;
			case 0: // MG Turret
				d = 3;
				r = 100;
				sd = 6;
				sdi = 6;
				sc = Color::OrangeRed;
				sw = 2.5;
				img = Turrets::MGTurret;
				break;
			case 1: // Sniper Turret
				d = 17;
				r = 200;
				sd = 28;
				sdi = 28;
				sc = Color::Firebrick;
				sw = 3;
				img = Turrets::SniperTurret;
				break;
			case 2: // Laser Turret
				d = 1;
				r = 120;
				sd = 0;
				sdi = 0;
				sc = Color::Orange;
				sw = 2;
				img = Turrets::LaserTurret;
				break;
			case 3: // Plasma Cannon
				d = 46;
				r = 140;
				sd = 35;
				sdi = 35;
				sc = Color::RoyalBlue;
				sw = 4.5;
				img = Turrets::PlasmaCannon;
				break;
			default:
				if (warn)
					MessageBox::Show(_t.ToString("Error creating turret of index #: Undefined index!"), "7 Towers TD", MessageBoxButtons::OK, MessageBoxIcon::Error);
				d = 0;
				r = 0;
				sd = 0;
				sdi = 0;
				t = -1; // Actually undefine it, otherwise this'll produce a runtime error.
				break;
			}
		}
	private:
		char t, lv;
		short d, x, y;
		unsigned c;
		unsigned short r, sd, sdi;
		float sw;
		double a;
		Bitmap * img;
		Color sc;
	public: 
		// Read/write properties
		__property char get_Type(){return t;};
		__property short get_Damage(){return d;};
		__property short get_X(){return x;}; // Note the X/Y properties mean different things to enemies.
		__property short get_Y(){return y;};
		__property unsigned short get_Range(){return r;};
		__property unsigned short get_ShotDelay(){return sdi;};
		__property unsigned short get_CurrentDelay(){return sd;};
		__property double get_Angle(){return a;};
		__property char get_Level(){return lv;};
		__property Bitmap * get_Image(){return img;};
		__property Color get_ShotColor(){return sc;};
		__property unsigned get_ShotCount(){return c;};
		__property float get_ShotWidth(){return sw;};
		__property void set_Type(char _t){t = _t;};
		__property void set_Damage(short _d){d = _d;};
		__property void set_X(short _x){x = _x;};
		__property void set_Y(short _y){y = _y;};
		__property void set_Range(unsigned short _r){r = _r;};
		__property void set_ShotDelay(unsigned short _sdi){sdi = _sdi;};
		__property void set_CurrentDelay(unsigned short _sd){sd = _sd;};
		__property void set_Angle(double _a){a = _a;};
		__property void set_Level(char _lv){lv = _lv;};
		__property void set_Image(Bitmap * _img){img = _img;};
		__property void set_ShotColor(Color _sc){sc = _sc;};
		__property void set_ShotCount(unsigned _c){c = _c;};
		__property void set_ShotWidth(float _sw){sw = _sw;};
		// Read-only properties
		__property String * get_Name()
		{
			if (t == -1)
				return Strings::Undefined;
			else if (lv < MASTER)
				return Strings::Turret[t];
			else
				return Strings::MasterTurret[t];
		}
		// Internal methods
	private:
		int InternalSell(int funds)
		{
			switch (this->Type)
			{
			case 0: // MG Turret
				switch (this->Level)
				{		
				case 1: return funds + MG_SELL1;
				case 2: return funds + MG_SELL2;
				case 3: return funds + MG_SELL3;
				case 4: return funds + MG_SELL4;
				case 5: return funds + MG_SELL5;
				default: return funds;
				}
			case 1: // Sniper Turret
				switch (this->Level)
				{
				case 1: return funds + SN_SELL1;
				case 2: return funds + SN_SELL2;
				case 3: return funds + SN_SELL3;
				case 4: return funds + SN_SELL4;
				case 5: return funds + SN_SELL5;
				default: return funds;
				}
			case 2: // Laser Turret
				switch (this->Level)
				{
				case 1: return funds + LA_SELL1;
				case 2: return funds + LA_SELL2;
				case 3: return funds + LA_SELL3;
				case 4: return funds + LA_SELL4;
				case 5: return funds + LA_SELL5;
				default: return funds;
				}
			case 3: // Plasma Turret
				switch (this->Level)
				{
				case 1: return funds + PL_SELL1;
				case 2: return funds + PL_SELL2;
				case 3: return funds + PL_SELL3;
				case 4: return funds + PL_SELL4;
				case 5: return funds + PL_SELL5;
				default: return funds;
				}
			default:
				return funds;
			}
		}
		// External methods
	public:
		int Upgrade(int funds)
		{
			switch (this->Type)
			{
			case 0: // MG Turret
				switch (this->Level)
				{
				case 1:
					if (funds < MG_UP1)
						return -1;
					funds -= MG_UP1;
					this->set_Damage(4);
					this->set_Range(104);
					Level++;
					return funds;
				case 2:
					if (funds < MG_UP2)
						return -1;
					funds -= MG_UP2;
					this->set_Damage(5);
					this->set_ShotDelay(5);
					this->set_Range(108);
					Level++;
					return funds;
				case 3:
					if (funds < MG_UP3)
						return -1;
					funds -= MG_UP3;
					this->set_Damage(6);
					this->set_Range(113);
					this->set_ShotDelay(4);
					Level++;
					return funds;
				case 4:
					if (funds < MG_UP4)
						return -1;
					funds -= MG_UP4;
					this->set_Damage(8);
					this->set_Range(118);
					this->set_ShotDelay(2);
					Level++;
					return funds;
				}
			case 1: // Sniper Turret
				switch (this->Level)
				{
				case 1:
					if (funds < SN_UP1)
						return -1;
					funds -= SN_UP1;
					this->set_Damage(21);
					this->set_ShotDelay(26);
					this->set_Range(208);
					Level++;
					return funds;
				case 2:
					if (funds < SN_UP2)
						return -1;
					funds -= SN_UP2;
					this->set_Damage(26);
					this->set_ShotDelay(24);
					this->set_Range(216);
					Level++;
					return funds;
				case 3:
					if (funds < SN_UP3)
						return -1;
					funds -= SN_UP3;
					this->set_Damage(33);
					this->set_Range(224);
					this->set_ShotDelay(21);
					Level++;
					return funds;
				case 4:
					if (funds < SN_UP4)
						return -1;
					funds -= SN_UP4;
					this->set_Damage(40);
					this->set_Range(999);
					this->set_ShotDelay(19);
					Level++;
					return funds;
				}
			case 2: // Laser Turret
				switch (this->Level)
				{
				case 1:
					if (funds < LA_UP1)
						return -1;
					funds -= LA_UP1;
					this->set_Damage(2);
					this->set_Range(123);
					Level++;
					return funds;
				case 2:
					if (funds < LA_UP2)
						return -1;
					funds -= LA_UP2;
					this->set_Damage(3);
					this->set_Range(126);
					Level++;
					return funds;
				case 3:
					if (funds < LA_UP3)
						return -1;
					funds -= LA_UP3;
					this->set_Damage(4);
					this->set_Range(130);
					Level++;
					return funds;
				case 4:
					if (funds < LA_UP4)
						return -1;
					funds -= LA_UP4;
					this->set_Damage(2);
					this->set_Range(142);
					this->set_ShotColor(Color::Lime);
					Level++;
					return funds;
				}
			case 3: // Plasma Turret
				switch (this->Level)
				{
				case 1:
					if (funds < PL_UP1)
						return -1;
					funds -= PL_UP1;
					this->set_Damage(71);
					this->set_Range(150);
					this->set_ShotDelay(33);
					Level++;
					return funds;
				case 2:
					if (funds < PL_UP2)
						return -1;
					funds -= PL_UP2;
					this->set_Damage(98);
					this->set_Range(160);
					this->set_ShotDelay(31);
					Level++;
					return funds;
				case 3:
					if (funds < PL_UP3)
						return -1;
					funds -= PL_UP3;
					this->set_Damage(137);
					this->set_Range(168);
					this->set_ShotDelay(29);
					Level++;
					return funds;
				case 4:
					if (funds < PL_UP4)
						return -1;
					funds -= PL_UP4;
					this->set_Damage(240);
					this->set_Range(175);
					this->set_ShotDelay(28);
					this->set_ShotWidth(5);
					Level++;
					return funds;
				}
			default:
				return -1;
			}
		}
	public:
		int Sell(int funds)
		{
			funds = InternalSell(funds);
			this->Type = -1;
			return funds;
		}
		__property int get_SellValue()
		{
			return InternalSell(0);
		}
		__property int get_UpgradeCost()
		{
			switch (this->Type)
			{
			case 0: // MG Turret
				switch (this->Level)
				{
				case 1: return MG_UP1;
				case 2: return MG_UP2;
				case 3: return MG_UP3;
				case 4: return MG_UP4;
				default: return 0;
				}
			case 1: // Sniper Turret
				switch (this->Level)
				{
				case 1: return SN_UP1;
				case 2: return SN_UP2;
				case 3: return SN_UP3;
				case 4: return SN_UP4;
				default: return 0;
				}
			case 2: // Laser Turret
				switch (this->Level)
				{
				case 1: return LA_UP1;
				case 2: return LA_UP2;
				case 3: return LA_UP3;
				case 4: return LA_UP4;
				default: return 0;
				}
			case 3: // Plasma Turret
				switch (this->Level)
				{
				case 1: return PL_UP1;
				case 2: return PL_UP2;
				case 3: return PL_UP3;
				case 4: return PL_UP4;
				default: return 0;
				}
			default:
				return 0;
			}
		}
		static int BuildCost(int _t)
		{
			switch (_t)
			{
			case 0: return MG_COST;
			case 1: return SN_COST;
			case 2: return LA_COST;
			case 3: return PL_COST;
			default: return 0;
			}
		}
	};
};