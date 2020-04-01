using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Windows::Forms;

namespace RiversTD
{
	public __gc __sealed class Maps
	{
	private:
		static const char temp __gc[] = // Template (blank) map
		{
		//  0/ 1/ 2/ 3/ 4/ 5/ 6/ 7/ 8/ 9/10/11/12/13/14/15/16/17/18/19/20/21/22
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 1
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 2
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 3
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 4
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 5
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 6
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 7
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 8
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 9
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 10
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 11
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 12
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 13
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 14
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 15
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 16
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 17
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 18
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 19

			0
		};
	public:
		static const int MW = 23; // Map width
		static const int MH = 20; // Map height
		static char map1 __gc[] =
		{
		//  0/ 1/ 2/ 3/ 4/ 5/ 6/ 7/ 8/ 9/10/11/12/13/14/15/16/17/18/19/20/21/22
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0
			0, 0, 2, 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 1
			0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 2
			0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 3
			0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 4
			0, 0, 1, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 2, 1,10, 0, 0, 0, 0, 0, 0, 0, // 5
			0, 0, 2, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 6
			0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 7
			0, 0, 2, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 8
			0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 9
			0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 10
			0, 0, 2, 2, 1, 2, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 11
			0, 0, 1, 0, 0, 1, 0, 0, 0, 2, 1, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 12
			0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 13
			0, 0, 5, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 14
			0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 15
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 16
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 17
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 18
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 19

			5,
		   15, 4, 1, 2, 3, 3, 4, 4, 4, 1, 1, 2,12, 3,-1,
		   14, 4, 1, 2, 3, 3, 4, 4, 4, 1, 4,15, 5,-1,
		   14, 2,14, 1, 4, 1, 4, 3, 4, 4, 1,13,10,-1,
		   13, 5,15, 1, 2, 1, 4, 3, 4, 3,11,15,-1,
		   15, 7, 5, 3, 2, 3, 4, 4, 3, 4, 4, 1,13,10,-1
		};
		static char map2 __gc[] =
		{
		//  0/ 1/ 2/ 3/ 4/ 5/ 6/ 7/ 8/ 9/10/11/12/13/14/15/16/17/18/19/20/21/22
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 0
			0, 0, 0, 0, 0, 0, 0, 4, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, // 1
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, // 2
			0, 0, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, // 3
			0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 4
			0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 5
			0, 0, 1, 0, 1, 0, 0, 0, 2, 1, 1, 2, 0, 8, 1, 1, 1, 1, 2, 0, 0, 0, 0, // 6
			0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, // 7
			0, 0, 1, 0, 1, 0, 2, 1, 2, 0, 0, 2, 1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, // 8
			0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, // 9
			0, 0, 1, 0, 1, 0, 1, 0, 2, 1, 1, 2, 0, 8, 1, 1, 1, 1, 2, 0, 0, 0, 0, // 10
			0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 11
			0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 12
			0, 0, 5, 0, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 13
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 14
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 15
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 16
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 17
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 18
			0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // 19

			6,
		   19, 7, 1, 4, 3, 2, 3, 4, 1, 4, 1, 4, 3, 4, 3, 2,13,10,-1,
		   19, 7, 1, 4, 3, 2, 3, 4, 1, 4, 3, 4, 1, 4, 1, 2,13, 6,-1,
		   20,18, 3, 1, 2, 3, 2, 3, 4, 1, 4, 1, 4, 3, 4, 3, 2,13,10,-1,
		   20,18, 3, 1, 2, 3, 2, 3, 4, 1, 4, 3, 4, 1, 4, 1, 2,13, 6,-1,
		   18, 2,13, 1, 4, 3, 4, 1, 4, 1, 4, 3, 4, 3, 2,13,10,-1,
		   18, 2,13, 1, 4, 3, 4, 1, 4, 3, 4, 1, 4, 1, 2,13, 6,-1
		};
		static char map3 __gc[] = temp;
		static char map4 __gc[] = temp;
		static char map5 __gc[] = temp;
		static char map6 __gc[] = temp;
		// Path format: 
		// Path count -
		// Path 1 Length(+6) - Start X - Start Y - Start D - Turn 1 - Turn 2 - Turn ... - End X - End Y - -1
		// Path 2 ...
		static char FromFile(String * filename, bool CurrentDirectory) __gc[]
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
				char n __gc[] = new char __gc[data->Length];
				for (int i = 0; i < n->Length; i++)
					n[i] = Convert::ToSByte(data[i]);
				return n;
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
					return new char __gc[1];
				}
				return new char __gc[1];
			}
		}
		static char ToGrid(char m __gc[])__gc[,]
		{
			int i;
			try
			{
				char grid __gc[,] = new char __gc[MW,MH];
				for (i = 0; i < MW; i++)
				{
					for (int j = 0; j < MH; j++)
						grid[i,j] = m[j*MW+i];
				}
				return grid;
			}
			catch (Exception * ex)
			{
				MessageBox::Show(String::Concat(ex->ToString(), "\n\ni = ", i.ToString()), "7 Rivers TD", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return new char __gc[MW,MH];
			}
		}
		static char ToPaths(char m __gc[])__gc[,] // Explanations are in the more confusing version
		{
			int i, pn, pc, ml;
			try
			{
				pc = m[MW*MH];
				if (pc == 0)
					throw new Exception("Path count cannot be zero!");
				i = MW*MH + 1;
				ml = 0;
				for (pn = 0; pn < pc; pn++)
				{
					if (m[i] > ml)
						ml = m[i];
					if (m[i] < PA_MIN)
						throw new Exception("Path length cannot be zero!");
					i += m[i];
				}
				char paths __gc[,] = new char __gc[pc,ml];
				int k = MW*MH;
				for (i = 0; i < pc; i++)
				{
					for (int j = 0; j < ml; j++)
					{
						k++;
						if (m[k] == -1)
							break;
						paths[i,j] = m[k];
					}
				}
				return paths;
			}
			catch (Exception * ex)
			{
				MessageBox::Show(String::Concat(ex->ToString(), "\n\ni = ", i.ToString()), "7 Rivers TD", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return new char __gc[1,1];
			}
		}
		static char ToPaths(char m __gc[], int cmax)__gc[,]
		{
			int i, pn, pc, ml;
			try
			{
				pc = m[MW*MH]; // pc = path count
				if (pc == 0)
					throw new Exception("Path count cannot be zero!");
				pc = ((pc < cmax) ? pc : cmax); // Considers only the first [cmax] paths
				i = MW*MH + 1;
				ml = 0;
				for (pn = 0; pn < pc; pn++)
				{
					if (m[i] > ml)
						ml = m[i]; // m[i] = path length
					if (m[i] < PA_MIN)
						throw new Exception("Path length cannot be zero!");
					i += m[i]; // This only considers the "Path X Length" values
				}
				char paths __gc[,] = new char __gc[pc,ml];
				int k = MW*MH;
				for (i = 0; i < pc; i++) // Considers each path in turn.
				{
					for (int j = 0; j < ml; j++)
					{
						k++;
						if (m[k] == -1)
							break; // Start a new path or end the final path, exclude -1 from the path
						paths[i,j] = m[k];
					}
				}
				return paths;
			}
			catch (Exception * ex)
			{
				MessageBox::Show(String::Concat(ex->ToString(), "\n\ni = ", i.ToString()), "7 Rivers TD", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return new char __gc[1,1];
			}
		}
		static char ToPaths(char m __gc[], int cmin, int c_count)__gc[,]
		{
			int i, pn, pc, ml;
			try
			{
				pc = m[MW*MH]; // pc = path count
				if (pc == 0 || c_count == 0)
					throw new Exception("Path count cannot be zero!");
				i = MW*MH + 1;
				ml = 0;
				for (pn = 0; pn < pc; pn++)
				{
					if (m[i] > ml)
						ml = m[i]; // m[i] = path length
					if (m[i] < PA_MIN)
						throw new Exception("Path length cannot be zero!");
					i += m[i]; // This only considers the "Path X Length" values
				}
				char paths __gc[,] = new char __gc[pc,ml];
				int k = MW*MH;
				for (i = cmin; i < cmin + c_count; i++) // Considers each path in turn.
				{
					for (int j = 0; j < ml; j++)
					{
						k++;
						if (m[k] == -1)
							break; // Start a new path or end the final path, exclude -1 from the path
						paths[i-cmin,j] = m[k];
					}
				}
				return paths;
			}
			catch (Exception * ex)
			{
				MessageBox::Show(String::Concat(ex->ToString(), "\n\ni = ", i.ToString()), "7 Rivers TD", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return new char __gc[1,1];
			}
		}
	};
};