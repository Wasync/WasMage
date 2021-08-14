#include "rush.h"
#include "debug.h"

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
		// SDLX_RenderQueueDisplay(SDLX_RenderQueue_FetchAll(NULL)[0], display);
		SDLX_Render_DisplayAll(display);
		SDL_RenderPresent(display->renderer);
		SDLX_FPSAdjust();
    }
}
