#include "SDLX_structs.h"
#include "SDLX_utils.h"
#include "SDLX_input.h"

# define GUICT 15
# define U 0
# define D 1
# define L 2
# define R 3
# define STARTSELECT 0
# define STAY 1
# define ENDSELECT 2
# define CLICKED 3
# define SELECT 4
# define WASSELECT 4


typedef struct SDLX_GUIMeta
{
	int type;
	int active;
	int selectStatus;
	int cd;

	SDLX_UIFunc		isSelectFn;
	SDLX_UIFunc		UIFuncs[4];
	SDLX_GUIElem	*neighbours[4];

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

static int keypress;
static int selector;
static int GUI_KEYS[5];
static int KEYSDATA[5];
static GUI_intern _intern;
static SDLX_GUIElem *defaultTarget;
static SDLX_GUIElem *currentTarget;


// Change names for greater undertandability
// Active -> Enabled
//
void SDLX_ResetInput(int key);

void SDLX_GUIInit(void)
{
	_intern.GUI = calloc(GUICT, sizeof(SDLX_GUIInfo));
	_intern.GUIMax = GUICT;
	_intern.GUICount = 0;
	defaultTarget = NULL;
	currentTarget = NULL;
	selector = SDLX_KEYBOARD;
}


//Change this to linked list /array
SDLX_GUIElem *SDLX_GUIElem_Create(SDLX_Sprite *sprite, const char *name,
			SDLX_UIFunc isSelectFn,
			SDLX_UIFunc OnSelectEnterFn,SDLX_UIFunc OnSelectExitFn,
			SDLX_UIFunc OnSelectStayFn,	SDLX_UIFunc OnClickFn)
{
	size_t i;

	i = _intern.GUICount;

	if (i >= _intern.GUIMax)
	{
		_intern.GUIMax *= 2;
		_intern.GUI = SDL_realloc(_intern.GUI, _intern.GUIMax * sizeof(SDLX_GUIInfo));
	}
	if (sprite)
	{
		_intern.GUI[i].elem.sprite = *sprite;
 	}

	(_intern.GUI[i].elem.sprite.dstptr == NULL)
		? (_intern.GUI[i].elem.sprite.dstptr = &_intern.GUI[i].elem.sprite.dst)
		: (NULL);
	_intern.GUI[i].elem.name = name;
	_intern.GUI[i].elem.metadata = &_intern.GUI[i].meta;
	_intern.GUI[i].elem.autotrigger = 	SDLX_TRUE;

	_intern.GUI[i].meta.cd				= 10;
	_intern.GUI[i].meta.type			= SDLX_BUTTON;
	_intern.GUI[i].meta.active			= SDLX_FALSE;
	_intern.GUI[i].meta.selectStatus	= SDLX_NONE;

	_intern.GUI[i].meta.isSelectFn 		= isSelectFn;

	_intern.GUI[i].meta.UIFuncs[STARTSELECT]= OnSelectEnterFn;
	_intern.GUI[i].meta.UIFuncs[STAY] 		= OnSelectStayFn;
	_intern.GUI[i].meta.UIFuncs[ENDSELECT]	= OnSelectExitFn;
	_intern.GUI[i].meta.UIFuncs[CLICKED]	= OnClickFn;

	_intern.GUICount++;
	return &(_intern.GUI[i].elem);
}

void	SDLX_GUIElem_SetActive(SDLX_GUIElem *elem, int isActive)
{
	elem->metadata->active = isActive;
	SDL_Log("Button %p %p", elem, elem->sprite.animator);
	if (elem->sprite.animator)
	{
		elem->sprite.animator->active = isActive;
		elem->sprite.animator->frameNo = 0;
		elem->sprite.animator->state = 0;
	}
}

void SDLX_GUI_KeyMap(int up, int down, int left, int right, int select)
{
	GUI_KEYS[U] = up;
	GUI_KEYS[D] = down;
	GUI_KEYS[L] = left;
	GUI_KEYS[R] = right;
	GUI_KEYS[SELECT] = select;
}

void	SDLX_GUIElem_SetDefaultTarget(SDLX_GUIElem *def) { defaultTarget = def; def->metadata->selectStatus = SDLX_NONE;
	currentTarget = def;
	def->triggered = SDLX_FALSE;
}

void	SDLX_GUIElem_SetKbTarget(SDL_UNUSED int Target,SDLX_GUIElem *target, SDLX_GUIElem *up, SDLX_GUIElem *down, SDLX_GUIElem *left, SDLX_GUIElem *right)
{
	target->metadata->neighbours[U] = up;
	target->metadata->neighbours[D] = down;
	target->metadata->neighbours[L] = left;
	target->metadata->neighbours[R] = right;
}

int count(int *c, int max)
{
	if (!(*c))
	{
		*c = max;
		return 0;
	}
	*c -= 1;
	return 1;
}

int _MouseUpdate(SDLX_GUIElem *elem)
{
	SDLX_Input input;
	int select;
	int mouseHover;

	input = SDLX_InputGet();
	elem->triggered = 0;
	select = elem->metadata->selectStatus;
	mouseHover = SDLX_MouseInRect(input.mouse.x, input.mouse.y, *elem->sprite.dstptr);
	if (!mouseHover && currentTarget == elem)
	{
		select = SDLX_FALSE;
	}
	else if (mouseHover && select == STARTSELECT)
		select = SDLX_TRUE;
	else if (mouseHover && select == SDLX_NONE)
	{
		select = SDLX_TRUE;
	}
	else if (!mouseHover && select != SDLX_NONE)
		select = SDL_FALSE;
	if (elem->autotrigger == SDLX_TRUE)
	{
		elem->triggered = (input.mouse_click == SDL_MOUSEBUTTONDOWN);
	}

	return select;
}


int _KBUpdate(SDLX_GUIElem *elem)
{
	int select;
	SDLX_GUIMeta *meta;

	meta = elem->metadata;
	select = elem->metadata->selectStatus;
	if (elem == currentTarget)
	{
		for (int i = 0; i < 4; i++)
		{
			if ((KEYSDATA[i] == SDLX_KEYDOWN || (KEYSDATA[i] == SDLX_KEYHELD && !count(&(meta->cd), 10)))
			&& elem->metadata->neighbours[i])
			{
				select = 0;
				currentTarget = elem->metadata->neighbours[i];
				currentTarget->metadata->selectStatus = 1;
				KEYSDATA[i] = SDLX_NONE;
				break ;
			}
		}
		if (elem->autotrigger)
		{
			elem->triggered = (KEYSDATA[4] == SDLX_KEYDOWN);
		}
	}

	return select;
}

int SDLX_DefaultGUISelect(SDLX_GUIElem *elem)
{
	int select;

	select = SDLX_FALSE;
	if (selector & 1 || ((selector >> 1) & 1))
		select = _MouseUpdate(elem);
	if (selector == 0)
		select = _KBUpdate(elem);

	return select;
}

int		_GetSelector(void)
{
	SDLX_Input	input;

	int			newselector;
	int			oldselector;

	input = SDLX_InputGet();
	oldselector = (selector << 1) & 2;
	newselector = 0;
	for (int i = 0; i < _intern.GUICount; i++)
	{
		if (_intern.GUI[i].meta.isSelectFn(&_intern.GUI[i].elem))
		{
			newselector = 1;
			break ;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		KEYSDATA[i] = SDLX_GetKeyMapState(GUI_KEYS[i]);
		if (KEYSDATA[i] == SDLX_KEYDOWN || KEYSDATA[i] == SDLX_KEYHELD)
		{
			newselector = 0;
			break ;
		}
	}
	KEYSDATA[4] = SDLX_GetKeyMapState(GUI_KEYS[4]);
	selector = oldselector + newselector;

	return 1;
}

void SDLX_GUIUpdate(void)
{
	int i;
	SDLX_GUIMeta *meta;
	SDLX_Input 	input;
	int mouseHover;
	int select;
	int oldSelect;


	_GetSelector();
	i = 0;

	while (i < _intern.GUICount)
	{
		meta = &_intern.GUI[i].meta;
		if (meta->active)
		{
			select =  meta->isSelectFn(&_intern.GUI[i].elem);
			oldSelect = meta->selectStatus;

			if (select == SDLX_TRUE && oldSelect == SDLX_FALSE)
				meta->UIFuncs[STARTSELECT](&_intern.GUI[i].elem);
			else if (select == SDLX_TRUE && oldSelect == SDLX_TRUE)
				meta->UIFuncs[STAY](&_intern.GUI[i].elem);
			else if (select == SDLX_FALSE && oldSelect == SDLX_TRUE)
				meta->UIFuncs[ENDSELECT](&_intern.GUI[i].elem);
			// SDL_Log("FUNC");
			meta->selectStatus = select;
			if (select != SDLX_FALSE && _intern.GUI[i].elem.triggered)
			{
				SDL_Log("Triggered %s\n", _intern.GUI[i].elem.name);
				meta->UIFuncs[CLICKED](&_intern.GUI[i].elem);
			}
			// if (&_intern.GUI[i]->autotrigger) Maybe?
			_intern.GUI[i].elem.triggered = SDLX_FALSE;
		}
			i++;
	}
}
