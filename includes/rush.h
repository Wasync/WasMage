#include "SDLX/SDLX.h"

typedef void (*lvl_func)(struct Context *, void *);

typedef struct Context
{
	SDLX_GUIElem *buttons[100];

	int lvl;
}			Context;
