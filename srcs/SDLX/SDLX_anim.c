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
	struct SDLX_AnimatorInfo *next;
}				SDLX_AnimatorInfo;

typedef struct Anim_intern
{
	SDLX_AnimatorInfo *head;
	SDLX_AnimatorInfo *tail;

	size_t animatorCount;
}			Anim_intern;

static Anim_intern _intern;

void SDLX_AnimInit(void)
{
	_intern.animatorCount = 0;
	_intern.head = calloc(1, sizeof(SDLX_AnimatorInfo));
	_intern.tail = _intern.head;
}

SDLX_Animator *SDLX_AnimatorCreate(SDLX_Animator *copy, SDLX_Anim **anims, int amount, SDL_Rect *dst, SDLX_Sprite *sprite)
{
	SDLX_AnimatorInfo *node;

	node =  calloc(1, sizeof(SDLX_AnimatorInfo));
	if (copy)
	{
		node->elem.anims = copy->anims;
		node->elem.amount = copy->amount;
		node->elem.sprite = copy->sprite;
		node->elem.spriteptr = &node->elem.sprite;
		node->elem.sprite.dstptr = &node->elem.sprite.dst;
	}
	else
	{
		node->elem.anims = anims;
		node->elem.amount = amount;
	}
	if (sprite)
	{
		node->elem.spriteptr = sprite;
		node->elem.sprite = *sprite;
	}
	else
	{
		SDLX_SpriteCreate(&node->elem.sprite, NULL, NULL, dst);
		node->elem.spriteptr = &node->elem.sprite;
		node->elem.spriteptr->srcptr = &node->elem.sprite.src;
	}
	if (dst)
	{
		node->elem.sprite.dst = *dst;
		if (sprite)
		{
			node->elem.spriteptr->dst = *dst;
			if (!node->elem.spriteptr->dstptr)
				node->elem.spriteptr->dstptr = &node->elem.spriteptr->dst;
		}
		// node->elem.sprite.dstptr = dst;
	}
	// else
	node->elem.sprite.dstptr = &node->elem.sprite.dst;

	node->elem.sprite.animator = &node->elem;
	node->elem.spriteptr->animator = &node->elem;
	node->elem.frameNo = 0;
	node->elem.state = 0;

	node->meta.stateLock = -1;
	node->meta.nextAnim = -1;
	node->elem.metadata = &node->meta;

	_intern.tail->next = node;
	_intern.tail = node;
	node->elem.active = SDLX_TRUE;

	SDL_Log("Sprite %p(%d, %d) , w %d, h %d\n",
	node->elem.spriteptr,
	node->elem.spriteptr->dstptr->x,
	node->elem.spriteptr->dstptr->y,
	node->elem.spriteptr->dstptr->w,
	node->elem.spriteptr->dstptr->h
	);

	SDL_Log("Anim %p", node->elem.spriteptr->animator);

	return &node->elem;
}

SDLX_Anim	*SDLX_AnimLoadVertical(SDL_Texture *tex, int cycle, int cell_w, int cell_h, SDL_bool loop, int x_off, int y_off)
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
	anim->srcs = calloc(cycle, sizeof(SDL_Rect));

	i = 0;
	x = x_off;
	y = y_off;
	anim->spriteSheet = tex;
	while (i < cycle)
	{
		anim->srcs[i].x = x;
		anim->srcs[i].y = y;
		anim->srcs[i].h = cell_h;
		anim->srcs[i].w = cell_w;

		y += cell_h;
		i++;
	}
	return anim;
}

//potentially pass destination ptr instead of returning alloc

SDLX_Anim	*SDLX_AnimLoadHorizontal(SDL_Texture *tex, int cycle, int cell_w, int cell_h, SDL_bool loop, int x_off, int y_off)
{
	SDLX_Anim	*anim;
	SDLX_Display *display;
	int i;
	int x;
	int y;

	anim = calloc(1, sizeof(*anim));
	anim->cycle = cycle;
	anim->start = 0;
	anim->loop = loop;
	anim->srcs = calloc(cycle, sizeof(SDL_Rect));

	i = 0;
	x = x_off;
	y = y_off;
	anim->spriteSheet = tex;
	while (i < cycle)
	{
		anim->srcs[i].x = x;
		anim->srcs[i].y = y;
		anim->srcs[i].h = cell_h;
		anim->srcs[i].w = cell_w;

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
	SDLX_AnimatorInfo *node;

	if (_intern.head)
	{
		node = _intern.head->next;
		i = 0;
		// SDL_Log("HERE");
		while (node != NULL)
		{
			if (node->elem.active == SDLX_TRUE && node->elem.anims)
			{
				animator = &node->elem;
				state = animator->state;
				frame = animator->frameNo;
				meta = node->elem.metadata;
				queue = animator->sprite.queue;
		// SDL_Log("NOT THERE");

				if (animator->anims[state]->loop != SDL_FALSE)
					animator->frameNo = (frame + 1) % animator->anims[state]->cycle;
				else
					animator->frameNo += 1 * (frame < animator->anims[state]->cycle - 1);
				animator->spriteptr->srcptr = &animator->anims[state]->srcs[frame];
				// SDL_Log("TEXTURE ADDRESS  CREATED %p", animator->anims[state]->spriteSheet);
				// SDL_Log("TEXTURE ADDRESS  CREATED  PTR %p", node->elem.spriteptr->spriteSheet);
				// SDL_Log("Sprite (%d, %d) , w %d, h %d\n",
							// animator->spriteptr->dst.x,
							// animator->spriteptr->dst.y,
							// animator->spriteptr->dst.w,
							// animator->spriteptr->dst.h
							// );

				animator->spriteptr->spriteSheet = animator->anims[state]->spriteSheet;

				SDLX_RenderQueueAdd(0, *animator->spriteptr);
				if (meta->stateLock == frame)
				{
					meta->stateLock = -1;
					animator->state = meta->nextAnim;
					animator->frameNo = 0;
				}
			}
			node = node->next;
		}
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
