using namespace System;
using namespace System::IO;
using namespace System::Text;

namespace RiversTD
{
	public __gc class Wave
	{
	public:
		Wave(int count, int _t, int HP, int speed, int trigger_t, int gold, const char m __gc[,])
		{
			es = new Enemy * __gc[count];
			ec = count;
			t = _t;
			for (int i = 0; i < count; i++)
				es[i] = new Enemy(_t, HP, speed, trigger_t, gold, m);
		}
	private:
		Enemy * es __gc[];
		int ec, t;
	public:
		__property Enemy * get_EnemyList()__gc[]{return es;};
		__property int get_Count(){return ec;};
		__property int get_Type(){return t;};
		__property void set_EnemyList(Enemy * _e __gc[]){es = _e;};
		__property void set_Count(int _c){ec = _c;};
		__property void set_Type(int _t){t = _t;};
	};
	public __gc class WaveSequence
	{
	public:
		WaveSequence(int length)
		{
			try
			{
				_w = new Wave * __gc[length];
				c = 0;
			}
			catch (Exception *)
			{
				c = 0;
			}
		}
		WaveSequence(void)
		{
			c = 0;
		}
	private:
		Wave * _w __gc[];
		int c;
	public:
		__property int get_Count(){return c;};
		void AddWave(Wave * wv)
		{
			_w->set_Item(c,wv);
			c++;
		}
		Wave * GetWave(int i)
		{
			return _w[i];
		}
	};
	public __gc class Waves
	{
	public:
		Waves(void)
		{
			ws = new Wave * __gc[WMAX];
		}
	private:
		static char p1_map1 __gc[,] = Maps::ToPaths(Maps::map1);
		static char p2_map1 __gc[,] = Maps::ToPaths(Maps::map1, 2);
		static char p1_map2 __gc[,] = Maps::ToPaths(Maps::map2);
		static char p2_map2 __gc[,] = Maps::ToPaths(Maps::map2, 2);
		static Wave * ws __gc[];
		//__property static Wave * get_Wave1(){return w1;};//__property static Wave * get_Wave2(){return w2;};//__property static Wave * get_Wave3(){return w3;};//__property static Wave * get_Wave4(){return w4;};
	public:
		__property static WaveSequence * get_Sequence(char sn)
		{
			ws = new Wave * __gc[WMAX];
			WaveSequence * s;
			switch (sn)
			{
			case 1:
				s = new WaveSequence(20);
				break;
			case 2:
				s = new WaveSequence(30);
				break;
			default:
				sn = 1;
				s = new WaveSequence(20);
				break;
			}
			InitializeWaves(sn);
			for (int i = 0; i < 20; i++)
				s->AddWave(ws[i]);
			return s;
		}
		__property WaveSequence * get_FileSequence(String * filename, char map __gc[], bool CurrentDirectory)
		{
			int length = InternalFromFile(filename, map, CurrentDirectory);
			WaveSequence * temp = new WaveSequence(length);
			for (int i = 0; i < length; i++)
				temp->AddWave(ws[i]);
			return temp;
		}
		__property int get_FileSequenceCount(String * filename, char map __gc[])
		{
			int length = InternalFromFile(filename, map);
			return length;
		}
		static void InitializeWaves(char sn)
		{	//  ws[ n] = new Wave(count,type,maxHP,spd.,trig.,gold,  paths );
			switch (sn)
			{
			case 1:
				ws[00] = new Wave(  10 ,  0,  8  ,  10 ,  30 ,  1 , p1_map1);
				ws[01] = new Wave(  14 ,  0,  10 ,  11 ,  24 ,  1 , p1_map1);
				ws[02] = new Wave(  13 ,  2,  11 ,  7  ,  22 ,  2 , p1_map1);
				ws[03] = new Wave(   8 ,  1,  17 ,  16 ,  15 ,  2 , p2_map1);
				ws[04] = new Wave(  15 ,  0,  18 ,  11 ,  19 ,  2 , p1_map1);
				ws[05] = new Wave(  32 ,  3,  5  ,  6  ,  3  ,  1 , p1_map1);
				ws[06] = new Wave(  12 ,  2,  19 ,  7  ,  20 ,  2 , p1_map1);
				ws[07] = new Wave(  10 ,  5,  24 ,  5  ,  10 ,  2 , p1_map1);
				ws[ 8] = new Wave(  19 ,  0,  29 ,  10 ,  25 ,  2 , p1_map1);
				ws[ 9] = new Wave(   7 ,  4,  22 ,  12 ,  14 ,  3 , p2_map1);
				ws[10] = new Wave(  10 ,  1,  45 ,  18 ,  20 ,  3 , p1_map1);
				ws[11] = new Wave(  14 ,  0,  38 ,  10 ,  18 ,  3 , p1_map1);
				ws[12] = new Wave(  42 ,  3,  9  ,  7  ,  4  ,  1 , p1_map1);
				ws[13] = new Wave(  18 ,  5,  49 ,  5  ,  22 ,  2 , p1_map1);
				ws[14] = new Wave(  15 ,  2,  38 ,  6  ,  9  ,  3 , p2_map1);
				ws[15] = new Wave(   9 ,  1, 102 ,  16 ,  19 ,  4 , p1_map1);
				ws[16] = new Wave(  16 ,  4,  47 ,  14 ,  30 ,  3 , p1_map1);
				ws[17] = new Wave(  55 ,  3,  11 ,  6  ,  5  ,  2 , p1_map1);
				ws[18] = new Wave(   6 ,  1, 285 ,  18 ,  38 ,  8 , p1_map1);
				ws[19] = new Wave(   1 ,  6, 1800,  26 ,  50 , 50 , p2_map1);
				break;
			case 2: // TODO: These waves and paths. Map can now be made using the Map Editor
				ws[00] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				ws[01] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				ws[02] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				ws[03] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				ws[04] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				ws[05] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				ws[06] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				ws[07] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				ws[ 8] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				ws[ 9] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				ws[10] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				ws[11] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				ws[12] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				ws[13] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				ws[14] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				ws[15] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				ws[16] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				ws[17] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				ws[18] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				ws[19] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				ws[20] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				ws[21] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				ws[22] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				ws[23] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				ws[24] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				ws[25] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				ws[26] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				ws[27] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				ws[28] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				ws[29] = new Wave(  14 ,  0,  11 ,  10 ,  30 ,  2 , p1_map2);
				break;
			}
		}
	private:
		// Funnily enough although InternalFromFile(String*,char[],bool) has return type int,
		// it actually reads in all waves and paths from the specified file as well.
		int InternalFromFile(String * filename, char map __gc[], bool CurrentDirectory)
		{
			FileStream * fs;
			StreamReader * sr;
			try
			{
				if (CurrentDirectory)
					filename = String::Concat(Environment::CurrentDirectory, "\\", filename);
				fs = new FileStream(filename, FileMode::Open, FileAccess::Read);
				sr = new StreamReader(fs, Encoding::ASCII);
				String * file = sr->ReadToEnd();
				sr->Close();
				String * data __gc[] = new String * __gc[SSMAX];
				data = file->Split(S","->ToCharArray(), SSMAX);
				int n __gc[] = new int __gc[data->Length];
				for (int i = 0; i < n->Length; i++)
					n[i] = Convert::ToInt32(data[i]);
				// Now that all that is over and done with, the program is left with a useful data array.
				// (n[0] is the wave count.)
				for (int i = 0; i < n[0]; i++)
				{
					if (n[i*7+7] == 0)
						ws[i] = new Wave(n[i*7+1], n[i*7+2], n[i*7+3], n[i*7+4], n[i*7+5], n[i*7+6], Maps::ToPaths(map));
					else
						ws[i] = new Wave(n[i*7+1], n[i*7+2], n[i*7+3], n[i*7+4], n[i*7+5], n[i*7+6], Maps::ToPaths(map, n[i*7+7]));
				}
				return n[0];
			}
			catch (Exception * ex)
			{
				MessageBox::Show(ex->Message, "Load failed", MessageBoxButtons::OK, MessageBoxIcon::Error);
				try
				{
					sr->Close();
				}
				catch (Exception *)
				{
					return -1;
				}
				return -1;
			}
		}
		int InternalFromFile(String * filename, char map __gc[])
		{
			FileStream * fs;
			StreamReader * sr;
			try
			{
				fs = new FileStream(filename, FileMode::Open, FileAccess::Read);
				sr = new StreamReader(fs, Encoding::ASCII);
				String * file = sr->ReadToEnd();
				sr->Close();
				String * data __gc[] = new String * __gc[SSMAX];
				data = file->Split(S","->ToCharArray(), SSMAX);
				int n __gc[] = new int __gc[data->Length];
				for (int i = 0; i < n->Length; i++)
					n[i] = Convert::ToInt32(data[i]);
				// Now that all that is over and done with, the program is left with a useful data array.
				return n[0];
			}
			catch (Exception * ex)
			{
				MessageBox::Show(ex->Message, "Load failed", MessageBoxButtons::OK, MessageBoxIcon::Error);
				try
				{
					sr->Close();
				}
				catch (Exception *)
				{
					return -1;
				}
				return -1;
			}
		}
	};	
};