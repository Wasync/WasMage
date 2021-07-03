#include "SDLX/SDLX.h"
#include "SDL2/SDL_image.h"

# define ANIMS_CT 5

typedef struct SDLX_AnimatorMeta
{
	int			stateLock;
	int			nextAnim;
}				SDLX_AnimatorMeta;

typedef struct SDLX_AnimatorInfo
{
	SDLX_Animator	elem;
	SDLX_AnimatorMeta meta;
}				SDLX_AnimatorInfo;

typedef struct Anim_intern
{
	SDLX_AnimatorInfo *animators;

	size_t animatorMax;
	size_t animatorCount;
}			Anim_intern;

static Anim_intern _intern;

void SDLX_AnimInit(void)
{
	_intern.animatorCount = 0;
	_intern.animatorMax = ANIMS_CT;
	_intern.animators = calloc(ANIMS_CT, sizeof(SDLX_AnimatorInfo));
}

SDLX_Animator *SDLX_AnimatorCreate(SDLX_Animator *copy, SDLX_Anim **anims, int amount, SDL_Rect *dst)
{
	size_t i;

	i = _intern.animatorCount;

	if (i >= _intern.animatorMax)
	{
		_intern.animatorMax *= 2;
		SDL_realloc(_intern.animators, _intern.animatorMax);
	}
	if (copy)
	{
		_intern.animators[i].elem.amount = copy->amount;
		_intern.animators[i].elem.anims = copy->anims;
		_intern.animators[i].elem.dst = copy->dst;
		_intern.animators[i].elem.dstptr = &_intern.animators[i].elem.dst;
	}
	else
	{
		_intern.animators[i].elem.amount = amount;
		_intern.animators[i].elem.anims = anims;
	}
	if (dst)
	{
		_intern.animators[i].elem.dst = *dst;
		_intern.animators[i].elem.dstptr = &_intern.animators[i].elem.dst;
	}
	else
		_intern.animators[i].elem.dstptr = NULL;
	_intern.animators[i].elem.frameNo = 0;
	_intern.animators[i].elem.state = 0;

	_intern.animators[i].meta.stateLock = -1;
	_intern.animators[i].meta.nextAnim = -1;
	_intern.animators[i].elem.metadata = &_intern.animators[i].meta;
	_intern.animatorCount++;
	return &_intern.animators[i].elem;
}

//potentially pass destination ptr instead of returning alloc
SDLX_Anim	*SDLX_AnimLoad(SDL_Texture *tex, int cycle, int cell_w, int cell_h, SDL_bool loop, int x_off, int y_off)
{
	SDLX_Anim	*anim;
	SDLX_Display *display;
	int i;
	int x;
	int y;

	display = SDLX_DisplayGet();
	anim = calloc(1, sizeof(*anim));
	anim->cycle = cycle;
	anim->start = 0;
	anim->loop = loop;
	anim->queue = 0;
	anim->sprites = calloc(cycle, sizeof(SDLX_Sprite));

	i = 0;
	x = x_off;
	y = y_off;
	while (i < cycle)
	{
		anim->sprites[i].src.x = x;
		anim->sprites[i].src.y = y;
		anim->sprites[i].src.h = cell_h;
		anim->sprites[i].src.w = cell_w;
		anim->sprites[i].srcptr = &anim->sprites[i].src;

		anim->sprites[i].center.x = 0;
		anim->sprites[i].center.y = 0;
		anim->sprites[i].spriteSheet = tex;

		anim->sprites[i].angle = 0;
		x += cell_w;
		i++;
	}
	return anim;
}

void SDLX_AnimationUpdate(void)
{
	int i;
	int frame;
	int state;
	int queue;

	SDLX_Animator	*animator;
	SDLX_AnimatorMeta *meta;

	i = 0;
	while (i < _intern.animatorCount)
	{
		animator = &_intern.animators[i].elem;
		meta = _intern.animators[i].elem.metadata;
		frame = animator->frameNo;
		state = animator->state;
		queue = animator->anims[state]->queue;

		if (animator->anims[state]->loop != SDL_FALSE)
			animator->frameNo = (frame + 1) % animator->anims[state]->cycle;
		else
			animator->frameNo += 1 * (frame < animator->anims[state]->cycle - 1);
		if (animator->dstptr)
			animator->anims[state]->sprites[frame].dstptr = animator->dstptr;
		SDLX_RenderQueueAdd(queue, animator->anims[state]->sprites[frame]);
		if (meta->stateLock == frame)
		{
			SDL_Log("HERE FRAME %d\n", frame);
			meta->stateLock = -1;
			animator->state = meta->nextAnim;
			animator->frameNo = 0;
		}
		i++;
	}
}


//refactor this
void SDLX_Animator_StateSet(SDLX_Animator *anim,int newState, int awaitCurrent)
{
	SDLX_AnimatorMeta *meta;

	meta = anim->metadata;
	if (awaitCurrent == SDLX_AWAITANIM || awaitCurrent >= anim->anims[anim->state]->cycle)
	{
		meta->stateLock = anim->anims[anim->state]->cycle - 1;
		meta->nextAnim = newState;
	}
	else if (awaitCurrent > 0)
	{
		meta->stateLock = awaitCurrent;
		meta->nextAnim = newState;
	}
	else
	{
		meta->stateLock = -1;
		anim->frameNo = 0;
		anim->state = newState;
	}
}
