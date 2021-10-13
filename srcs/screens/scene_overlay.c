# include "rush.h"

static SDLX_Sprite OverlayBG;

void init_pause(SDL_Texture *pauseTex, Context *ctx)
{
	SDL_Rect pause;
	SDL_Rect src;
	SDL_Rect dst;

	src.w = 160;
	src.h = 111;
	src.x = 0;
	src.y = 0;

	dst.w = src.w * 2;
	dst.h = src.h * 2;
	dst = src;
	dst.x = WIN_W / 4;
	dst.y = WIN_H / 4;

	SDLX_SpriteCreate(&OverlayBG, pauseTex,&src , &dst);

	src.y += src.h;
	src.w = 30;
	src.h = 30;
	src.x = src.w;

	dst.y += dst.h - 32;
	dst.h = 30;
	dst.w = 32;
	dst.x = dst.w;

	// SDLX_SpriteCreate(&ctx->buttons[16].sprite, pauseTex, &src , &dst);

	// src.x += src.w;
	// dst.x += dst.w;
	// SDLX_SpriteCreate(&ctx->buttons[17].sprite, pauseTex, &src , &dst);

	// src.x += src.w;
	// dst.x += dst.w;
	// SDLX_SpriteCreate(&ctx->buttons[18].sprite, pauseTex, &src , &dst);

	// src.x += src.w;
	// dst.x += dst.w;
	// SDLX_SpriteCreate(&ctx->buttons[19].sprite, pauseTex, &src , &dst);

	// SDLX_GUIElem_Create(&ctx->buttons[16].elem, &ctx->buttons[16].sprite, "Play" ,		&SDLX_DefaultGUISelect, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc);
	// SDLX_GUIElem_Create(&ctx->buttons[17].elem, &ctx->buttons[17].sprite, "Restart",	&SDLX_DefaultGUISelect, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc);
	// SDLX_GUIElem_Create(&ctx->buttons[18].elem, &ctx->buttons[18].sprite, "SpellBook",	&SDLX_DefaultGUISelect, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc);
	// SDLX_GUIElem_Create(&ctx->buttons[19].elem, &ctx->buttons[19].sprite, "Home" ,		&SDLX_DefaultGUISelect, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc);

	// ctx->buttons[16].elem.active = SDLX_FALSE;
	// ctx->buttons[17].elem.active = SDLX_FALSE;
	// ctx->buttons[18].elem.active = SDLX_FALSE;
	// ctx->buttons[19].elem.active = SDLX_FALSE;

}

void showPauseScreen()
{

}
