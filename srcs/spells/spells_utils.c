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
			ctx->player.current = &ctx->spells[i];
			SDL_Log("cast %d as %d",id,  i);
			ctx->player.current->cast.animator->active = SDLX_TRUE;
			ctx->player.current->projectile.animator->active = SDLX_FALSE;
			ctx->player.current->info.elapsed = &ctx->player.current->cast.animator->frameNo;
			ctx->player.current->info.state = &ctx->player.current->cast.animator->state;
			*ctx->player.current->info.state = 1;
			*ctx->player.current->info.elapsed = 0;
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
	spell->collider.active = SDLX_TRUE;
}

int GetSpell(void)
{
	Context *ctx;
	int number;
	int i;

	i = 0;
	number = 0;
	ctx = getCtx();


	while (i < ctx->level.norder)
	{
		number |= (1 << (atoi(ctx->level.order[i]->name) + i));

		ctx->level.order[i]->sprite.dst.w = 0;
		ctx->level.order[i]->sprite.animator->active = SDLX_FALSE;
		ctx->level.order[i]->data = &ctxFalse;
		i++;
	}
	ctx->level.norder = 0;
	ctx->level.drawing = SDLX_FALSE;
	SDL_Log("GOt %d", number);
	return number;
}

void DrawSpell(void)
{
	SDLX_Display *display;
	SDLX_Sprite *sprite;
	SDLX_Input input;

	Context *ctx;

	ctx = getCtx();
	input = SDLX_InputGet();
	display = SDLX_DisplayGet();


	SDL_SetRenderDrawColor(display->renderer, 255, 0, 0, 255);
	sprite = &ctx->level.order[ctx->level.norder - 1]->sprite;
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
	dst->collider.reactionFn = src->info.reaction;
}
