using namespace System;
using namespace System::Drawing;
using namespace System::Drawing::Drawing2D;
using namespace System::Windows::Forms;

namespace RiversTD
{
	public __value struct EnemyColors
	{
		static Color lc[] = {Color::LightGray, Color::Black};
		static Color lc2[] = {Color::Silver, Color::Black};
		static Color lc3[] = {Color::DarkGray, Color::Black};
		static Color lc4[] = {Color::Gray, Color::Black};
	};
	public __gc class Enemy
	{
	public:
		Enemy(void) // Creates a new undefined enemy
		{
			t = -1;
			hp = 0; s = 0; d = 0; x = 0; y = 0; ph = 0; pm = 0; pp = 0, sp = 0;
		}
		Enemy(int _t, int _x, int _y, int _d) // Sets enemy properties as default values
		{
			t = _t;
			hp = 0; s = 0; d = _d; x = _x; y = _y; ph = 0; pm = 0; pp = 0, sp = 0;
			InitializeEnemyImages(_t);
		}
		Enemy(unsigned _t, int _hp, int _s, int _tt, int _gg, char paths __gc[,])
		{
			d = 0; x = 0; y = 0;
			ph = 0; pp = 4; sp = 0; pm = 4;
			hp = _hp; s = _s; tt = _tt; gg = _gg;
			hpi = hp; si = s;
			name = Strings::Enemy[_t];
			InitializeEnemyImages(_t);
			SetPath(paths);
			// path[0] (i.e. path length) is used in GameLoop rather than here. (It feels more at home.)
			x = path[1]*GS;
			y = path[2]*GS;
			d = path[3];
			t = -1; // Doesn't this defeat the object of assigning a type...?
		}
	private:
		int hp, t, d, pp, sp, tt, hpi, s, si, gg;
		double x, y, ph, pm;
		char path __gc[];
		Bitmap * img __gc[];
		static Random * r = new Random();
		String * name;
	public:
		// Read/write properties
		__property int get_HP()
		{
			if (hp > 0)
				return hp;
			else
				return 0;
		}
		__property int get_Speed(){return s;};
		__property int get_Type(){return t;};
		__property int get_SpeedPhase(){return sp;};
		__property int get_Direction(){return d;};
		__property int get_PathPoint(){return pp;};
		__property int get_Gold(){return gg;};
		__property double get_X(){return x;}; // Note the X/Y properties mean different things to turrets.
		__property double get_Y(){return y;};
		__property Bitmap * get_Image(int _i){return img[_i];};
		__property double get_Phase(){return ph;};
		__property double get_MaxPhase(){return pm;};
		__property int get_Trigger(){return tt;};
		__property String * get_Name(){return name;};
		__property void set_HP(int _hp)
		{
			if (_hp > hpi)
				hp = hpi;
			else if (_hp > 0)
				hp = _hp;
			else
			{
				hp = 0;
				t = -1;
			}
		}
		__property void set_Phase(double _ph)
		{
			if (_ph >= pm)
				_ph -= pm;
			else if (_ph < 0)
				_ph += pm;
			ph = _ph;
		}
		__property void set_Speed(int _s){s = _s;};
		__property void set_Type(int _t){t = _t;};
		__property void set_SpeedPhase(int _sp){sp = _sp;};
		__property void set_Direction(int _d){d = _d;};
		__property void set_PathPoint(int _pp){pp = _pp;};
		__property void set_Gold(int _gg){gg = _gg;};
		__property void set_X(double _x){x = _x;};
		__property void set_Y(double _y){y = _y;};
		__property void set_MaxPhase(double _pm){pm = _pm;};
		__property void set_Trigger(int _tt){tt = _tt;};
		__property void set_Image(int _i, Bitmap * _img){img[_i] = _img;};
		__property void set_Name(String * _name){name = _name;};
		// Read-only properties
		__property char get_Path(int _i){return path[_i];};
		__property int get_InitialSpeed(){return si;};
		__property Region * get_Region()
		{
			GraphicsPath * gp = new GraphicsPath();
			gp->AddEllipse(X+8, Y+8, 16, 16);
			// This rectangle could also be defined using GS, but the image is defined using these numbers.
			return new Drawing::Region(gp);
		}
		
		// Public methods
		void InitializeEnemyImages(int _t)
		{
			img = new Bitmap * __gc[IMAX];
			for (int i = 0; i < 6; i++)
				this->img[i] = new Bitmap(32,32);
			Graphics * g;
			Drawing::Rectangle rect = Drawing::Rectangle(8, 8, 16, 16);
			Drawing::Rectangle rectS;
			Drawing::Rectangle rectL = Drawing::Rectangle(4, 4, 24, 24);
			LinearGradientBrush * lgb;
			switch (_t)
			{
			case ARMOUR:
				lgb = new LinearGradientBrush(rect, Color::Gainsboro, Color::Black, LinearGradientMode::ForwardDiagonal);
				g = Graphics::FromImage(img[0]);
				g->FillEllipse(lgb, rect);
				g->DrawEllipse(Pens::Black, rect);
				g = Graphics::FromImage(img[1]);
				lgb = new LinearGradientBrush(rect, Color::LightGray, Color::Black, LinearGradientMode::ForwardDiagonal);
				g->FillEllipse(lgb, rect);
				g->DrawEllipse(Pens::Black, rect);
				g = Graphics::FromImage(img[2]);
				lgb = new LinearGradientBrush(rect, Color::Silver, Color::Black, LinearGradientMode::ForwardDiagonal);
				g->FillEllipse(lgb, rect);
				g->DrawEllipse(Pens::Black, rect);
				g = Graphics::FromImage(img[3]);
				lgb = new LinearGradientBrush(rect, Color::DarkGray, Color::Black, LinearGradientMode::ForwardDiagonal);
				g->FillEllipse(lgb, rect);
				g->DrawEllipse(Pens::Black, rect);
				g = Graphics::FromImage(img[4]);
				lgb = new LinearGradientBrush(rect, Color::Silver, Color::Black, LinearGradientMode::ForwardDiagonal);
				g->FillEllipse(lgb, rect);
				g->DrawEllipse(Pens::Black, rect);
				g = Graphics::FromImage(img[5]);
				lgb = new LinearGradientBrush(rect, Color::LightGray, Color::Black, LinearGradientMode::ForwardDiagonal);
				g->FillEllipse(lgb, rect);
				g->DrawEllipse(Pens::Black, rect);
			    break;
			case SWARM:
				rectS = Drawing::Rectangle(10, 10, 12, 12);
				g = Graphics::FromImage(img[0]);
				g->FillEllipse(Brushes::DarkViolet, rectS);
				g = Graphics::FromImage(img[1]);
				g->FillEllipse(Brushes::BlueViolet, rectS);
				g = Graphics::FromImage(img[2]);
				g->FillEllipse(Brushes::MediumPurple, rectS);
				g = Graphics::FromImage(img[3]);
				g->FillEllipse(Brushes::MediumSlateBlue, rectS);
				g = Graphics::FromImage(img[4]);
				g->FillEllipse(Brushes::MediumPurple, rectS);
				g = Graphics::FromImage(img[5]);
				g->FillEllipse(Brushes::BlueViolet, rectS);
			    break;
			case REGEN:
				g = Graphics::FromImage(img[0]);
				g->FillPie(Brushes::YellowGreen, rect, 0, 90);
				g->FillPie(Brushes::LimeGreen, rect, 90, 90);
				g->FillPie(Brushes::ForestGreen, rect, 180, 90);
				g->FillPie(Brushes::OliveDrab, rect, 270, 90);
				g->DrawLine(Pens::Green, 8, 16, 24, 16);
				g->DrawLine(Pens::Green, 16, 8, 16, 24);
				g = Graphics::FromImage(img[1]);
				g->FillPie(Brushes::YellowGreen, rect, 90, 90);
				g->FillPie(Brushes::LimeGreen, rect, 180, 90);
				g->FillPie(Brushes::ForestGreen, rect, 270, 90);
				g->FillPie(Brushes::OliveDrab, rect, 0, 90);
				g->DrawLine(Pens::Green, 8, 16, 24, 16);
				g->DrawLine(Pens::Green, 16, 8, 16, 24);
				g = Graphics::FromImage(img[2]);
				g->FillPie(Brushes::YellowGreen, rect, 180, 90);
				g->FillPie(Brushes::LimeGreen, rect, 270, 90);
				g->FillPie(Brushes::ForestGreen, rect, 0, 90);
				g->FillPie(Brushes::OliveDrab, rect, 90, 90);
				g->DrawLine(Pens::Green, 8, 16, 24, 16);
				g->DrawLine(Pens::Green, 16, 8, 16, 24);
				g = Graphics::FromImage(img[3]);
				g->FillPie(Brushes::YellowGreen, rect, 270, 90);
				g->FillPie(Brushes::LimeGreen, rect, 0, 90);
				g->FillPie(Brushes::ForestGreen, rect, 90, 90);
				g->FillPie(Brushes::OliveDrab, rect, 180, 90);
				g->DrawLine(Pens::Green, 8, 16, 24, 16);
				g->DrawLine(Pens::Green, 16, 8, 16, 24);
				break;
			case ERRATIC:
				g = Graphics::FromImage(img[0]);
				g->FillEllipse(Brushes::Aquamarine, rect);
				g = Graphics::FromImage(img[1]);
				g->FillEllipse(Brushes::Turquoise, rect);
				g = Graphics::FromImage(img[2]);
				g->FillEllipse(Brushes::MediumAquamarine, rect);
				g = Graphics::FromImage(img[3]);
				g->FillEllipse(Brushes::DarkTurquoise, rect);
				g = Graphics::FromImage(img[4]);
				g->FillEllipse(Brushes::MediumAquamarine, rect);
				g = Graphics::FromImage(img[5]);
				g->FillEllipse(Brushes::Turquoise, rect);
			    break;
			case BOSS:
				lgb = new LinearGradientBrush(rectL, Color::Gainsboro, Color::Black, LinearGradientMode::ForwardDiagonal);
				g = Graphics::FromImage(img[0]);
				g->FillEllipse(lgb, rectL);
				g->DrawEllipse(Pens::Black, rectL);
				g = Graphics::FromImage(img[1]);
				lgb = new LinearGradientBrush(rectL, Color::LightGray, Color::Black, LinearGradientMode::ForwardDiagonal);
				g->FillEllipse(lgb, rectL);
				g->DrawEllipse(Pens::Black, rectL);
				g = Graphics::FromImage(img[2]);
				lgb = new LinearGradientBrush(rectL, Color::Silver, Color::Black, LinearGradientMode::ForwardDiagonal);
				g->FillEllipse(lgb, rectL);
				g->DrawEllipse(Pens::Black, rectL);
				g = Graphics::FromImage(img[3]);
				lgb = new LinearGradientBrush(rectL, Color::DarkGray, Color::Black, LinearGradientMode::ForwardDiagonal);
				g->FillEllipse(lgb, rectL);
				g->DrawEllipse(Pens::Black, rectL);
				g = Graphics::FromImage(img[4]);
				lgb = new LinearGradientBrush(rectL, Color::Silver, Color::Black, LinearGradientMode::ForwardDiagonal);
				g->FillEllipse(lgb, rectL);
				g->DrawEllipse(Pens::Black, rectL);
				g = Graphics::FromImage(img[5]);
				lgb = new LinearGradientBrush(rectL, Color::LightGray, Color::Black, LinearGradientMode::ForwardDiagonal);
				g->FillEllipse(lgb, rectL);
				g->DrawEllipse(Pens::Black, rectL);
			    break;
			case SPRINT_BOSS:
				g = Graphics::FromImage(img[0]);
				g->FillEllipse(Brushes::Red, rectL);
				g = Graphics::FromImage(img[1]);
				g->FillEllipse(Brushes::OrangeRed, rectL);
				g = Graphics::FromImage(img[2]);
				g->FillEllipse(Brushes::DarkOrange, rectL);
				g = Graphics::FromImage(img[3]);
				g->FillEllipse(Brushes::Orange, rectL);
				g = Graphics::FromImage(img[4]);
				g->FillEllipse(Brushes::DarkOrange, rectL);
				g = Graphics::FromImage(img[5]);
				g->FillEllipse(Brushes::OrangeRed, rectL);
			    break;
			case REGEN_BOSS:
				g = Graphics::FromImage(img[0]);
				g->FillPie(Brushes::YellowGreen, rectL, 0, 90);
				g->FillPie(Brushes::LimeGreen, rectL, 90, 90);
				g->FillPie(Brushes::ForestGreen, rectL, 180, 90);
				g->FillPie(Brushes::OliveDrab, rectL, 270, 90);
				g->DrawLine(Pens::Green, 4, 16, 28, 16);
				g->DrawLine(Pens::Green, 16, 4, 16, 28);
				g = Graphics::FromImage(img[1]);
				g->FillPie(Brushes::YellowGreen, rectL, 90, 90);
				g->FillPie(Brushes::LimeGreen, rectL, 180, 90);
				g->FillPie(Brushes::ForestGreen, rectL, 270, 90);
				g->FillPie(Brushes::OliveDrab, rectL, 0, 90);
				g->DrawLine(Pens::Green, 4, 16, 28, 16);
				g->DrawLine(Pens::Green, 16, 4, 16, 28);
				g = Graphics::FromImage(img[2]);
				g->FillPie(Brushes::YellowGreen, rectL, 180, 90);
				g->FillPie(Brushes::LimeGreen, rectL, 270, 90);
				g->FillPie(Brushes::ForestGreen, rectL, 0, 90);
				g->FillPie(Brushes::OliveDrab, rectL, 90, 90);
				g->DrawLine(Pens::Green, 4, 16, 28, 16);
				g->DrawLine(Pens::Green, 16, 4, 16, 28);
				g = Graphics::FromImage(img[3]);
				g->FillPie(Brushes::YellowGreen, rectL, 270, 90);
				g->FillPie(Brushes::LimeGreen, rectL, 0, 90);
				g->FillPie(Brushes::ForestGreen, rectL, 90, 90);
				g->FillPie(Brushes::OliveDrab, rectL, 180, 90);
				g->DrawLine(Pens::Green, 4, 16, 28, 16);
				g->DrawLine(Pens::Green, 16, 4, 16, 28);
				break;
			case ERRATIC_BOSS:
				g = Graphics::FromImage(img[0]);
				g->FillEllipse(Brushes::Aquamarine, rectL);
				g = Graphics::FromImage(img[1]);
				g->FillEllipse(Brushes::Turquoise, rectL);
				g = Graphics::FromImage(img[2]);
				g->FillEllipse(Brushes::MediumAquamarine, rectL);
				g = Graphics::FromImage(img[3]);
				g->FillEllipse(Brushes::DarkTurquoise, rectL);
				g = Graphics::FromImage(img[4]);
				g->FillEllipse(Brushes::MediumAquamarine, rectL);
				g = Graphics::FromImage(img[5]);
				g->FillEllipse(Brushes::Turquoise, rectL);
			    break;
			default: // Normal enemies will look like this
				g = Graphics::FromImage(img[0]);
				g->FillEllipse(Brushes::Red, rect);
				g = Graphics::FromImage(img[1]);
				g->FillEllipse(Brushes::OrangeRed, rect);
				g = Graphics::FromImage(img[2]);
				g->FillEllipse(Brushes::DarkOrange, rect);
				g = Graphics::FromImage(img[3]);
				g->FillEllipse(Brushes::Orange, rect);
				g = Graphics::FromImage(img[4]);
				g->FillEllipse(Brushes::DarkOrange, rect);
				g = Graphics::FromImage(img[5]);
				g->FillEllipse(Brushes::OrangeRed, rect);
			    break;
			}
				
			for (int i = 0; i < 6; i++)
				img[i]->MakeTransparent(Color::White);
		}
		void Draw(Graphics * g, Drawing::Rectangle rect)
		{
			g->DrawImageUnscaled(img[(int)ph], rect);
		}
		void Draw(Graphics * g, int _x, int _y)
		{
			g->DrawImageUnscaled(img[(int)ph], _x, _y);
		}
		void Draw(Graphics * g)
		{
			g->DrawImageUnscaled(this->img[(int)ph], x, y);
		}
		void SetPath(char m __gc[,])
		{
			path = new char __gc[m->GetLength(1)]; // Highest path length
			int pc = r->Next(0, m->GetLength(0)); // Path count
			for (int i = 0; i < m->GetLength(1); i++)
				path[i] = m[pc,i];
		}
		bool Intersects(Graphics * g, int mx, int my)
		{
			if (t == -1)
				return 0;
			Drawing::Region * re = this->Region;
			re->Intersect(RectangleF(mx-1, my-1, 3, 3));
			return !re->IsEmpty(g);
		}
	};
};