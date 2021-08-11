# include "rush.h"

static MainLevel mainlvl;

void main_levelInit(void *arg)
{
	SDLX_Animator *animator;
	SDLX_Sprite sprite;
	SDLX_Anim	**anim;
	SDLX_Anim	**beam;

	SDL_Texture *tex;
	SDL_Rect scroll;
	SDL_Rect beamrect;
	SDL_Rect dst;

	Context *ctx;
	int i;

	ctx = getCtx();

	tex = SDLX_LoadTexture("Assets/Spells/DrawBeam.png", SDLX_DisplayGet());
	beam = calloc(1, sizeof(SDLX_Anim));
	beam[0] = SDLX_AnimLoadVertical(tex, 8, 128, 16, SDL_TRUE, 0, 0);

	tex = SDLX_LoadTexture("Assets/scroll.png", SDLX_DisplayGet());
	scroll.h = 128 * 2.25;
	scroll.w = 64 *2.25;
	scroll.x = WIN_W - scroll.w - 10;
	scroll.y = WIN_H - scroll.h ;

	SDLX_SpriteCreate(&ctx->sprites[0] , tex, NULL, &scroll);

	ctx->sprites[0].srcptr = NULL;
	ctx->nsprites++;


	anim = calloc(1, sizeof(SDLX_Anim));
	tex = SDLX_LoadTexture("Assets/Spells/Fireball.png", SDLX_DisplayGet());

	i = 0;
	dst.h = 128;
	dst.w = 128;
	dst.x = STARTX;
	dst.y = STARTY;
	while (i < 10)
	{
		// ctx->active[i] = NoSpell;
		SDLX_SpriteCreate(&ctx->active[i].sprite, NULL, NULL, &dst);
		SDLX_AnimatorCreate(NULL, NULL, 0, NULL, &ctx->active[i].sprite)->active = SDLX_FALSE;
		i++;
	}
	anim[0] = SDLX_AnimLoadHorizontal(tex, 11, 64, 64, SDLX_FALSE, 0, 0);
	SDLX_SpriteCreate(&ctx->spells[0].sprite, tex, NULL, &dst);
	SDLX_AnimatorCreate(NULL, anim, 1, NULL, &ctx->spells[0].sprite)->active = SDLX_FALSE;
	ctx->spells[0].id = 20616;
	ctx->spells[0].func = &Fireball;
	ctx->spells[0].duration = 11;
	ctx->current = &NoSpell;

	dst.h = 10;
	dst.w = 0;

	ctx->buttons[ 2] = SDLX_GUIElem_Create(NULL, "0" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	ctx->buttons[ 3] = SDLX_GUIElem_Create(NULL, "1" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	ctx->buttons[ 4] = SDLX_GUIElem_Create(NULL, "2" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	ctx->buttons[ 5] = SDLX_GUIElem_Create(NULL, "3" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	ctx->buttons[ 6] = SDLX_GUIElem_Create(NULL, "4" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	ctx->buttons[ 7] = SDLX_GUIElem_Create(NULL, "5" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	ctx->buttons[ 8] = SDLX_GUIElem_Create(NULL, "6" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	ctx->buttons[ 9] = SDLX_GUIElem_Create(NULL, "7" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	ctx->buttons[10] = SDLX_GUIElem_Create(NULL, "8" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	ctx->buttons[11] = SDLX_GUIElem_Create(NULL, "9" , &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	ctx->buttons[12] = SDLX_GUIElem_Create(NULL, "10", &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	ctx->buttons[13] = SDLX_GUIElem_Create(NULL, "11", &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	ctx->buttons[14] = SDLX_GUIElem_Create(NULL, "12", &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);

//// TOP POINT

	dst.x = scroll.x + 73;
	dst.y = scroll.y + 60;
	SDLX_AnimatorCreate(NULL, beam, 1, &dst, &ctx->buttons[2]->sprite);

/// TOP ROW

	dst.x = scroll.x + 37;
	dst.y = scroll.y + 93;
	SDLX_AnimatorCreate(NULL, beam, 1, &dst, &ctx->buttons[3]->sprite);

	dst.x = scroll.x + 60;
	dst.y = scroll.y + 93;
	SDLX_AnimatorCreate(NULL, beam, 1, &dst, &ctx->buttons[4]->sprite);

	dst.x = scroll.x + 85;
	dst.y = scroll.y + 93;
	SDLX_AnimatorCreate(NULL, beam, 1, &dst, &ctx->buttons[5]->sprite);

	dst.x = scroll.x + 109;
	dst.y = scroll.y + 93;
	SDLX_AnimatorCreate(NULL, beam, 1, &dst, &ctx->buttons[6]->sprite);

///MIDDLE ROW

	dst.x = scroll.x + 50;
	dst.y = scroll.y + 128;
	SDLX_AnimatorCreate(NULL, beam, 1, &dst, &ctx->buttons[7]->sprite);

	ctx->buttons[7]->autotrigger = SDLX_TRUE;

	dst.x = scroll.x + 73;
	dst.y = scroll.y + 128;
	SDLX_AnimatorCreate(NULL, beam, 1, &dst, &ctx->buttons[8]->sprite);


	dst.x = scroll.x + 95;
	dst.y = scroll.y + 128;
	SDLX_AnimatorCreate(NULL, beam, 1, &dst, &ctx->buttons[9]->sprite);

/// BOTTOM ROW

	dst.x = scroll.x + 37;
	dst.y = scroll.y + 160;
	SDLX_AnimatorCreate(NULL, beam, 1, &dst, &ctx->buttons[10]->sprite);

	dst.x = scroll.x + 60;
	dst.y = scroll.y + 160;
	SDLX_AnimatorCreate(NULL, beam, 1, &dst, &ctx->buttons[11]->sprite);


	dst.x = scroll.x + 85;
	dst.y = scroll.y + 160;
	SDLX_AnimatorCreate(NULL, beam, 1, &dst, &ctx->buttons[12]->sprite);


	dst.x = scroll.x + 100;
	dst.y = scroll.y + 160;
	SDLX_AnimatorCreate(NULL, beam, 1, &dst, &ctx->buttons[13]->sprite);


//BOTTOM MOST POINT
	dst.x = scroll.x + 73;
	dst.y = scroll.y + 195;
	SDLX_AnimatorCreate(NULL, beam, 1, &dst, &ctx->buttons[14]->sprite);

///////////////////////////////////////
	ctx->buttons[2]->sprite.center = (SDL_Point){0, dst.h / 2};
	ctx->buttons[2]->sprite.animator->active = SDLX_FALSE;
	ctx->buttons[2]->data = &ctxFalse;

	ctx->buttons[3]->sprite.center = (SDL_Point){0, dst.h / 2};
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



	SDLX_GUIElem_SetActive(ctx->buttons[2 ], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx->buttons[3 ], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx->buttons[4 ], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx->buttons[5 ], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx->buttons[6 ], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx->buttons[7 ], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx->buttons[8 ], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx->buttons[9 ], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx->buttons[10], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx->buttons[11], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx->buttons[12], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx->buttons[13], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx->buttons[14], SDLX_TRUE);

	mainlvl.norder = 0;
	mainlvl.drawing = SDLX_FALSE;
	ctx->lvl_data = &mainlvl;
	SDL_Log("Init test lvl\n");
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
			ctx->active[i].step.x = (ctx->active[i].sprite.dst.x - (input.mouse.x - 64)) / 7;
			ctx->active[i].step.y = (ctx->active[i].sprite.dst.y - (input.mouse.y - 64)) / 7;
		}
		i++;
	}
	if (lvl->drawing == SDLX_TRUE)
	{
		DrawSpell();
		if (input.mouse_click == SDL_MOUSEBUTTONUP)
		{
			CastSpell(GetSpell());
		}
	}
	renderSprites();
}

void main_levelCleanup(void *arg)
{
	Context *ctx;

	ctx = getCtx();
	SDL_Log("Cleanup main lvl\n");
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
}
