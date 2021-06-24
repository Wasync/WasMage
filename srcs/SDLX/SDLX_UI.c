#include "SDLX.h"

# define GUICT 10

typedef struct SDLX_GUIMeta
{
	int type;
	int active;
	int kb_target;
	int isSelect;

	SDLX_UIFunc		OnSelectEnter;
	SDLX_UIFunc		OnSelectExit;
	SDLX_UIFunc		OnSelectStay;
	SDLX_UIFunc		OnClick;
	SDLX_UIFunc		OnClickStay;
	SDLX_UIFunc		OnClickExit;

	struct { int x, y; } coords;
}				SDLX_GUIMeta;

typedef struct SDLX_GUIInfo
{
	SDLX_GUIElem elem;
	SDLX_GUIMeta meta;
}				SDLX_GUIInfo;

typedef struct GUI_intern
{
	SDLX_GUIInfo *GUI;

	size_t GUIMax;
	size_t GUICount;
}			GUI_intern;

static GUI_intern _intern;

void SDLX_GUIInit(void)
{
	_intern.GUI = calloc(GUICT, sizeof(SDLX_GUIInfo));
	_intern.GUIMax = GUICT;
	_intern.GUICount = 0;
}

SDLX_GUIElem *SDLX_GUIElem_Create(SDLX_Animator *animator, const char *name,
			SDLX_UIFunc OnSelectEnterFn,SDLX_UIFunc OnSelectExitFn,
			SDLX_UIFunc OnSelectStayFn,	SDLX_UIFunc OnClickHeldFn,
			SDLX_UIFunc OnClickFn,	SDLX_UIFunc OnClickReleaseFn)
{
	size_t i;

	i = _intern.GUICount;

	if (i >= _intern.GUIMax)
	{
		_intern.GUIMax *= 2;
		SDL_realloc(_intern.GUI, _intern.GUIMax);
	}
	_intern.GUI[i].elem.animator = animator;
	_intern.GUI[i].elem.name = name;
	_intern.GUI[i].elem.metadata = &_intern.GUI[i].meta;

	_intern.GUI[i].meta.type = SDLX_BUTTON;
	_intern.GUI[i].meta.active = SDLX_FALSE;
	_intern.GUI[i].meta.OnSelectEnter = OnSelectEnterFn;
	_intern.GUI[i].meta.OnSelectStay = OnSelectStayFn;
	_intern.GUI[i].meta.OnSelectExit = OnSelectExitFn;
	_intern.GUI[i].meta.OnClick		 = OnClickFn;
	_intern.GUI[i].meta.OnClickStay = OnClickHeldFn;
	_intern.GUI[i].meta.OnClickExit = OnClickReleaseFn;
	/** Potentially in SetKBCoords
	 * If iskbtarget & AUTO
	 * set kb taget to auto
	 *	some func to figure out coords based on relative pos. Need a button set to 0,0
	 * else if iskbtarget & TRUE
	 * 	set kbtarget to true:
	 *  get coord from other func unless auto then if function called do nothing
	 */
	_intern.GUICount++;
	return &(_intern.GUI[i].elem);
}

void	SDLX_GUIElem_SetActive(SDLX_GUIElem *elem, int isActive) { elem->metadata->active = isActive; }

//Refactor this
void SDLX_GUIUpdate(void)
{
	int i;

	SDLX_Input input;

	SDLX_GUIMeta *meta;

	input = SDLX_InputGet();
	i = 0;
	while (i < _intern.GUICount)
	{
		meta = &(_intern.GUI[i].meta);
		if (meta->active)
		{
			if (SDLX_MouseIntersectRect(input.mouse_x, input.mouse_y, *_intern.GUI[i].elem.animator->dstptr))
			{
				if (meta->isSelect == SDLX_TRUE)
				{
					meta->OnSelectStay(&(_intern.GUI[i].elem));
				}
				else
				{
					meta->isSelect = SDLX_TRUE;
					meta->OnSelectEnter(&(_intern.GUI[i].elem));
				}
				if (input.mouse_click == SDL_MOUSEBUTTONDOWN)
				{
					meta->OnClick(&(_intern.GUI[i].elem));
				}
				else if (input.mouse_click == SDL_MOUSEBUTTONUP)
				{
					meta->OnClickExit(&(_intern.GUI[i].elem));
				}
			}
			else
			{
				if (meta->isSelect == SDLX_TRUE)
				{
					meta->isSelect = SDL_FALSE;
					meta->OnSelectExit(&(_intern.GUI[i].elem));
				}
			}
		}
		i++;
	}
}
