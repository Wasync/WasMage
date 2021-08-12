# include "rush.h"

int MenuHover(SDLX_GUIElem *elem)
{
	SDLX_Animator_StateSet(elem->sprite.animator, 1, SDLX_NONE);
	return 0;
}

int StartClick(SDLX_GUIElem *elem)
{
	SDLX_Animator_StateSet(elem->sprite.animator, 2, SDLX_NONE);
	SDLX_LevelManagerSwitch(1, NULL);
	SDL_Log("HIT start\n");

	return 0;
}

int ExitClick(SDLX_GUIElem *elem)
{
	SDLX_Animator_StateSet(elem->sprite.animator, 2, SDLX_NONE);
	SDLX_LevelManagerSwitch(0, NULL);
	SDL_Log("HIT exit\n");

	return 0;
}
