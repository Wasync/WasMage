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

	ctx= getCtx();
	lvl = (MainLevel *)ctx->lvl_data;
	input = SDLX_InputGet();
	if (lvl->drawing == SDLX_TRUE)
	{
		DrawShape();
		if (input.mouse_click == SDL_MOUSEBUTTONUP)
			SDL_Log("Shape %d\n", GetShape());
	}
	renderSprites();
}

void test_level(void *arg)
{
	(void)arg;


}

