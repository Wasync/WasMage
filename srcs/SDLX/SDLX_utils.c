#include "SDLX/SDLX_structs.h"
#include "SDLX/SDLX_config.h"

void SDLX_FPSAdjust()
{
	static int start;
	int delay;

	// This if statement else first frame is delayed by > 1000 ms
	// Workaround is to pass start time but requires variable from outside func
	// Somehow set start to an appropriate starting value
	// This only slows game if it is rendering too fast - but it also halts loop
	// Need to :  if too fast render extra frames of non animated things
	// Render less if too slow
	if (start != 0)
	{
		delay = start - SDL_GetTicks();
		delay = MAX(FRAME_TIME - delay , 0);
		SDL_Delay(delay);
	}
	start = SDL_GetTicks();
}



int	SDLX_MouseIntersectRect(int x, int y, SDL_Rect rect)
{
	if (rect.x <= x && x <= (rect.x + rect.w) &&
		rect.y <= y && y <= (rect.y + rect.h))
		return SDLX_TRUE;
	return SDLX_FALSE;
}
