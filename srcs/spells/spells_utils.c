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
		if (ctx->spells[i].info.id == id)
		{
			ctx->current = &ctx->spells[i];
			SDL_Log("cast %d as %d",id,  i);
			ctx->current->cast.animator->active = SDLX_TRUE;
			ctx->current->projectile.animator->active = SDLX_FALSE;
			ctx->current->info.elapsed = &ctx->current->cast.animator->frameNo;
			ctx->current->info.state = &ctx->current->cast.animator->state;
			*ctx->current->info.state = 1;
			*ctx->current->info.elapsed = 0;
			break ;
		}
		i++;
	}
}

int ReadyCheck(Spell *spell)
{
	if (!spell->info.id)
		return 0;
	// SDL_Log("Spell State %d frame %d", *spell->info.state, *spell->info.elapsed );
	if (*spell->info.state == 2 && *spell->info.elapsed == spell->info.castTime)
		SDLX_Animator_StateSet(spell->cast.animator, 1, SDLX_FALSE);
	if (*spell->info.state == 1 && *spell->info.elapsed == spell->info.chargeTime)
		SDLX_Animator_StateSet(spell->cast.animator, 0, SDLX_FALSE);
	return *spell->info.state == 0;
}

void ActivateSpell(Spell *spell)
{
	spell->info.elapsed = &spell->projectile.animator->frameNo;
	spell->info.state = &spell->projectile.animator->state;
	spell->projectile.animator->active = SDLX_TRUE;
	spell->cast.animator->active = SDLX_FALSE;
	spell->cast.dstptr->x = STARTX;
	spell->cast.dstptr->y = STARTY;
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

void CopySpell(Spell *src, Spell *dst)
{
	dst->info = src->info;
	dst->cast.animator->anims = src->cast.animator->anims;
	dst->cast.animator->amount = src->cast.animator->amount;
	dst->cast.animator->frameNo = 0;
	dst->projectile.animator->anims = src->projectile.animator->anims;
	dst->projectile.animator->amount = src->projectile.animator->amount;
	dst->projectile.animator->frameNo = 0;
}
