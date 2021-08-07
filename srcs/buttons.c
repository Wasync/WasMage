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

int isHoverDraw(SDLX_GUIElem *elem)
{
	SDLX_Input input;

	input = SDLX_InputGet();

	if (SDLX_PointInCircle(input.mouse,
	 (SDLX_Circle){elem->sprite.dst.x + 2, elem->sprite.dst.y + 5, 7}))
	{
		if (input.mouse_click == SDL_MOUSEBUTTONDOWN)
			elem->triggered = SDLX_TRUE;
		return SDLX_TRUE;
	}
	return SDLX_FALSE;
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
		SDLX_GUIElem_SetActive(elem, SDLX_TRUE);
	}
	return 0;
}

int DrawButtonTrigger(SDLX_GUIElem *elem)
{
	Context *ctx;
	MainLevel *lvlData;
	ctx = getCtx();

		SDL_Log("Is Trigger %s", elem->name);
	lvlData = (MainLevel *)(ctx->lvl_data);
	lvlData->order[0] = elem;
	lvlData->norder++;
	lvlData->drawing = SDLX_TRUE;
	elem->sprite.animator->active = SDLX_TRUE;

	return 0;
}
