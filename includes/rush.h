#ifndef RUSH_H
# define RUSH_H


# include "SDLX/SDLX.h"
# include "buttons.h"

# define STARTX 230
# define STARTY 769

typedef int (*SpellFn)();

typedef struct Spell
{
	int id;
	int cd;
	int cost;
	int duration;

	SDL_Point	step;
	SDL_Texture *spellPage;
	SDLX_Sprite sprite;

	SpellFn func;
}			Spell;

typedef struct Context
{
	SDLX_GUIElem *buttons[100];
	SDLX_Sprite  sprites[100];

	Spell 		spells[20];
	Spell		active[10];
	Spell		*current;

	void *lvl_data;
	int nbuttons;
	int nsprites;
	int nspells;
	int lvl;
}			Context;

typedef struct MainLevel
{
	// SDLX_Animator *shape[13];
	SDLX_GUIElem *order[13];
	int norder;
	int drawing;
}				MainLevel;


static int ctxTrue = SDLX_TRUE;
static int ctxFalse = SDLX_FALSE;
static Spell NoSpell;

// Ref for scroll UI so no need to allocate


Context *getCtx(void);

Context *init_game(void);
void main_menuInit(void *args);
void main_levelInit(void *args);
void test_levelInit(void *args);

void main_menuCleanup(void *arg);
void main_levelCleanup(void *arg);
void test_levelCleanup(void *arg);

void main_menu(void *args);
void main_level(void *arg);
void test_level(void *args);

void DrawSpell(void);
int GetSpell(void);
void CastSpell(int id);

void renderSprites(void);

int Fireball(Spell *spell);
int NoSpellFn(Spell *spell);


#endif
