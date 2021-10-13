#ifndef LEVEL_STRUCTS_H
# define LEVEL_STRUCTS_H

# include "data_structs.h"

typedef struct Wave
{
	Enemy		enemies[50];
	int			nenemies;

	int 		difficulty;
	int			nAlive;
	int			spawnTimer;
}				Wave;


typedef struct Area
{
	SDL_Texture *bg;
	int nwaves;

	Wave 		waves[12];

	int			currentWave;
	int 		isLoaded;
}				Area;


#endif
