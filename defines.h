#define GS 32 // Grid size
#define AS 736 // Area size
#define FD 0.4 // Opening/exit fading effect distance
#define FDL 0.37 // Fading effect gradient limiter
#define GSM 0.64 // Grid size fading effect modifier
#define TMAX 32 // Turret limit
#define TTMAX 10 // Turret type limit
#define UCMAX 800 // Upgrade cost limit
#define CHARRED -9 // Charred tile index
#define STD_TLIM 10 // Highest positive tile index
#define FAST 25 // Game loop interval on "Fast" setting
#define VICTORY 0 // Victory message index
#define DEFEAT 1 // Defeat message index
#define INIT_HP 20 // Initial HP
#define INIT_GOLD 60 // Initia-- Well, what do you think?
#define INIT_WAVE 1 // No comment. (Useful for high-end wave testing.)
#define MASTER 5 // Highest level a turret can reach
#define PA_MIN 5 // Minimal path length (contains only start and end points, and initial direction)
#define PA_MAX 50 // Maximum path length
#define PA_CMAX 10 // Maximum path count
#define INFO_Y 340 // Y-coordinate of information box on Control Panel
#define RELAX 70 // "Relax time" between waves
#define SSMAX 1024 // Maximum number of substrings an input file can be split into
#define MLMAX 1024 // Maximum map/path file length
#define MPL 48 // Maximum path length
#define MPC 10 // Maximum path count

// --- Enemy Traits and Modifiers ---
#define NORMAL 0
#define ARMOUR 1
#define SPRINT 2
#define SWARM 3
#define REGEN 4
#define ERRATIC 5
#define BOSS 6
#define SPRINT_BOSS 7
#define REGEN_BOSS 8
#define ERRATIC_BOSS 9
#define BOSS_DAMAGE 5 // Damage dealt by any boss
#define EMAX 400 // Enemy limit
#define ETMAX 11 // Enemy type limit
#define WMAX 150 // Wave limit
#define IMAX 8 // Enemy image limit
#define ERR_RATE 8 // Erratic enemy constant

// --- Turret Build Costs, Upgrade Costs and Sale Values ---
#define MG_COST 50
#define MG_UP1 15
#define MG_UP2 25
#define MG_UP3 35
#define MG_UP4 155
#define MG_SELL1 45
#define MG_SELL2 58
#define MG_SELL3 81
#define MG_SELL4 112
#define MG_SELL5 252
#define SN_COST 80
#define SN_UP1 30
#define SN_UP2 55
#define SN_UP3 100
#define SN_UP4 170
#define SN_SELL1 72
#define SN_SELL2 99
#define SN_SELL3 148
#define SN_SELL4 238
#define SN_SELL5 391
#define LA_COST 110
#define LA_UP1 105
#define LA_UP2 100
#define LA_UP3 95
#define LA_UP4 190
#define LA_SELL1 99
#define LA_SELL2 193
#define LA_SELL3 283
#define LA_SELL4 369
#define LA_SELL5 540
#define PL_COST 150
#define PL_UP1 85
#define PL_UP2 100
#define PL_UP3 130
#define PL_UP4 325
#define PL_SELL1 135
#define PL_SELL2 211
#define PL_SELL3 301
#define PL_SELL4 418
#define PL_SELL5 711