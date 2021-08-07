#include "rush.h"
# include "MT.h"
# include "MT_vec2.h"

int GetShape(void)
{
	Context *ctx;
	MainLevel *lvl;
	int number;
	int i;

	i = 0;
	number = 0;
	ctx = getCtx();
	lvl =  (MainLevel *)ctx->lvl_data;

	while (i < lvl->norder)
	{
		number += atoi(lvl->order[i]->name);
		number *= 10;

		lvl->order[i]->sprite.animator->active = SDLX_FALSE;
		i++;
	}
	lvl->norder = 0;
	lvl->drawing = SDLX_FALSE;
	return number;
}

void DrawShape(void)
{
	SDLX_Display *display;
	SDLX_Sprite *sprite;
	SDLX_Input input;

	Context *ctx;
	MainLevel *lvl;
	int i;
	int last[2];

	ctx = getCtx();
	input = SDLX_InputGet();
	display = SDLX_DisplayGet();

	i = 1;
	lvl =  (MainLevel *)ctx->lvl_data;
	last[0] = lvl->order[0]->sprite.dst.x;
	last[1] = lvl->order[0]->sprite.dst.y;
	SDL_SetRenderDrawColor(display->renderer, 255, 0, 0, 255);

	sprite = &lvl->order[lvl->norder - 1]->sprite;
	sprite->dst.w = SDL_sqrt(MT_GetDistance(sprite->dst.x , sprite->dst.y , input.mouse.x, input.mouse.y));
	sprite->angle = MT_ToDegf(atan2(-(sprite->dst.y - input.mouse.y), -(sprite->dst.x - input.mouse.x)));
	if (sprite->dst.w > 200)
		sprite->dst.w = 200;

	SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
}

void renderSprites(void)
{
	SDLX_Display *display;
	Context *ctx;

	int i;

	i = 0;
	ctx = getCtx();
	while (i < ctx->nsprites)
	{
		SDLX_RenderQueueAdd(0, ctx->sprites[i]);
		i++;
	}
}
