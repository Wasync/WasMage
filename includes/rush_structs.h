#ifndef STRUCTS_H
# define STRUCTS_H

# include "SDLX/SDLX.h"

typedef struct Enemy Enemy;

typedef int (*SpellFn)();
typedef int (*EnemyFn)(Enemy *);

enum
{
	L_ENEMY = 0b0001,
	L_SPELL = 0b0010,
	L_PLAYER = 0b0100,
};

enum
{
	FIRE = 0,
	ICE,
	EARTH,
	WATER,
	LIGHT,
	SHADOW
};

typedef struct  SpellInfo
{
	int 		id;
	int 		cd;
	int 		cost;
	int			type;
	int			damage;
	int			active;
	int 		duration;
	int 		castTime;
	int 		chargeTime;
	int 		*state;
	int 		*elapsed;

	const char *name;
	SDLX_ReactionFn reaction;
	SpellFn func;

}				SpellInfo;

typedef struct Spell
{
	SpellInfo info;

	SDL_Point	step;
	SDLX_Sprite cast;
	SDLX_Sprite projectile;
	SDLX_Animator p_anim;
	SDLX_Animator c_anim;
	SDL_Texture *spellPage;

	SDLX_Collider collider;
}			Spell;

typedef struct Enemy_Info
{
	int			id;
	int 		hp;
	int			type;
	int			speed;
	EnemyFn		func;

	SDL_Rect 	hitbox;
}				Enemy_Info;

typedef struct Enemy
{
	Enemy_Info	info;

	SDLX_Sprite sprite;
	SDLX_Collider collider;
	SDLX_Animator animator;

}				Enemy;



typedef struct Formation
{
	Enemy		enemies[50];
	int 		nenemies;

}				Formation;

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

typedef struct PlayerData
{
	Spell		active[10];
	Spell		*current;

	SDLX_Collider collider;

	int hp;
	int mana;
	int exp;
}				PlayerData;

typedef struct Button
{
	SDLX_GUIElem elem;
	SDLX_Sprite sprite;
	SDLX_Animator anim;

	int isTrigger;
}				Button;

typedef struct MainLevel
{
	Button *order[13];
	Area *area;

	int norder;
	int drawing;
	int state;
}			MainLevel;

typedef struct Context
{
	Button			buttons[100];
	SDLX_Sprite  	sprites[100];
	SDLX_Sprite		scroll;

	Spell 		spells[20];
	Enemy		enemy_data[50];
	PlayerData		player;

	MainLevel level;

	int nbuttons;
	int nsprites;
	int nenmies;
	int nspells;
	int lvl;
}			Context;

#endif
