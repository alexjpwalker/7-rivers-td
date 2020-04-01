using namespace System;
using namespace System::Drawing;

namespace RiversTD
{
	public __gc __sealed class Strings
	{
	public:
		static void Initialize(void)
		{
			for (int i = 0; i < ens->Length; i++)
			{
				ens[i] = undef;
				cols[i] = Color::LightGray;
			}
			for (int i = 0; i < tus->Length; i++)
				tus[i] = undef;
			for (int i = 0; i < g_ovs->Length; i++)
				g_ovs[i] = undef;
			ens[0] = "Normal";
			ens[1] = "Armoured"; cols[1] = Color::MediumPurple;
			ens[2] = "Sprinter"; cols[2] = Color::YellowGreen;
			ens[3] = "Swarm"; cols[3] = Color::Brown;
			ens[REGEN] = "Regenerator"; cols[REGEN] = Color::Orange;
			ens[ERRATIC] = "Erratic"; cols[ERRATIC] = Color::SkyBlue;
			ens[BOSS] = "Armour Boss"; cols[BOSS] = Color::Red;
			ens[SPRINT_BOSS] = "Sprint Boss"; cols[SPRINT_BOSS] = Color::Lime;
			ens[REGEN_BOSS] = "Regen Boss"; cols[REGEN_BOSS] = Color::Yellow;
			ens[ERRATIC_BOSS] = "Erratic Boss"; cols[ERRATIC_BOSS] = Color::Aqua;
			ens[ETMAX-1] = "None";
			tus[0] = "MG Turret"; mtus[0] = "Chaingun";
			tus[1] = "Sniper Turret"; mtus[1] = "Sniper Tower";
			tus[2] = "Laser Turret"; mtus[2] = "Laser Pulser";
			tus[3] = "Plasma Turret"; mtus[3] = "Plasma Cannon";
			specs[0] = "Rapid Fire";
			specs[1] = "Infinite Range";
			specs[2] = "Multi Hit";
			specs[3] = "Plasma Burst";
			g_ovs[0] = "You have killed all of the enemies.\nCongratulations, you win!";
			g_ovs[1] = "You allowed too many enemies to reach your base and ran out of HP.\nYou have lost the game!";
		}
	private:
		static String * ens __gc[] = new String * __gc[ETMAX];
		static Color cols __gc[] = new Color __gc[ETMAX];
		static String * tus __gc[] = new String * __gc[TTMAX];
		static String * mtus __gc[] = new String * __gc[TTMAX];
		static String * specs __gc[] = new String * __gc[TTMAX];
		static String * undef = "Undefined";
		static String * g_ovs __gc[] = new String * __gc[4];
	public:
		__property static String * get_Enemy()__gc[]{return ens;};
		__property static Color get_ColorCode()__gc[]{return cols;};
		__property static String * get_Turret()__gc[]{return tus;};
		__property static String * get_MasterTurret()__gc[]{return mtus;};
		__property static String * get_Special()__gc[]{return specs;};
		__property static String * get_Undefined(){return undef;};
		__property static String * get_GameOver()__gc[]{return g_ovs;};
	};
};