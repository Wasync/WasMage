#include "rush_structs.h"
#include "enemies.h"

# define NAREAS 2

extern Formation _formations_data[NFORMATIONS];
extern Enemy 	 _enemy_data[50];

Area areas[NAREAS];

typedef void (*AreaFn)(void);


void _loadArea_0(void);

static AreaFn areaInit[NAREAS] = { &_loadArea_0 };

void _loadArea_0(void)
{
	memcpy(&(areas[0].waves[0].enemies), &(F_SINGLE.enemies), sizeof(Enemy) * F_SINGLE.nenemies);
	areas[0].waves[0].nenemies =  F_SINGLE.nenemies;
	areas[0].waves[0].spawnTimer = 2;
	areas[0].nwaves = 0;
	areas[0].currentWave = -1;
	areas[0].waves[0].nAlive = areas[0].waves[0].nenemies;
	SDL_Log("ENEMIES NO %d", areas[0].waves[0].nenemies);
}

Area *loadArea(int areaNo)
{
	if (areas[areaNo].isLoaded == SDLX_FALSE)
	{
		areaInit[areaNo]();
	}
	return &areas[areaNo];
}
