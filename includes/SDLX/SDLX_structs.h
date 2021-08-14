#ifndef SDLX_structs_H
#define SDLX_structs_H

# include "../SDL2/SDL.h"
# include "SDLX_config.h"

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
struct SDLX_Animator;
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

typedef enum SDLX_Keys
{
	SDLX_UP = 1,
	SDLX_DOWN,
	SDLX_LEFT,
	SDLX_RIGHT,
	SDLX_PAUSE
}			SDLX_Keys;

typedef enum SDLX_InputType
{
	SDLX_MOUSE = 0,
	SDLX_KEYBOARD,
	SDLX_CONTROLLER,
	SDLX_AXIS,
	SDLX_GESTURE,
	SDLX_KEYUP,
	SDLX_KEYDOWN,
	SDLX_KEYHELD
}				SDLX_InputType;

typedef struct	SDLX_Input
{
	int input[INPUT_AMOUNT]; // This is just assuming no more than 5 keys will be mapped but that is a terrible asusmption. This should be allocated
	SDL_Point mouse;
	SDL_Point mouse_delta;
	int mouse_click;
	int key_down;
}				SDLX_Input;

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
	SDL_Rect			*srcptr;
	SDL_Rect			*dstptr;

	SDL_RendererFlip	flip;
	SDL_Point			center;
	SDL_Texture			*sprite_sheet;

	struct SDLX_Animator *animator;

	double				angle;
	int					queue;
}	SDLX_Sprite;

typedef struct SDLX_Anim
{
	int			cycle;
	int			start;

	SDL_bool	loop;
	SDL_Rect	*srcs;
	SDL_Texture *sprite_sheet;
}				SDLX_Anim;

typedef struct SDLX_Animator
{
	int			state;
	int			active;
	int			amount;
	int			frameNo;

	SDLX_Anim	**anims;

	SDLX_Sprite	sprite;
	SDLX_Sprite	*spriteptr;

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
	SDLX_Sprite sprite;
	SDLX_Sprite *spriteptr;

	void *data;

	int	 triggered;
	int  autotrigger;
	struct SDLX_GUIMeta *metadata;

	const char *name;
}				SDLX_GUIElem;


typedef void (* SDLX_LevelFunc)(void *);
typedef int (* SDLX_UIFunc)(SDLX_GUIElem *);

#endif
