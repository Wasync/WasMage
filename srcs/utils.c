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

void CopyEnemy(Enemy *dst, Enemy*src)
{
	dst->info = src->info;
	SDLX_AnimatorCopy(dst->sprite.animator, src->sprite.animator);
	dst->sprite.angle = src->sprite.angle;
	dst->sprite.center = src->sprite.center;
	dst->sprite.flip = src->sprite.flip;
	dst->sprite.dst = *src->sprite.dstptr;
}

int NextWave(Area *area)
{
	Context *ctx;
	Wave *wave;


	if (area->currentWave == area->nwaves)
		return -1;
	ctx = getCtx();
	area->currentWave++;
	wave = &(area->waves[area->currentWave]);
	ctx->nenmies = wave->nenemies;
	for (int i = 0; i < wave->nenemies; i++)
	{
		CopyEnemy(&ctx->enemy_data[i], &wave->enemies[i]);
		ctx->enemy_data[i].sprite.animator->active = SDLX_TRUE;
		ctx->enemy_data[i].collider.active = SDLX_TRUE;
	}
}

int spell_collide(SDLX_Collider *self, SDLX_Collider *other)
{
	SDL_Rect *rect;
	SDL_Point point;

	rect = (SDL_Rect *)self->collisionBoxPtr;
	point.x = rect->x + (rect->w / 2);
	point.y = rect->y + (rect->h / 2);
	return (((Spell *)self->data)->info.active &&
		SDL_PointInRect(&point, other->collisionBoxPtr));
}
