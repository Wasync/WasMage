#ifndef SDLX_structs_H
#define SDLX_structs_H

# include "../SDL2/SDL.h"

# ifndef MAX
#  define MAX(a, b)\
	({ 	__typeof__ (a) _a = (a);\
		__typeof__ (b) _b = (b);\
		(_a > _b) ? (a) : (b);})\

# endif

# ifndef MIN
#  define MIN(a, b)			\
({ 	__typeof__ (a) _a = (a);\
	__typeof__ (b) _b = (b);\
	(_a < _b) ? (a) : (b);})\

# endif

struct SDLX_GUIMeta;
// typedef struct SDLX_GUIMeta  GUIMETA;

enum
{
	SDLX_AWAITANIM = -2,
	SDLX_NONE = -1,
	SDLX_FALSE = 0,
	SDLX_TRUE,
	SDLX_AUTO
};

enum SDLX_GUIType
{
	SDLX_BUTTON = 1,
	SDLX_PANEL
};

typedef struct SDLX_Display
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*background;
}	SDLX_Display;

typedef struct SDLX_Sprite
{
	SDL_Rect			dst;
	SDL_Rect			src;
	SDL_Rect			*dstptr;
	SDL_Rect			*srcptr;

	SDL_RendererFlip	flip;
	SDL_Point			center;
	SDL_Texture			*spriteSheet;

	double				angle;
	int					active;
}	SDLX_Sprite;

typedef struct SDLX_Anim
{
	int			cycle;
	int			start;
	int			queue;

	SDL_bool	loop;
	SDLX_Sprite	*sprites;
}				SDLX_Anim;

typedef struct SDLX_Animator
{
	int			state;
	int			amount;
	int			frameNo;

	SDL_Rect	dst;
	SDL_Rect	*dstptr;
	SDLX_Anim	**anims;

	void		*metadata;
}				SDLX_Animator;

typedef struct SDLX_RenderQueue
{
	size_t		amount;
	size_t		capacity;

	SDLX_Sprite *sprites;
}	SDLX_RenderQueue;

typedef struct SDLX_Circle
{
	double x;
	double y;
	double radius;
}				SDLX_Circle;

typedef struct SDLX_GUIElem
{
	SDLX_Animator *animator;

	void *data;
	struct SDLX_GUIMeta *metadata;

	const char *name;
}				SDLX_GUIElem;

typedef void (* SDLX_UIFunc)(SDLX_GUIElem *);

#endif
