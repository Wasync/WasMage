#include "rush.h"

static int wasInit;

int initSpells()
{
	Context		*ctx;
	SDL_Rect 	dst;
	SDL_Texture *t_Fireball;

	SDLX_Anim	**a_Fireball;

	Spell s_Fireball;

	int i;

	if (wasInit)
		return wasInit;

	i = 0;
	dst.h = 128;
	dst.w = 128;
	dst.x = STARTX;
	dst.y = STARTY;
	ctx = getCtx();
	while (i < 10)
	{
		SDLX_SpriteCreate(&ctx->active[i].cast, NULL, NULL, &dst);
		SDLX_SpriteCreate(&ctx->active[i].projectile, NULL, NULL, &dst);
		SDLX_AnimatorCreate(NULL, NULL, 0, NULL, &ctx->active[i].cast)->active = SDLX_FALSE;
		SDLX_AnimatorCreate(NULL, NULL, 0, NULL, &ctx->active[i].projectile)->active = SDLX_FALSE;
		i++;
	}

	dst.h =  98 * 2;
	dst.w = 128 * 2;
	dst.x -= dst.w / 2;
	dst.y = WIN_H - dst.h;
	t_Fireball = SDLX_LoadTexture("Assets/Spells/Fireball.png", SDLX_DisplayGet());
	a_Fireball = calloc(4, sizeof(SDLX_Anim *));
	a_Fireball[0] = SDLX_AnimLoadHorizontal(t_Fireball,  6, 128, 98, SDLX_TRUE , 0, 98);
	a_Fireball[1] = SDLX_AnimLoadHorizontal(t_Fireball,  9, 128, 98, SDLX_TRUE, 0, 0);
	a_Fireball[2] = SDLX_AnimLoadHorizontal(t_Fireball,  8, 128, 98, SDLX_TRUE, 0, 197);
	a_Fireball[3] = SDLX_AnimLoadHorizontal(t_Fireball, 11,  64, 64, SDLX_TRUE, 0, 296);

	SDLX_SpriteCreate(&(ctx->spells[0].cast), t_Fireball, NULL, &dst);
	SDLX_SpriteCreate(&(ctx->spells[0].projectile), t_Fireball, NULL, &dst);
	SDLX_AnimatorCreate(NULL, a_Fireball, 3, NULL, &(ctx->spells[0].cast))->active = SDLX_FALSE;
	SDLX_AnimatorCreate(NULL, &a_Fireball[3], 1, NULL, &(ctx->spells[0].projectile))->active = SDLX_FALSE;
	ctx->spells[0].info.id = FBALL;
	ctx->spells[0].info.func = &Fireball;
	ctx->spells[0].info.duration = 10;
	ctx->spells[0].info.chargeTime = 8;
	ctx->spells[0].info.castTime = 7;
	ctx->spells[0].cast.queue = 0;

	ctx->current = &NoSpell;
	wasInit = 1;
	return 0;
}

