#include "SDLX/SDLX.h"
# define ANIMS_CT 5
# define QUEUE_CT 3
# define GUI_CT 10


/** In the future it would be beneficial to sperate this file
 * such that SDLX.c be only responsible for init and misc process (like adjusting FPS)
 * Users would have  to specify which part of SDLX to initialize
 *
 * WIll need to change some ints to bools, but maybe not
 */


// This struct to be visible within this file only
// It is necessary to internally keep track of input, animations and render queues in orde rto update them properly
// Any animator or rander queue not created with the functions within this file or not added via one of these functions
// cannot be kept track of and therefore cannot be automagically updated

typedef struct _SDLX_Intern
{
	SDLX_Display		*display;
	SDLX_GUIElem		*GUI;
	SDLX_Animator		*animators;
	SDLX_RenderQueue 	*renderQueues;

	int				animatorCount;
	int				queuesCount;
	int				GUICount;
	int				animatorMax;
	int				queuesMax;
	int				GUIMax;
}				_SDLX_Intern;

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

	struct coords { int x, y; };
}				SDLX_GUIMeta;

typedef struct SDLX_AnimatorMeta
{
	int			stateLock;
	int			nextAnim;
}				SDLX_AnimatorMeta;


static _SDLX_Intern _intern;

void SDLX_Init(void)
{
	int i;

	//SDL_Log("New Animator  %p\n", _intern.animators);
	i = 0;
	_intern.animatorCount = 0;
	_intern.animatorMax = ANIMS_CT;

	_intern.queuesCount = QUEUE_CT;
	_intern.queuesMax = QUEUE_CT;

	_intern.GUICount = 0;
	_intern.GUIMax = GUI_CT;

	_intern.display = SDLX_DisplayGet();
	_intern.GUI = calloc(GUI_CT, sizeof(SDLX_GUIElem));
	_intern.animators = calloc(ANIMS_CT, sizeof(SDLX_Animator));
	_intern.renderQueues = calloc(QUEUE_CT, sizeof(SDLX_RenderQueue));
	while (i < QUEUE_CT)
	{
		_intern.renderQueues[i].sprites = calloc(5,sizeof(SDLX_Sprite));
		_intern.renderQueues[i].amount = 0;
		_intern.renderQueues[i].capacity = 5;
		i++;
	}
}
void	SDLX_RenderQueueAdd(int queue, SDLX_Sprite sprite)
{
	// SDL_Log("Queue no %d\n", queue);
	if (queue < 0 || queue >= _intern.queuesCount)
		return ;
	if (_intern.renderQueues[queue].capacity <= _intern.renderQueues[queue].amount)
	{
		// SDL_Log("Too many sprites\n");
		_intern.renderQueues[queue].capacity *= 2;
		_intern.renderQueues[queue].sprites = SDL_realloc(_intern.renderQueues[queue].sprites,_intern.renderQueues[queue].capacity * sizeof(SDLX_Sprite));
	}
	_intern.renderQueues[queue].sprites[_intern.renderQueues[queue].amount] = sprite;
	// SDL_Log("Sprite set\n");
	_intern.renderQueues[queue].amount++;
}

// In case user needs a render q to modifiy it
SDLX_RenderQueue **SDLX_RenderQueue_FetchAll(int *amount)
{
	if (amount)
		*amount = _intern.queuesCount;

	return &_intern.renderQueues;
}

void SDLX_RenderQueue_Flush(int queueNo)
{
	// *amount = _intern.queuesCount;

	queueNo += 0;
}

// This create an aimator from sratch or as a copy of another.
// Indeed the copying may be useful if (when)  two different entities use the saem set of animatons and therefore
// might be on different frames / state of animation

SDLX_Animator *SDLX_AnimatorCreate(SDLX_Animator *copy, SDLX_Anim **anims, int amount, SDL_Rect *dst)
{
	int i;

	i = _intern.animatorCount;
	//SDL_Log("Instantiating animator %d\n", i);
	if (i >= _intern.animatorMax)
	{
		_intern.animatorMax *= 2;
		SDL_realloc(_intern.animators, _intern.animatorMax);
	}
	if (copy)
	{
		_intern.animators[i].amount = copy->amount;
		_intern.animators[i].anims = copy->anims;
		_intern.animators[i].dst = copy->dst;
		_intern.animators[i].dstptr = &_intern.animators[i].dst;
	}
	else
	{
		_intern.animators[i].amount = amount;
		_intern.animators[i].anims = anims;
	}
	if (dst)
	{
		_intern.animators[i].dst = *dst;
		_intern.animators[i].dstptr = &_intern.animators[i].dst;
	}
	else
		_intern.animators[i].dstptr = NULL;
	_intern.animators[i].frameNo = 0;
	_intern.animators[i].state = 0;
	_intern.animatorCount++;
	return &_intern.animators[i];
}

