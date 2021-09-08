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
	ctx->scroll.srcptr = NULL;

	initSpells();
	initSpellData();


	dst.h = 10;
	dst.w = 0;

	ctx->buttons[ 3] = SDLX_GUIElem_Create(NULL, "0" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	ctx->buttons[ 4] = SDLX_GUIElem_Create(NULL, "1" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	ctx->buttons[ 5] = SDLX_GUIElem_Create(NULL, "2" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	ctx->buttons[ 6] = SDLX_GUIElem_Create(NULL, "3" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	ctx->buttons[ 7] = SDLX_GUIElem_Create(NULL, "4" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	ctx->buttons[ 8] = SDLX_GUIElem_Create(NULL, "5" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	ctx->buttons[ 9] = SDLX_GUIElem_Create(NULL, "6" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	ctx->buttons[10] = SDLX_GUIElem_Create(NULL, "7" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	ctx->buttons[11] = SDLX_GUIElem_Create(NULL, "8" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	ctx->buttons[12] = SDLX_GUIElem_Create(NULL, "9" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	ctx->buttons[13] = SDLX_GUIElem_Create(NULL, "10", &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	ctx->buttons[14] = SDLX_GUIElem_Create(NULL, "11", &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	ctx->buttons[15] = SDLX_GUIElem_Create(NULL, "12", &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);

// //// TOP POINT

	dst.x = scroll.x + 73;
	dst.y = scroll.y + 60;
	SDLX_AnimatorCreate(NULL, a_beam, 1, &dst, &ctx->buttons[3]->sprite);

// /// TOP ROW

	dst.x = scroll.x + 37;
	dst.y = scroll.y + 93;
	SDLX_AnimatorCreate(NULL, a_beam, 1, &dst, &ctx->buttons[4]->sprite);

	dst.x = scroll.x + 60;
	dst.y = scroll.y + 93;
	SDLX_AnimatorCreate(NULL, a_beam, 1, &dst, &ctx->buttons[5]->sprite);

	dst.x = scroll.x + 85;
	dst.y = scroll.y + 93;
	SDLX_AnimatorCreate(NULL, a_beam, 1, &dst, &ctx->buttons[6]->sprite);

	dst.x = scroll.x + 109;
	dst.y = scroll.y + 93;
	SDLX_AnimatorCreate(NULL, a_beam, 1, &dst, &ctx->buttons[7]->sprite);

// ///MIDDLE ROW

	dst.x = scroll.x + 50;
	dst.y = scroll.y + 128;
	SDLX_AnimatorCreate(NULL, a_beam, 1, &dst, &ctx->buttons[8]->sprite);

	ctx->buttons[7]->autotrigger = SDLX_TRUE;

	dst.x = scroll.x + 73;
	dst.y = scroll.y + 128;
	SDLX_AnimatorCreate(NULL, a_beam, 1, &dst, &ctx->buttons[9]->sprite);


	dst.x = scroll.x + 95;
	dst.y = scroll.y + 128;
	SDLX_AnimatorCreate(NULL, a_beam, 1, &dst, &ctx->buttons[10]->sprite);

// /// BOTTOM ROW

	dst.x = scroll.x + 37;
	dst.y = scroll.y + 160;
	SDLX_AnimatorCreate(NULL, a_beam, 1, &dst, &ctx->buttons[11]->sprite);

	dst.x = scroll.x + 60;
	dst.y = scroll.y + 160;
	SDLX_AnimatorCreate(NULL, a_beam, 1, &dst, &ctx->buttons[12]->sprite);


	dst.x = scroll.x + 85;
	dst.y = scroll.y + 160;
	SDLX_AnimatorCreate(NULL, a_beam, 1, &dst, &ctx->buttons[13]->sprite);


	dst.x = scroll.x + 100;
	dst.y = scroll.y + 160;
	SDLX_AnimatorCreate(NULL, a_beam, 1, &dst, &ctx->buttons[14]->sprite);


// //BOTTOM MOST POINT
	dst.x = scroll.x + 73;
	dst.y = scroll.y + 195;
	SDLX_AnimatorCreate(NULL, a_beam, 1, &dst, &ctx->buttons[15]->sprite);

// ///////////////////////////////////////

	SDLX_GUIElem_SetActive(ctx->buttons[ 3], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx->buttons[ 4], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx->buttons[ 5], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx->buttons[ 6], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx->buttons[ 7], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx->buttons[ 8], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx->buttons[ 9], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx->buttons[10], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx->buttons[11], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx->buttons[12], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx->buttons[13], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx->buttons[14], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx->buttons[15], SDLX_TRUE);

	ctx->buttons[3]->spriteptr->center = (SDL_Point){0, dst.h / 2};
	ctx->buttons[3]->sprite.animator->active = SDLX_FALSE;
	ctx->buttons[3]->data = &ctxFalse;

	ctx->buttons[4]->sprite.center = (SDL_Point){0, dst.h / 2};
	ctx->buttons[4]->sprite.animator->active = SDLX_FALSE;
	ctx->buttons[4]->data = &ctxFalse;

	ctx->buttons[5]->sprite.center = (SDL_Point){0, dst.h / 2};
	ctx->buttons[5]->sprite.animator->active = SDLX_FALSE;
	ctx->buttons[5]->data = &ctxFalse;

	ctx->buttons[6]->sprite.center = (SDL_Point){0, dst.h / 2};
	ctx->buttons[6]->sprite.animator->active = SDLX_FALSE;
	ctx->buttons[6]->data = &ctxFalse;

	ctx->buttons[7]->sprite.center = (SDL_Point){0, dst.h / 2};
	ctx->buttons[7]->sprite.animator->active = SDLX_FALSE;
	ctx->buttons[7]->data = &ctxFalse;

	ctx->buttons[8]->sprite.center = (SDL_Point){0, dst.h / 2};
	ctx->buttons[8]->sprite.animator->active = SDLX_FALSE;
	ctx->buttons[8]->data = &ctxFalse;

	ctx->buttons[9]->sprite.center = (SDL_Point){0, dst.h / 2};
	ctx->buttons[9]->sprite.animator->active = SDLX_FALSE;
	ctx->buttons[9]->data = &ctxFalse;

	ctx->buttons[10]->sprite.center = (SDL_Point){0, dst.h / 2};
	ctx->buttons[10]->sprite.animator->active = SDLX_FALSE;
	ctx->buttons[10]->data = &ctxFalse;

	ctx->buttons[11]->sprite.center = (SDL_Point){0, dst.h / 2};
	ctx->buttons[11]->sprite.animator->active = SDLX_FALSE;
	ctx->buttons[11]->data = &ctxFalse;

	ctx->buttons[12]->sprite.center = (SDL_Point){0, dst.h / 2};
	ctx->buttons[12]->sprite.animator->active = SDLX_FALSE;
	ctx->buttons[12]->data = &ctxFalse;

	ctx->buttons[13]->sprite.center = (SDL_Point){0, dst.h / 2};
	ctx->buttons[13]->sprite.animator->active = SDLX_FALSE;
	ctx->buttons[13]->data = &ctxFalse;

	ctx->buttons[14]->sprite.center = (SDL_Point){0, dst.h / 2};
	ctx->buttons[14]->sprite.animator->active = SDLX_FALSE;
	ctx->buttons[14]->data = &ctxFalse;

	ctx->buttons[15]->sprite.center = (SDL_Point){0, dst.h / 2};
	ctx->buttons[15]->sprite.animator->active = SDLX_FALSE;
	ctx->buttons[15]->data = &ctxFalse;

	ctx->level.norder = 0;
	ctx->level.drawing = SDLX_FALSE;

	init_enemies();
	init_enemyData();
	ctx->level.area = loadArea(0);
	NextWave(ctx->level.area);
	SDL_Log("Init main lvl\n");

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
		&& !(SDL_PointInRect(&input.mouse, ctx->scroll.dstptr));
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
			ctx->player.active[i].projectile.animator->active = SDLX_FALSE;
			ctx->player.active[i].projectile.dst.x = STARTX - 64;
			ctx->player.active[i].projectile.dst.y = STARTY - 64;

		}

		if (ready && ctx->player.current->info.id != 0 && ctx->player.active[i].info.id == 0)
		{
			CopySpell(ctx->player.current, &ctx->player.active[i]);
			ActivateSpell(&ctx->player.active[i]);
			SDLX_Animator_StateSet(ctx->player.current->cast.animator, 2, SDLX_FALSE);
			ready = SDLX_FALSE;
			ctx->player.active[i].step.x = (ctx->player.active[i].projectile.dst.x - (input.mouse.x - 64)) / 7;
			ctx->player.active[i].step.y = (ctx->player.active[i].projectile.dst.y - (input.mouse.y - 64)) / 7;
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
	SDLX_GUIElem_SetActive(ctx->buttons[2], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx->buttons[3], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx->buttons[4], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx->buttons[5], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx->buttons[6], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx->buttons[7], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx->buttons[8], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx->buttons[9], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx->buttons[10], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx->buttons[11], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx->buttons[12], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx->buttons[13], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx->buttons[14], SDLX_FALSE);
	SDL_Log("Cleanup main lvl\n");
}
