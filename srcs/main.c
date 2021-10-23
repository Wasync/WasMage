#include "rush.h"
 #include <emscripten.h>
// #include "debug.h"

SDLX_Display *display;
static SDL_Event e;
void loop()
{
	SDLX_ResetWindow();
	SDLX_InputUpdate(e);
	SDLX_InputLoop();
	SDLX_LevelRun();
	SDLX_GUIUpdate();
	SDLX_AnimationUpdate();

	# ifdef DEBUG
		debug(ctx);
	#endif
	// SDLX_RenderQueueDisplay(SDLX_RenderQueue_FetchAll(NULL)[0], display);
	SDLX_Render_DisplayAll(display);
	SDL_RenderPresent(display->renderer);
	SDLX_FPSAdjust();
}

int main(void)
{
	Context *ctx;

	SDL_Log("Starting up\n");
	ctx = init_game();
	display = SDLX_DisplayGet();
		SDLX_LevelRun();
	// SDL_Log("ORI start%p", a->spriteptr->dstptr);
	// SDL_Log("ORI D %p R %p", display, display->renderer);
	emscripten_set_main_loop(loop, 0, 1);
}
