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
			ctx->player.current->c_anim.active = SDLX_TRUE;
			ctx->player.current->p_anim.active = SDLX_FALSE;
			ctx->player.current->info.elapsed = &ctx->player.current->c_anim.frameNo;
			ctx->player.current->info.state = &ctx->player.current->c_anim.state;
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
		SDLX_Animator_StateSet(&spell->c_anim, 1, SDLX_FALSE);
	if (*spell->info.state == 1 && *spell->info.elapsed == spell->info.chargeTime)
		SDLX_Animator_StateSet(&spell->c_anim, 0, SDLX_FALSE);
	return *spell->info.state == 0;
}

void ActivateSpell(Spell *spell)
{
	spell->info.elapsed = &spell->p_anim.frameNo;
	spell->info.state = &spell->p_anim.state;
	spell->p_anim.active = SDLX_TRUE;
	spell->c_anim.active = SDLX_FALSE;
	spell->cast.dst->x = STARTX;
	spell->cast.dst->y = STARTY;
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
		number |= (1 << (atoi(ctx->level.order[i]->elem.name) + i));

		ctx->level.order[i]->sprite.dst->w = 0;
		ctx->level.order[i]->anim.active = SDLX_FALSE;
		ctx->level.order[i]->isTrigger = SDLX_FALSE;
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
	sprite = &ctx->level.order[ctx->level.norder - 1]->sprite;
	// SDL_Log("noder %d", ctx->level.norder);
	// SDL_Log("Sprite %p", sprite);


	SDL_SetRenderDrawColor(display->renderer, 255, 0, 0, 255);
	sprite->dst->w = SDL_sqrt(MT_GetDistance(sprite->dst->x , sprite->dst->y , input.mouse.x, input.mouse.y));
	// sprite->dst->w += input.mouse_delta.x + input.mouse_delta.y; potentially something to be done with mouse delta
	// to avoid the sqrt
	sprite->angle = MT_ToDegf(atan2(-(sprite->dst->y - input.mouse.y), -(sprite->dst->x - input.mouse.x)));
	if (sprite->dst->w > 200)
		sprite->dst->w = 200;

	SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
}

void CopySpell(Spell *src, Spell *dst)
{
	dst->info = src->info;
	dst->c_anim.anims = src->c_anim.anims;
	dst->c_anim.amount = src->c_anim.amount;
	dst->c_anim.frameNo = 0;
	dst->p_anim.anims = src->p_anim.anims;
	dst->p_anim.amount = src->p_anim.amount;
	dst->p_anim.frameNo = 0;
	dst->collider.reactionFn = src->info.reaction;
}
