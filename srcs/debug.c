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
	rect.x = input.mouse.x - 32;
	rect.y = input.mouse.y - 32;

	if (input.mouse_click == SDL_MOUSEBUTTONDOWN)
		SDL_Log("Mouse (%d,%d) (%d,%d)\n", input.mouse.x, input.mouse.y,
		input.mouse.x - 471, input.mouse.y -  587);

	SDL_RenderDrawRect(display->renderer, &rect);
	SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 255);
}
