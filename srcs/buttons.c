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
	 (SDLX_Circle){elem->sprite.dst.x + 2, elem->sprite.dst.y + 5, 8}))
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

	if (lvlData->drawing == SDLX_TRUE && *(int *)elem->data == SDLX_FALSE)
	{
		if(lvlData->norder != 0)
		{
			lvlData->order[lvlData->norder - 1]->sprite.dst.w += 4;
			// lvlData->order[lvlData->norder - 1]->sprite.angle = MT_ToDegf(
			// 	atan2(-(lvlData->order[lvlData->norder - 1]->sprite.dst.y
			// 			- elem->sprite.dst.y),
			// 		-(lvlData->order[lvlData->norder - 1]->sprite.dst.x
			// 			- elem->sprite.dst.x)));
		}
		// Fix by changing w toditance between them
		// to be correct but can't be done without extra sqrt
		// & will be a little off anyways
		// AVoid for now
		// }
		lvlData->order[lvlData->norder] = elem;
		elem->sprite.animator->active = SDLX_TRUE;
		elem->data = &ctxTrue;
		lvlData->norder++;
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
	elem->data = &ctxTrue;;

	return 0;
}
