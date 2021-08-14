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
		SDLX_SpriteCreate(&ctx->active[i].sprite, NULL, NULL, &dst);
		SDLX_AnimatorCreate(NULL, NULL, 0, NULL, &ctx->active[i].sprite)->active = SDLX_FALSE;
		i++;
	}

	t_Fireball = SDLX_LoadTexture("Assets/Spells/Fireball.png", SDLX_DisplayGet());
	a_Fireball = calloc(1, sizeof(SDLX_Anim));
	a_Fireball[0] = SDLX_AnimLoadHorizontal(t_Fireball, 11, 64, 64, SDLX_FALSE, 0, 0);
	SDLX_SpriteCreate(&s_Fireball.sprite, t_Fireball, NULL, &dst);
	SDLX_AnimatorCreate(NULL, a_Fireball, 1, NULL, &s_Fireball.sprite)->active = SDLX_FALSE;
	s_Fireball.info.id = 20616;
	s_Fireball.info.func = &Fireball;
	s_Fireball.info.duration = 11;
	s_Fireball.sprite.queue = 2;

	ctx->spells[0] = s_Fireball;

	ctx->current = &NoSpell;
	wasInit = 1;
}

