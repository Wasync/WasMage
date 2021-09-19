#ifndef ENEMIES_H
# define ENEMIES_H

# include "rush_structs.h"
# define NFORMATIONS 1
# define NWAVES      1

extern Formation _formations_data[NFORMATIONS];

extern Enemy 	 _enemy_data[50];

# define E_SKULL _enemy_data[0]

# define F_SINGLE _formations_data[0]

# define F_ADD(formation, data, _x, _y, _w, _h, offset)\
{	\
	memcpy(&(formation.enemies[offset]), &data, sizeof(data));\
	formation.enemies[offset].sprite.dst = &formation.enemies[offset].sprite._dst;\
	formation.enemies[offset].sprite._dst.x = _x;\
	formation.enemies[offset].sprite._dst.y = _y;\
	formation.enemies[offset].sprite._dst.w = _w;\
	formation.enemies[offset].sprite._dst.h = _h;\
	formation.nenemies++;\
	offset++; }\

void init_enemies(void);
void init_enemyData(void);

Area *loadArea(int areaNo);

int NextWave(Area *area);
void CopyEnemy(Enemy *dst, Enemy*src);
int skullfn(Enemy *self);

void e_react(SDLX_Collider *self, SDLX_Collider *other);

#endif
