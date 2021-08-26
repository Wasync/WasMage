#ifndef RUSH_H
# define RUSH_H


# include "SDLX/SDLX.h"
# include "buttons.h"

# define STARTX 230
# define STARTY 769
# define FBALL 20616

typedef int (*SpellFn)();
typedef void (*EnemyFn)(void *);

typedef struct  SpellInfo
{
	int 		id;
	int 		cd;
	int 		cost;
	int			active;
	int 		duration;
	int 		castTime;
	int 		chargeTime;
	int 		*state;
	int 		*elapsed;

	SpellFn func;

}				SpellInfo;

typedef struct Spell
{
	SpellInfo info;

	SDL_Point	step;
	SDLX_Sprite cast;
	SDLX_Sprite projectile;
	SDL_Texture *spellPage;

}			Spell;

typedef struct Enemy
{
	int		id;
	int 	hp;
	int		type;

	SDLX_Sprite sprite;
	SDL_Rect 	hitbox;

	EnemyFn		func;

}				Enemy;

typedef struct MainLevel
{
	Spell		active[10];
	Spell		*current;

	Enemy		enemies[100];
}				MainLevel;

typedef struct PlayerData
{
	
}

typedef struct Context
{
	SDLX_GUIElem	*buttons[100];
	SDLX_Sprite  	sprites[100];
	SDLX_Sprite		scroll;

	Spell 		spells[20];

	Enemy		enemy_data[20];

	void *lvl_data;

	int nbuttons;
	int nsprites;
	int nspells;
	int lvl;
}			Context;

typedef struct MainLevel
{
	SDLX_GUIElem *order[13];
	int norder;
	int drawing;
	int state;
}				MainLevel;


static int ctxTrue = SDLX_TRUE;
static int ctxFalse = SDLX_FALSE;
static Spell NoSpell;

// Ref for scroll UI so no need to allocate


Context *getCtx(void);

Context *init_game(void);
void	main_menuInit(void *args);
void	main_levelInit(void *args);
void	test_levelInit(void *args);

void	main_menuCleanup(void *arg);
void	main_levelCleanup(void *arg);
void	test_levelCleanup(void *arg);

void	main_menu(void *args);
void	main_level(void *arg);
void	test_level(void *args);

int		ReadyCheck(Spell *spell);
int		GetSpell(void);
void	DrawSpell(void);
void	CastSpell(int id);
void	ActivateSpell(Spell *spell);
void	CopySpell(Spell *src, Spell *dst);

void	renderSprites(void);
void	flushSprites(void);

int 	initSpells();
int 	Fireball(Spell *spell);
int 	NoSpellFn(Spell *spell);


#endif
