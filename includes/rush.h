#ifndef RUSH_H
# define RUSH_H


# include "SDLX/SDLX.h"
# include "buttons.h"

typedef struct Context
{
	SDLX_GUIElem *buttons[100];

	void *lvl_data;
	int nbuttons;
	int lvl;
}			Context;

typedef struct MainLevel
{
	SDLX_Animator *shape[9];
	SDLX_GUIElem *order[9];
	int norder;
	int drawing;

}				MainLevel;


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

void DrawShape(void);
int GetShape(void);

#endif
