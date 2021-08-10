# include "rush.h"

void main_menu(void *arg)
{
	(void)arg;
}

void main_level(void *arg)
{
	SDLX_Input input;
	Context *ctx;
	MainLevel *lvl;
	int i;

	ctx= getCtx();
	lvl = (MainLevel *)ctx->lvl_data;
	input = SDLX_InputGet();
	i = 0;

	while(i < 1)
	{
		if (ctx->active[i].id && !ctx->active[i].func(&ctx->active[i]))
		{
			ctx->active[i].id = 0;
			ctx->active[i].sprite.animator->active = SDLX_FALSE;
			ctx->active[i].sprite.dst.x = STARTX - 64;
			ctx->active[i].sprite.dst.y = STARTY - 64;
			SDL_Log("HERE %d %d", ctx->active[i].sprite.animator->active, ctx->spells[0].sprite.animator->active);
		}
		else if (ctx->active[i].id == 0  && ctx->current->id != 0 && input.mouse_click == SDL_MOUSEBUTTONDOWN)
		{
			// SDL_Log("HERE ANIM (%d,%d), (%d, %d)",
			// ctx->current->sprite.dst.x,
			// ctx->current->sprite.dst.y,
			// ctx->current->sprite.dst.w,
			// ctx->current->sprite.dst.h
			// );

			ctx->active[i].id = ctx->current->id;
			ctx->active[i].cd = ctx->current->cd;
			ctx->active[i].cost = ctx->current->cost;
			ctx->active[i].func = ctx->current->func;
			ctx->active[i].duration = ctx->current->duration;

			SDL_Log("Current %p, active %p", ctx->current->sprite.dstptr, ctx->active[i].sprite.dstptr);
			ctx->active[i].sprite.animator->active = SDLX_TRUE;
			ctx->active[i].sprite.animator->anims = ctx->current->sprite.animator->anims;
			ctx->active[i].sprite.animator->amount = ctx->current->sprite.animator->amount;
			ctx->active[i].sprite.animator->frameNo =  0;
			ctx->active[i].sprite.src = ctx->current->sprite.src;
			// ctx->active[i].sprite.dstptr = &ctx->active[i].sprite.dst;
			ctx->active[i].step.x = (ctx->active[i].sprite.dst.x - (input.mouse.x - 64)) / 7;
			ctx->active[i].step.y = (ctx->active[i].sprite.dst.y - (input.mouse.y - 64)) / 7;
			// ctx->current = &NoSpell;
		}
		i++;
	}
	if (lvl->drawing == SDLX_TRUE)
	{
		DrawShape();
		if (input.mouse_click == SDL_MOUSEBUTTONUP)
		{
			CastSpell(GetShape());
		}
	}
	renderSprites();
}

//MOUSE INIT POS 307, 749

void test_level(void *arg)
{

}

