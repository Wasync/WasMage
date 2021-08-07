#include "rush.h"

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

int TestClick(SDLX_GUIElem *elem)
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

int DrawButtonHover(SDLX_GUIElem *elem)
{
	Context *ctx;
	MainLevel *lvlData;

	ctx = getCtx();
	lvlData = ctx->lvl_data;
	lvlData = (MainLevel *)(ctx->lvl_data);

	if (lvlData->drawing == SDLX_TRUE)
	{
		lvlData->order[lvlData->norder] = elem;
		lvlData->norder++;
		SDLX_GUIElem_SetActive(elem, SDLX_FALSE);
	}
	return 0;
}

int DrawButtonTrigger(SDLX_GUIElem *elem)
{
	Context *ctx;
	MainLevel *lvlData;
	ctx = getCtx();

	lvlData = (MainLevel *)(ctx->lvl_data);
	lvlData->order[0] = elem;
	lvlData->norder++;
	lvlData->drawing = SDLX_TRUE;
	SDLX_GUIElem_SetActive(elem, SDLX_FALSE);

	return 0;
}
