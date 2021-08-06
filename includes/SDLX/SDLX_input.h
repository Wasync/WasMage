#ifndef SDLX_INPUT_H
# define SDLX_INPUT_H

# include "SDLX_config.h"
# include "SDLX.h"

typedef struct	SDLX_Input
{
	int input[INPUT_AMOUNT]; // This is just assuming no more than 5 keys will be mapped but that is a terrible asusmption. This should be allocated
	int mouse[2];
	int mouseDelta[2];
	int mouse_click;
	int key_down;
}				SDLX_Input;


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

SDLX_Input	SDLX_InputGet();
int			SDLX_DirReverse(int dir);
/*
* This functions doesn't exist yet :>
 */
int			SDLX_InputRemap(int sdl_code, int type, int sdlx_code, int value, int controller_no);

/**
 * @brief Maps an SDL input Keycode to and SDLX code for ease of access. Allows multiple mappins per SDLX code
 * @example SDLX_inputMap(SDL_KEYCODE_RIGH, 1, SDLX_RIGHT, 0);
 * @param sdl_code the SDL_Keycode or Controller_code to map from
 * @param type the type of input to be mapped 1: keyboard 2 :controller
 * @param sdlx_code the SDLX code to map to
 * @param controller_no controller index to pull input from, irrelevant if type is not 2
 *  */

void 		SDLX_InputResetBuffer(void);

void		SDLX_InputMap  (int sdl_code, int type, int sdlx_code, int value, int SDL_UNUSED controller_no);
void		SDLX_InputUpdate(SDL_Event SDL_UNUSED event);
void		SDLX_InputLoop(void);

int 		SDLX_GetKeyMapState(int key);

#endif
