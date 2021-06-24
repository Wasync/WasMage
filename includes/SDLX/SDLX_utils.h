#ifndef SDLX_UTILS_H
# define SDLX_UTILS_H

# include "SDLX/SDLX_structs.h"
/*
* Caps FPS to FRAMERATE and ensure app ticks are consitent
 */
void			SDLX_FPSAdjust(void);
int				SDLX_MouseIntersectRect(int x, int y, SDL_Rect rect);

#endif
