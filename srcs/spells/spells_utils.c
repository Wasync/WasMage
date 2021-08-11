#include "rush.h"
# include "MT.h"
# include "MT_vec2.h"

int NoSpellFn(Spell *spell)
{
	(void)spell;
	return 0;
}

void CastSpell(int id)
{
	int i;
	Context *ctx;

	ctx = getCtx();
	i  = 0;

	while (i < 20)
	{
		if (ctx->spells[i].id == id)
		{
			ctx->current = &ctx->spells[i];
			break ;
		}
		i++;
	}
}

int GetSpell(void)
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
		number |= (1 << (atoi(lvl->order[i]->name) + i));

		lvl->order[i]->sprite.dst.w = 0;
		lvl->order[i]->sprite.animator->active = SDLX_FALSE;
		lvl->order[i]->data = &ctxFalse;
		i++;
	}
	lvl->norder = 0;
	lvl->drawing = SDLX_FALSE;
	return number;
}

void DrawSpell(void)
{
	SDLX_Display *display;
	SDLX_Sprite *sprite;
	SDLX_Input input;

	Context *ctx;
	MainLevel *lvl;

	ctx = getCtx();
	input = SDLX_InputGet();
	display = SDLX_DisplayGet();

	lvl =  (MainLevel *)ctx->lvl_data;

	SDL_SetRenderDrawColor(display->renderer, 255, 0, 0, 255);
	sprite = &lvl->order[lvl->norder - 1]->sprite;
	sprite->dst.w = SDL_sqrt(MT_GetDistance(sprite->dst.x , sprite->dst.y , input.mouse.x, input.mouse.y));
	// sprite->dst.w += input.mouse_delta.x + input.mouse_delta.y; potentially something to be done with mouse delta
	// to avoid the sqrt
	sprite->angle = MT_ToDegf(atan2(-(sprite->dst.y - input.mouse.y), -(sprite->dst.x - input.mouse.x)));
	if (sprite->dst.w > 200)
		sprite->dst.w = 200;

	SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
}
