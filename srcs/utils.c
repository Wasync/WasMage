#include "rush.h"

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

void flushSprites(void)
{
	SDLX_Display *display;
	Context *ctx;

	int i;

	i = 0;
	ctx = getCtx();
	while (i < ctx->nsprites)
	{
		ctx->sprites[i].sprite_sheet = NULL;
		ctx->sprites[i].animator = NULL;
		ctx->sprites[i].dst = (SDL_Rect){0, 0, 0, 0};
		ctx->sprites[i].src = (SDL_Rect){0, 0, 0, 0};
		i++;
	}
	ctx->nsprites = 0;
}

void CollisionCheck(Enemy *enemies, Spell *spells)
{
	int i;
	int n;

	i = 0;

	while (i < 10)
	{
		n = 0;

		if (spells[i].info.active)
		{
			while (n < 50)
			{
				if (SDL_HasIntersection(&spells[i].projectile.dstptr, &enemies[n].hitbox))
					SDL_Log("Hit");
				n++;
			}
		}
		i++;
	}

}
