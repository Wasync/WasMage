# include "rush.h"

void main_menuInit(void *arg)
{
	SDLX_Animator *animator;
	SDLX_Anim	**anim;

	SDL_Texture *tex;	SDL_Rect dst;

	Context *ctx;

	ctx = getCtx();
	dst.x = WIN_W / 2 - (32 * W_SCALE);
	dst.y = WIN_W / 2 - (64 * H_SCALE);
	dst.w = 64 * W_SCALE;
	dst.h = 64 * 1.25;

	ctx->buttons[0] = SDLX_GUIElem_Create(NULL, "Start", &SDLX_DefaultGUISelect, &MenuHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &StartClick);
	ctx->buttons[1] = SDLX_GUIElem_Create(NULL, "Exit", &SDLX_DefaultGUISelect, &MenuHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &ExitClick);
	tex = SDLX_LoadTexture("Assets/UI/MainMenu.png", SDLX_DisplayGet());

	anim = calloc(3, sizeof(SDLX_Anim));
	anim[2] = SDLX_AnimLoadHorizontal(tex, 2, 64, 64, SDL_FALSE, 64 * 8, 0);
	anim[0] = SDLX_AnimLoadHorizontal(tex, 1, 64, 64, SDL_TRUE, 0, 0);
	anim[1] = SDLX_AnimLoadHorizontal(tex, 8, 64, 64, SDL_FALSE, 64, 0);
	animator = SDLX_AnimatorCreate(NULL, anim, 3, &dst, &ctx->buttons[0]->sprite);

	dst.x = WIN_W / 2 - (32 * W_SCALE);
	dst.y = WIN_W - 80;
	anim = calloc(3, sizeof(SDLX_Anim));
	anim[2] = SDLX_AnimLoadHorizontal(tex, 2, 64, 64, SDL_FALSE, 64 * 8, 64);
	anim[0] = SDLX_AnimLoadHorizontal(tex, 1, 64, 64, SDL_TRUE, 0, 64);
	anim[1] = SDLX_AnimLoadHorizontal(tex, 8, 64, 64, SDL_FALSE, 64, 64);
	animator = SDLX_AnimatorCreate(NULL, anim, 3, &dst, &ctx->buttons[1]->sprite);

	ctx->buttons[0]->autotrigger = SDLX_TRUE;
	ctx->buttons[0]->triggered = SDLX_FALSE;

	SDLX_GUIElem_SetActive(ctx->buttons[0], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx->buttons[1], SDLX_TRUE);
	// SDLX_GUIElem_SetKbTarget(SDLX_FALSE, ctx->buttons[0], NULL, NULL, NULL, NULL);
	// SDLX_GUIElem_SetDefaultTarget(ctx->buttons[0]);
	SDL_Log("MainMenu Init \n");
}

void main_menuCleanup(void *arg)
{
	Context *ctx;

	ctx = getCtx();
	SDL_Log("Cleanup main menu\n");
	SDLX_GUIElem_SetActive(ctx->buttons[0], SDLX_FALSE);
}
