#include "debug.h"

void debug(Context *ctx)
{
	SDLX_Input input;
	SDLX_Display *display;

	SDL_Rect rect;

	display = SDLX_DisplayGet();
	input = SDLX_InputGet();

	SDL_SetRenderDrawColor(display->renderer, 0, 0, 255, 255);
	rect.h = 64;
	rect.w =  64;
	rect.x = input.mouse[0] - 32;
	rect.y = input.mouse[1] - 32;

	if (input.mouse_click > 0)
		SDL_Log("Mouse (%d,%d)\n", input.mouse[0], input.mouse[1]);

	SDL_RenderDrawRect(display->renderer, &rect);
	SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
}
