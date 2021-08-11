#include "rush.h"

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
