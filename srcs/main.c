#include "rush.h"
// #include "debug.h"

int main(void)
{
	Context *ctx;
	SDL_Event e;
	SDLX_Display  *display;

	SDL_Log("Starting up\n");
	ctx = init_game();
	display = SDLX_DisplayGet();
    while (1)
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
		SDLX_RenderQueueDisplay(SDLX_RenderQueue_FetchAll(NULL)[0], display);
		SDL_RenderPresent(SDLX_DisplayGet()->renderer);
		SDLX_FPSAdjust();
    }
}
