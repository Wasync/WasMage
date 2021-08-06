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
	SDL_Log("Shape\n");
	while (i < lvl->norder)
	{
		number += atoi(lvl->order[i]->name);
		number *= 10;

		SDLX_GUIElem_SetActive(lvl->order[i], SDLX_TRUE);
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
	// SDL_Log("HERE");
	while (i < lvl->norder)
	{

		last[0] = lvl->order[i]->sprite.dst.x + 32;
		last[1] = lvl->order[i]->sprite.dst.y + 32;
		i++;
	}
	sprite = &lvl->order[i - 1]->sprite;
	sprite->dst.w = SDL_sqrt(MT_GetDistance(last[0] , last[1] , input.mouse[0], input.mouse[1]));
	// anim->angle = MT_V2Heading180_Deg((MT_Vector2){last[0] - input.mouse[0], last[1] - input.mouse[1]});
	sprite->angle = MT_ToDegf(atan2(-(last[1] - input.mouse[1]), -(last[0] - input.mouse[0])));
	if (sprite->dst.w > 200)
		sprite->dst.w = 200;
	SDL_Log("DIST %d, angle %d", sprite->dst.w, sprite->angle);

	// SDL_RenderDrawLine(display->renderer, last[0] + 32, last[1] + 32, input.mouse[0], input.mouse[1]);
	SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
}
