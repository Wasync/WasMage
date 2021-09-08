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

	if (ctx->level.drawing == SDLX_TRUE && *(int *)elem->data == SDLX_FALSE)
	{
		if(ctx->level.norder != 0)
		{
			ctx->level.order[ctx->level.norder - 1]->sprite.dst.w += 4;
		}
		// Fix by changing w toditance between them
		// to be correct but can't be done without extra sqrt
		// & will be a little off anyways
		// AVoid for now
		// }
		ctx->level.order[ctx->level.norder] = elem;
		elem->sprite.animator->active = SDLX_TRUE;
		elem->data = &ctxTrue;
		ctx->level.norder++;
	}
	return 0;
}

int DrawButtonTrigger(SDLX_GUIElem *elem)
{
	Context *ctx;
	ctx = getCtx();

	ctx->level.order[0] = elem;
	ctx->level.norder++;
	ctx->level.drawing = SDLX_TRUE;
	elem->sprite.animator->active = SDLX_TRUE;
	elem->data = &ctxTrue;;

	return 0;
}
