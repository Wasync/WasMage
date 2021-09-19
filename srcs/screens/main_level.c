# include "rush.h"

void main_levelInit(void *arg)
{
	SDLX_Anim	**a_beam;

	SDL_Texture *t_beam;
	SDL_Texture *t_scroll;
	SDL_Rect scroll;
	SDL_Rect beamrect;
	SDL_Rect dst;

	Context *ctx;
	int i;

	ctx = getCtx();
	t_beam = SDLX_LoadTexture("Assets/Spells/DrawBeam.png", SDLX_DisplayGet());
	t_scroll = SDLX_LoadTexture("Assets/scroll.png", SDLX_DisplayGet());

	a_beam = calloc(1, sizeof(SDLX_Anim *));
	a_beam[0] = SDLX_AnimLoadVertical(t_beam, 8, 128, 16, SDL_TRUE, 0, 0);

	scroll.h = 128 * 2.25;
	scroll.w = 64 *2.25;
	scroll.x = WIN_W - scroll.w - 10;
	scroll.y = WIN_H - scroll.h ;

	ctx->nsprites = 0;
	SDLX_SpriteCreate(&ctx->scroll , t_scroll, NULL, &scroll);
	ctx->scroll.queue = 0;
	ctx->scroll.src = NULL;

	initSpells();
	initSpellData();


	dst.h = 10;
	dst.w = 0;

	SDLX_GUIElem_Create(&ctx->buttons[ 3].elem, &ctx->buttons[ 3].sprite, "0" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	SDLX_GUIElem_Create(&ctx->buttons[ 4].elem, &ctx->buttons[ 4].sprite, "1" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	SDLX_GUIElem_Create(&ctx->buttons[ 5].elem, &ctx->buttons[ 5].sprite, "2" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	SDLX_GUIElem_Create(&ctx->buttons[ 6].elem, &ctx->buttons[ 6].sprite, "3" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	SDLX_GUIElem_Create(&ctx->buttons[ 7].elem, &ctx->buttons[ 7].sprite, "4" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	SDLX_GUIElem_Create(&ctx->buttons[ 8].elem, &ctx->buttons[ 8].sprite, "5" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	SDLX_GUIElem_Create(&ctx->buttons[ 9].elem, &ctx->buttons[ 9].sprite, "6" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	SDLX_GUIElem_Create(&ctx->buttons[10].elem, &ctx->buttons[10].sprite, "7" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	SDLX_GUIElem_Create(&ctx->buttons[11].elem, &ctx->buttons[11].sprite, "8" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	SDLX_GUIElem_Create(&ctx->buttons[12].elem, &ctx->buttons[12].sprite, "9" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	SDLX_GUIElem_Create(&ctx->buttons[13].elem, &ctx->buttons[13].sprite, "10", &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	SDLX_GUIElem_Create(&ctx->buttons[14].elem, &ctx->buttons[14].sprite, "11", &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	SDLX_GUIElem_Create(&ctx->buttons[15].elem, &ctx->buttons[15].sprite, "12", &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);

// //// TOP POINT

	dst.x = scroll.x + 73;
	dst.y = scroll.y + 60;
	SDLX_AnimatorCreate(&ctx->buttons[3].anim, a_beam, 1, &ctx->buttons[3].sprite);
	ctx->buttons[3].sprite._dst = dst;

// /// TOP ROW

	dst.x = scroll.x + 37;
	dst.y = scroll.y + 93;
	SDLX_AnimatorCreate(&ctx->buttons[4].anim, a_beam, 1, &ctx->buttons[4].sprite);
	ctx->buttons[4].sprite._dst = dst;

	dst.x = scroll.x + 60;
	dst.y = scroll.y + 93;
	SDLX_AnimatorCreate(&ctx->buttons[5].anim, a_beam, 1, &ctx->buttons[5].sprite);
	ctx->buttons[5].sprite._dst = dst;

	dst.x = scroll.x + 85;
	dst.y = scroll.y + 93;
	SDLX_AnimatorCreate(&ctx->buttons[6].anim, a_beam, 1, &ctx->buttons[6].sprite);
	ctx->buttons[6].sprite._dst = dst;

	dst.x = scroll.x + 109;
	dst.y = scroll.y + 93;
	SDLX_AnimatorCreate(&ctx->buttons[7].anim, a_beam, 1, &ctx->buttons[7].sprite);
	ctx->buttons[7].sprite._dst = dst;

// ///MIDDLE ROW

	dst.x = scroll.x + 50;
	dst.y = scroll.y + 128;
	SDLX_AnimatorCreate(&ctx->buttons[8].anim, a_beam, 1, &ctx->buttons[8].sprite);
	ctx->buttons[8].sprite._dst = dst;

	dst.x = scroll.x + 73;
	dst.y = scroll.y + 128;
	SDLX_AnimatorCreate(&ctx->buttons[9].anim, a_beam, 1, &ctx->buttons[9].sprite);
	ctx->buttons[9].sprite._dst = dst;


	dst.x = scroll.x + 95;
	dst.y = scroll.y + 128;
	SDLX_AnimatorCreate(&ctx->buttons[10].anim, a_beam, 1, &ctx->buttons[10].sprite);
	ctx->buttons[10].sprite._dst = dst;

// /// BOTTOM ROW

	dst.x = scroll.x + 37;
	dst.y = scroll.y + 160;
	SDLX_AnimatorCreate(&ctx->buttons[11].anim, a_beam, 1, &ctx->buttons[11].sprite);
	ctx->buttons[11].sprite._dst = dst;

	dst.x = scroll.x + 60;
	dst.y = scroll.y + 160;
	SDLX_AnimatorCreate(&ctx->buttons[12].anim, a_beam, 1, &ctx->buttons[12].sprite);
	ctx->buttons[12].sprite._dst = dst;


	dst.x = scroll.x + 85;
	dst.y = scroll.y + 160;
	SDLX_AnimatorCreate(&ctx->buttons[13].anim, a_beam, 1, &ctx->buttons[13].sprite);
	ctx->buttons[13].sprite._dst = dst;


	dst.x = scroll.x + 100;
	dst.y = scroll.y + 160;
	SDLX_AnimatorCreate(&ctx->buttons[14].anim, a_beam, 1, &ctx->buttons[14].sprite);
	ctx->buttons[14].sprite._dst = dst;


// //BOTTOM MOST POINT
	dst.x = scroll.x + 73;
	dst.y = scroll.y + 195;
	SDLX_AnimatorCreate(&ctx->buttons[15].anim, a_beam, 1, &ctx->buttons[15].sprite);
	ctx->buttons[15].sprite._dst = dst;

// ///////////////////////////////////////

	ctx->buttons[ 3].elem.active = SDLX_TRUE;
	ctx->buttons[ 4].elem.active = SDLX_TRUE;
	ctx->buttons[ 5].elem.active = SDLX_TRUE;
	ctx->buttons[ 6].elem.active = SDLX_TRUE;
	ctx->buttons[ 7].elem.active = SDLX_TRUE;
	ctx->buttons[ 8].elem.active = SDLX_TRUE;
	ctx->buttons[ 9].elem.active = SDLX_TRUE;
	ctx->buttons[10].elem.active = SDLX_TRUE;
	ctx->buttons[11].elem.active = SDLX_TRUE;
	ctx->buttons[12].elem.active = SDLX_TRUE;
	ctx->buttons[13].elem.active = SDLX_TRUE;
	ctx->buttons[14].elem.active = SDLX_TRUE;
	ctx->buttons[15].elem.active = SDLX_TRUE;

	ctx->buttons[ 3].elem.data = &ctx->buttons[ 3];
	ctx->buttons[ 4].elem.data = &ctx->buttons[ 4];
	ctx->buttons[ 5].elem.data = &ctx->buttons[ 5];
	ctx->buttons[ 6].elem.data = &ctx->buttons[ 6];
	ctx->buttons[ 7].elem.data = &ctx->buttons[ 7];
	ctx->buttons[ 8].elem.data = &ctx->buttons[ 8];
	ctx->buttons[ 9].elem.data = &ctx->buttons[ 9];
	ctx->buttons[10].elem.data = &ctx->buttons[10];
	ctx->buttons[11].elem.data = &ctx->buttons[11];
	ctx->buttons[12].elem.data = &ctx->buttons[12];
	ctx->buttons[13].elem.data = &ctx->buttons[13];
	ctx->buttons[14].elem.data = &ctx->buttons[14];
	ctx->buttons[15].elem.data = &ctx->buttons[15];

	ctx->buttons[3].sprite._center = (SDL_Point){0, dst.h / 2};
	ctx->buttons[3].sprite.center = &ctx->buttons[3].sprite._center;
	ctx->buttons[3].anim.active = SDLX_FALSE;

	ctx->buttons[4].sprite._center = (SDL_Point){0, dst.h / 2};
	ctx->buttons[4].sprite.center = &ctx->buttons[4].sprite._center;
	ctx->buttons[4].anim.active = SDLX_FALSE;

	ctx->buttons[5].sprite._center = (SDL_Point){0, dst.h / 2};
	ctx->buttons[5].sprite.center = &ctx->buttons[5].sprite._center;
	ctx->buttons[5].anim.active = SDLX_FALSE;

	ctx->buttons[6].sprite._center = (SDL_Point){0, dst.h / 2};
	ctx->buttons[6].sprite.center = &ctx->buttons[6].sprite._center;
	ctx->buttons[6].anim.active = SDLX_FALSE;

	ctx->buttons[7].sprite._center = (SDL_Point){0, dst.h / 2};
	ctx->buttons[7].sprite.center = &ctx->buttons[7].sprite._center;
	ctx->buttons[7].anim.active = SDLX_FALSE;

	ctx->buttons[8].sprite._center = (SDL_Point){0, dst.h / 2};
	ctx->buttons[8].sprite.center = &ctx->buttons[8].sprite._center;
	ctx->buttons[8].anim.active = SDLX_FALSE;

	ctx->buttons[9].sprite._center = (SDL_Point){0, dst.h / 2};
	ctx->buttons[9].sprite.center = &ctx->buttons[9].sprite._center;
	ctx->buttons[9].anim.active = SDLX_FALSE;

	ctx->buttons[10].sprite._center = (SDL_Point){0, dst.h / 2};
	ctx->buttons[10].sprite.center = &ctx->buttons[10].sprite._center;
	ctx->buttons[10].anim.active = SDLX_FALSE;

	ctx->buttons[11].sprite._center = (SDL_Point){0, dst.h / 2};
	ctx->buttons[11].sprite.center = &ctx->buttons[11].sprite._center;
	ctx->buttons[11].anim.active = SDLX_FALSE;

	ctx->buttons[12].sprite._center = (SDL_Point){0, dst.h / 2};
	ctx->buttons[12].sprite.center = &ctx->buttons[12].sprite._center;
	ctx->buttons[12].anim.active = SDLX_FALSE;

	ctx->buttons[13].sprite._center = (SDL_Point){0, dst.h / 2};
	ctx->buttons[13].sprite.center = &ctx->buttons[13].sprite._center;
	ctx->buttons[13].anim.active = SDLX_FALSE;

	ctx->buttons[14].sprite._center = (SDL_Point){0, dst.h / 2};
	ctx->buttons[14].sprite.center = &ctx->buttons[14].sprite._center;
	ctx->buttons[14].anim.active = SDLX_FALSE;

	ctx->buttons[15].sprite._center = (SDL_Point){0, dst.h / 2};
	ctx->buttons[15].sprite.center = &ctx->buttons[15].sprite._center;
	ctx->buttons[15].anim.active = SDLX_FALSE;


	ctx->level.norder = 0;
	ctx->level.drawing = SDLX_FALSE;

	init_enemies();
	init_enemyData();
	ctx->level.area = loadArea(0);
	NextWave(ctx->level.area);
}

void main_level(void *arg)
{
	SDLX_Input input;
	Context *ctx;
	int i;
	int ready;

	ctx = getCtx();
	input = SDLX_InputGet();
	i = 0;

	ctx->nsprites = 0;
	ready = ReadyCheck(ctx->player.current)
		&& input.mouse_click == SDL_MOUSEBUTTONDOWN
		&& !(SDL_PointInRect(&input.mouse, ctx->scroll.dst));
	// if (ctx->level.area->waves[ctx->level.area->currentWave].nAlive <= 0)
	// 	NextWave(ctx->level.area);
	while (i < ctx->nenmies)
	{
		if (ctx->enemy_data[i].info.id != 0)
			ctx->enemy_data[i].info.func(&ctx->enemy_data[i]);
		i++;
	}
	i = 0;
	while(i < 1)
	{
		if (ctx->player.active[i].info.id && ctx->player.active[i].info.func(&ctx->player.active[i]))
		{
			ctx->player.active[i].info.id = 0;
			ctx->player.active[i].collider.active = SDLX_FALSE;
			ctx->player.active[i].p_anim.active = SDLX_FALSE;
			ctx->player.active[i].projectile._dst.x = STARTX - 64;
			ctx->player.active[i].projectile._dst.y = STARTY - 64;

		}

		if (ready && ctx->player.current->info.id != 0 && ctx->player.active[i].info.id == 0)
		{
			CopySpell(ctx->player.current, &ctx->player.active[i]);
			ActivateSpell(&ctx->player.active[i]);
			SDLX_Animator_StateSet(&(ctx->player.current->c_anim), 2, SDLX_FALSE);
			ready = SDLX_FALSE;
			ctx->player.active[i].step.x = (ctx->player.active[i].projectile._dst.x - (input.mouse.x - 64)) / 7;
			ctx->player.active[i].step.y = (ctx->player.active[i].projectile._dst.y - (input.mouse.y - 64)) / 7;
		}
		i++;
	}
	if (ctx->level.drawing == SDLX_TRUE)
	{
		DrawSpell();
		if (input.mouse_click == SDL_MOUSEBUTTONUP)
			CastSpell(GetSpell());
	}
	ctx->sprites[ctx->nsprites] = ctx->scroll;
	ctx->nsprites++;
	SDLX_PollCollisions();
	// SDL_Log("Poll");
	SDLX_ResolveCollisions();
	// SDL_Log("REsolve");
	// CollisionCheck(ctx->enemy_data, ctx->nenemies, ctx->player.active, 10);
	renderSprites();
}

void main_levelCleanup(void *arg)
{
	Context *ctx;

	ctx = getCtx();
	ctx->buttons[ 2].elem.active = SDLX_FALSE;
	ctx->buttons[ 3].elem.active = SDLX_FALSE;
	ctx->buttons[ 4].elem.active = SDLX_FALSE;
	ctx->buttons[ 5].elem.active = SDLX_FALSE;
	ctx->buttons[ 6].elem.active = SDLX_FALSE;
	ctx->buttons[ 7].elem.active = SDLX_FALSE;
	ctx->buttons[ 8].elem.active = SDLX_FALSE;
	ctx->buttons[ 9].elem.active = SDLX_FALSE;
	ctx->buttons[10].elem.active = SDLX_FALSE;
	ctx->buttons[11].elem.active = SDLX_FALSE;
	ctx->buttons[12].elem.active = SDLX_FALSE;
	ctx->buttons[13].elem.active = SDLX_FALSE;
	ctx->buttons[14].elem.active = SDLX_FALSE;
	SDL_Log("Cleanup main lvl\n");
}
