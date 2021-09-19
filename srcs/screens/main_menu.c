# include "rush.h"

static int cursor;

void main_menuInit(void *arg)
{
	SDLX_Animator *animator;
	SDLX_Anim	**anim;

	SDL_Texture *button_tx;
	SDL_Rect dst;
	SDL_Rect src;
	SDL_Rect text_src;

	Context *ctx;


	ctx = getCtx();
	ctx->nsprites = 0;


	button_tx = SDLX_LoadTexture("Assets/UI/MainMenu.png", SDLX_DisplayGet());

	dst.x = WIN_W / 2 - (98  * W_SCALE);
	dst.y = WIN_W / 2 - (32  * H_SCALE);
	dst.w = 98 * 2 * W_SCALE;
	dst.h = 32 * 2 * 1.25;

	src.h = 32;
	src.w = 98;
	src.x = 0;
	src.y = 0;
	SDLX_SpriteCreate(&ctx->sprites[ctx->nsprites], button_tx, &src, &dst);
	SDLX_GUIElem_Create(&ctx->buttons[0].elem, &ctx->buttons[0].sprite, "Start", &SDLX_DefaultGUISelect, &MenuEnterHover,  &MenuExitHover, &SDLX_NullGUIFunc, &StartClick);
	ctx->nsprites++;


	dst.y += 98 * 2;
	SDLX_SpriteCreate(&ctx->sprites[ctx->nsprites], button_tx, &src, &dst);
	SDLX_GUIElem_Create(&ctx->buttons[1].elem, &ctx->buttons[1].sprite, "Spells", &SDLX_DefaultGUISelect, &MenuEnterHover,  &MenuExitHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc);
	ctx->nsprites++;

	dst.y = WIN_H - dst.h - 32;
	dst.x = WIN_W - dst.w - 32;
	SDLX_SpriteCreate(&ctx->sprites[ctx->nsprites], button_tx, &src, &dst);
	SDLX_GUIElem_Create(&ctx->buttons[2].elem, &ctx->buttons[2].sprite, "Credits", &SDLX_DefaultGUISelect, &MenuEnterHover,  &MenuExitHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc);
	ctx->nsprites++;


	src.y += src.h;
	src.h = 48;
	src.w = 48;
	dst.w = 0;
	dst.h = 64;
	SDLX_SpriteCreate(&ctx->sprites[ctx->nsprites], button_tx, &src, &dst);
	cursor = ctx->nsprites;
	ctx->nsprites++;

	src.x = 48 * 2;
	src.w = 32;
	src.h = 16;
	dst.w = 124;
	dst.h = 64;
	dst.x = WIN_W / 2 - (98  * W_SCALE) + 64;
	dst.y = WIN_W / 2 - (64  * H_SCALE);
	SDLX_SpriteCreate(&ctx->sprites[ctx->nsprites], button_tx, &src, &dst);
	ctx->nsprites++;

	src.x -= 48;
	src.w = 48;
	dst.w = 150;
	dst.x = WIN_W / 2 - (98  * W_SCALE) + 48;
	dst.y += 98 * 2;
	SDLX_SpriteCreate(&ctx->sprites[ctx->nsprites], button_tx, &src, &dst);
	ctx->nsprites++;

	src.y += 16;
	src.w = 56;
	dst.y = WIN_H - dst.h - 98;
	dst.x = WIN_W - dst.w - 64;
	SDLX_SpriteCreate(&ctx->sprites[ctx->nsprites], button_tx, &src, &dst);
	ctx->nsprites++;

	// SDLX_SpriteCreate(&ctx->sprites[ctx->nsprites], tex, &src, &dst);
	// ctx->buttons[0]->autotrigger = SDLX_TRUE;
	// ctx->buttons[0]->triggered = SDLX_FALSE;

	ctx->buttons[0].elem.data = &cursor;
	ctx->buttons[1].elem.data = &cursor;
	ctx->buttons[2].elem.data = &cursor;

	ctx->buttons[0].elem.active = SDLX_TRUE;
	ctx->buttons[1].elem.active = SDLX_TRUE;
	ctx->buttons[2].elem.active = SDLX_TRUE;
	SDLX_GUIElem_SetDefaultTarget(&ctx->buttons[0].elem);
	// SDLX_GUIElem_SetKbTarget(SDLX_FALSE, ctx->buttons[0], NULL, NULL, NULL, NULL);
	SDL_Log("MainMenu Init \n");
}

void main_menu(void *arg)
{
	(void)arg;
	renderSprites();
}

void main_menuCleanup(void *arg)
{
	Context *ctx;

	ctx = getCtx();
	ctx->buttons[0].elem.active = SDLX_FALSE;
	ctx->buttons[1].elem.active = SDLX_FALSE;
	ctx->buttons[2].elem.active = SDLX_FALSE;
	// flushSprites();
	SDL_Log("Cleanup main menu\n");
}
