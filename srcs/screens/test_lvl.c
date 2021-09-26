# include "rush.h"
# include "MT_vec2.h"

#define ERR_MARGIN 20
#define CMP_MARGIN 3
#define NPATTERNS 4

typedef struct Stroke
{
	MT_Vector2 vec;
	SDL_Point start;
	SDL_Point end;
	// double angle;
}				Stroke;

static Stroke match[NPATTERNS];

void test_levelInit(void *arg)
{

	SDL_Log("Init Test level\n");
	match[0].vec.x = 100;
	match[0].vec.y = 0;

	match[1].vec.x = -100;
	match[1].vec.y = 0;

	match[2].vec.x = 0;
	match[2].vec.y = 100;

	match[3].vec.x = 0;
	match[3].vec.y = -100;
}

void test_level(void *arg)
{
	static int isdown;
	static int i = -1;
	static int c;
	static int n;
	SDLX_Input input;
	static Stroke stroke[4];
	static Stroke save;
	static Stroke cmp;

	input = SDLX_InputGet();

	if (input.mouse_click == SDL_MOUSEBUTTONDOWN)
	{
		i  = -1;
		if (!isdown)
		{
			n = 0;
			c = 0;
			isdown = SDLX_TRUE;
			stroke[n].start = input.mouse;
			stroke[n].end = input.mouse;
		}
		else if (isdown == SDLX_NONE)
			isdown = SDLX_FALSE;
	}
	if (isdown == SDLX_TRUE)
	{
		save = stroke[n];
		stroke[n].end = input.mouse;
		stroke[n].vec.x = stroke[n].end.x - stroke[n].start.x;
		stroke[n].vec.y = stroke[n].end.y - stroke[n].start.y;
		stroke[n].vec = MT_V2Normalize(stroke[n].vec);
		stroke[n].vec.x = stroke[n].vec.x * 100;
		stroke[n].vec.y = stroke[n].vec.y * 100;
		if (c > 10)
		{
			if (
				n < 3 &&
				(stroke[n].vec.x - cmp.vec.x < -CMP_MARGIN ||
				stroke[n].vec.x - cmp.vec.x > CMP_MARGIN ||
				stroke[n].vec.y - cmp.vec.y > CMP_MARGIN ||
				stroke[n].vec.y - cmp.vec.y < -CMP_MARGIN ))
				{
				SDL_Log("DIFF x %f y %f", stroke[n].vec.x - cmp.vec.x, stroke[n].vec.y - cmp.vec.y);
				// SDL_Log("??????????? %d %d %d %d",
				// 			stroke[n].vec.x - cmp.vec.x < -CMP_MARGIN ,
				// 	stroke[n].vec.x - cmp.vec.x > CMP_MARGIN,
				// 	stroke[n].vec.y - cmp.vec.y < CMP_MARGIN,
				// 	stroke[n].vec.y - cmp.vec.y < -CMP_MARGIN );
				// stroke[n] = save;
					n++;
					c = 0;
					stroke[n].start = input.mouse;
					stroke[n].end = input.mouse;
				}
		}
		else if (input.mouse_delta.x != 0 || input.mouse_delta.y != 0)
		{
			cmp = stroke[n];
			c++;
		}
	}
	if (input.mouse_click == SDL_MOUSEBUTTONUP && isdown)
	{
		isdown = SDLX_NONE;
		c = 0;
		// stroke[n].start = input.mouse;
		for (int x = 0; x < NPATTERNS; x++)
		{
			if (
				(stroke[n].vec.x <= match[x].vec.x + ERR_MARGIN &&
				stroke[n].vec.x >= match[x].vec.x - ERR_MARGIN)
				&&
				(stroke[n].vec.y <= match[x].vec.y + ERR_MARGIN &&
				stroke[n].vec.y >= match[x].vec.y - ERR_MARGIN)
			)
			{
			// SDL_Log("Attempt %d y: %d [ %d | %d ] \n");
				i = x;
				break ;
			}
		}
		if (i == SDLX_NONE)
			SDL_Log("No correction found");
		else
			SDL_Log("Similar to stroke %d", i);
	}
	if (i != -1)
	{
		SDL_SetRenderDrawColor(SDLX_DisplayGet()->renderer,0, 255, 0, 255);
		SDL_RenderDrawLine(SDLX_DisplayGet()->renderer, stroke[n].start.x, stroke[n].start.y, stroke[n].start.x + match[i].vec.x,
																						 stroke[n].start.y + match[i].vec.y);
	}
	for (int x = 0; x <= n; x++)
	{
		SDL_SetRenderDrawColor(SDLX_DisplayGet()->renderer, 255, 0, 0, 255);
		SDL_RenderDrawLine(SDLX_DisplayGet()->renderer, stroke[x].start.x, stroke[x].start.y, stroke[x].end.x, stroke[x].end.y);
		SDL_SetRenderDrawColor(SDLX_DisplayGet()->renderer, 0, 0, 0, 255);
	}
}



void test_levelCleanup(void *arg)
{
	SDL_Log("Cleanup Test level\n");
	// SDLX_GUIElem_SetActive(ctx.buttons[1], SDLX_FALSE);
}