SDLX_GUIElem *SDLX_GUIElem_Create(SDLX_Animator *animator, const char *name,
			SDLX_UIFunc OnSelectEnterFn,SDLX_UIFunc OnSelectExitFn,
			SDLX_UIFunc OnSelectStayFn,	SDLX_UIFunc OnClickHeldFn,
			SDLX_UIFunc OnClickFn,	SDLX_UIFunc OnClickReleaseFn)
{
	int i;
	SDLX_GUIMeta *meta;

	i = _intern.GUICount;
	meta = calloc(1, sizeof(*meta));

	if (i >= _intern.GUIMax)
	{
		_intern.GUIMax *= 2;
		SDL_realloc(_intern.GUI, _intern.GUIMax);
	}
	_intern.GUI[i].animator = animator;
	_intern.GUI[i].metadata = meta;
	_intern.GUI[i].name = name;

	meta->type = SDLX_BUTTON;
	meta->active = SDLX_FALSE;
	meta->OnSelectEnter = OnSelectEnterFn;
	meta->OnSelectStay = OnSelectStayFn;
	meta->OnSelectExit = OnSelectExitFn;
	meta->OnClick	  = OnClickFn;
	meta->OnClickStay = OnClickHeldFn;
	meta->OnClickExit = OnClickReleaseFn;
	/** Potentially in SetKBCoords
	 * If iskbtarget & AUTO
	 * set kb taget to auto
	 *	some func to figure out coords based on relative pos. Need a button set to 0,0
	 * else if iskbtarget & TRUE
	 * 	set kbtarget to true:
	 *  get coord from other func unless auto then if function called do nothing
	 */
	_intern.GUICount++;
	return &(_intern.GUI[i]);
}

void			SDLX_GUIElem_SetActive(SDLX_GUIElem *elem, int isActive)
{
	SDLX_GUIMeta *meta;

	meta = elem->metadata;
	meta->active = isActive;
}

void SDLX_Animator_StateSet(SDLX_Animator *anim,int newState, int awaitCurrent)
{
	SDLX_AnimatorMeta *meta;

	meta = anim->metadata;
	if (awaitCurrent == SDLX_AWAITANIM || awaitCurrent > anim->anims[anim->state]->cycle)
	{
		meta->stateLock = awaitCurrent;
		meta->nextAnim = newState;
	}
	else
	{
		anim->state = newState;
		anim->frameNo = 0;
	}
}

void SDLX_GUIUpdate(void)
{
	int i;

	SDLX_Input input;

	SDLX_GUIMeta *meta;

	input = SDLX_InputGet();
	i = 0;
	while (i < _intern.GUICount)
	{
		meta = _intern.GUI[i].metadata;
		if (meta->active)
		{
			if (SDLX_MouseIntersectRect(input.mouse_x, input.mouse_y, _intern.GUI[i].animator->dst))
			{
				
				if (meta->isSelect == SDLX_TRUE)
				{
					meta->OnSelectStay(&(_intern.GUI[i]));
				}
				else
				{
					meta->isSelect = SDLX_TRUE;
					meta->OnSelectEnter(&(_intern.GUI[i]));
				}
			}
			else
			{
				if (meta->isSelect == SDLX_TRUE)
				{
					meta->isSelect = SDL_FALSE;
					meta->OnSelectExit(&(_intern.GUI[i]));
				}
			}
		}
		i++;
	}
}

void SDLX_AnimationUpdate(void)
{
	int i;
	int frame;
	int state;
	int queue;
	i = 0;
	while (i < _intern.animatorCount)
	{
		frame = _intern.animators[i].frameNo;
		state = _intern.animators[i].state;
		queue = _intern.animators[i].anims[state]->queue;
		if (_intern.animators[i].anims[state]->loop != SDL_FALSE)
			frame = (frame + 1) % _intern.animators[i].anims[state]->cycle;
		else
			frame += 1 * (frame < _intern.animators[i].anims[state]->cycle - 1);
		if (_intern.animators[i].dstptr)
			_intern.animators[i].anims[state]->sprites[frame].dstptr = _intern.animators[i].dstptr;
		SDL_Log("HERE FRAME %d\n", frame);
		SDLX_RenderQueueAdd(queue, _intern.animators[i].anims[state]->sprites[frame]);
		// SDL_Log("HERE");
		_intern.animators[i].frameNo = frame;
		i++;
	}
}


