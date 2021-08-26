#include "rush.h"
// #include "debug.h"

SDLX_Animator *a;

int main(void)
{
	Context *ctx;
	SDL_Event e;
	SDLX_Display  *display;

	SDL_Log("Starting up\n");
	ctx = init_game();
	display = SDLX_DisplayGet();
		SDLX_LevelRun();
	// SDL_Log("ORI start%p", a->spriteptr->dstptr);
	// SDL_Log("ORI D %p R %p", display, display->renderer);

    while (1)
    {
		// SDL_Log("Anim start%p", a->spriteptr->dstptr);
		SDLX_ResetWindow();
		// SDL_Log("Anim rest %p", a->spriteptr->dstptr);
		SDLX_InputUpdate(e);
		// SDL_Log("Anim up %p", a->spriteptr->dstptr);
        SDLX_InputLoop();
		// SDL_Log("Anim inp %p", a->spriteptr->dstptr);
		SDLX_LevelRun();
		// SDL_Log("Anim run %p", a->spriteptr->dstptr);
		SDLX_GUIUpdate();
		// SDL_Log("Anim gui %p", a->spriteptr->dstptr);
		SDLX_AnimationUpdate();
		// SDL_Log("Anim anim dst %p %d, %d. %d %d",
		// a->spriteptr->dstptr,
		//  a->spriteptr->dstptr->x,
		//  a->spriteptr->dstptr->y,
		//  a->spriteptr->dstptr->h,
		//  a->spriteptr->dstptr->w
		//  );
		// SDL_Log("Anim anim src%d", a->spriteptr->srcptr->x);
		# ifdef DEBUG
			debug(ctx);
		#endif
		// SDLX_RenderQueueDisplay(SDLX_RenderQueue_FetchAll(NULL)[0], display);
		SDLX_Render_DisplayAll(display);
		// SDL_Log("Anim displa %p", a->spriteptr->dstptr);
		SDL_RenderPresent(display->renderer);
		// SDL_Log("Anim RENDER %p", a->spriteptr->dstptr);
		SDLX_FPSAdjust();
		// SDL_Log("Anim FPS %p", a->spriteptr->dstptr);
    }
}
