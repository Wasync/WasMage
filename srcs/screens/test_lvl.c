# include "rush.h"
# include "MT_vec2.h"

#define ERR_MARGIN 22
#define ERR_DELTA 5
#define LEN 8

typedef struct Stroke
{
	MT_Vector2 vec;
	SDL_Point start;
	SDL_Point end;
	// double angle;
}				Stroke;

static Stroke match[LEN];

void test_levelInit(void *arg)
{

	SDL_Log("Init Test level\n");
	match[0].vec.x = 100;
	match[0].vec.y = 0;

	match[1].vec.x = 0;
	match[1].vec.y = 100;

	match[2].vec.x = -100;
	match[2].vec.y = 0;

	match[3].vec.x = 0;
	match[3].vec.y = -100;

	match[4].vec.x = 50;
	match[4].vec.y = 50;

	match[5].vec.x = -50;
	match[5].vec.y = -50;

	match[6].vec.x = -50;
	match[6].vec.y = 50;

	match[7].vec.x = 50;
	match[7].vec.y = -50;

}

void test_level(void *arg)
{
	static int isdown;
	static int i = -1;
	static int c;
	SDLX_Input input;
	static Stroke stroke;
	static MT_Vector2 delta;

	input = SDLX_InputGet();

	if (isdown == SDLX_TRUE)
	{
		// c++;
		stroke.end = input.mouse;
		stroke.vec.x = stroke.end.x - stroke.start.x;
		stroke.vec.y = stroke.end.y - stroke.start.y;
		stroke.vec = MT_V2Normalize(stroke.vec);
		stroke.vec.x = stroke.vec.x * 100;
		stroke.vec.y = stroke.vec.y * 100;
		if (input.mouse_delta.x != 0 && input.mouse_delta.y != 0)
		{
			// SDL_Log("Delta %f,%f", delta.x, delta.y);
			// SDL_Log("STROKE %f,%f", stroke.vec.x, stroke.vec.y);
			SDL_Log("Attempt x: %f [ %f | %f ] \n",  stroke.vec.x , delta.x + ERR_DELTA, delta.x - ERR_DELTA);
			SDL_Log("Attempt y: %f [ %f | %f ] \n",  stroke.vec.y , delta.y + ERR_DELTA, delta.y - ERR_DELTA);
			if (
				!((stroke.vec.x <= delta.x + ERR_DELTA &&
				stroke.vec.x >= delta.x - ERR_DELTA)
				&&
				(stroke.vec.y <= delta.y + ERR_DELTA &&
				stroke.vec.y >= delta.y - ERR_DELTA))
				&&
				(delta.x != 0 && delta.y != 0))

			{
				isdown = SDLX_NONE;
				SDL_Log("END STROKE");
			}
		}
		delta.x = stroke.vec.x;
		delta.y = stroke.vec.y;
	}
	if (input.mouse_click == SDL_MOUSEBUTTONDOWN)
	{
		c = 0;
		i  = -1;
		if (!isdown)
		{
			isdown = SDLX_TRUE;
			stroke.start = input.mouse;
			stroke.end = input.mouse;
			delta.x = 0;
			delta.y = 0;
		}
		else if (isdown == SDLX_NONE)
			isdown = SDLX_FALSE;
	}
	if (input.mouse_click == SDL_MOUSEBUTTONUP && isdown)
	{
		isdown = SDLX_NONE;
		stroke.vec.x = stroke.end.x - stroke.start.x;
		stroke.vec.y = stroke.end.y - stroke.start.y;
		// SDL_Log("Got stroke vec (%f,%f)", stroke.vec.x, stroke.vec.y);
		SDL_Log("Got stroke vec (%f,%f)", delta.x, delta.y);
		// stroke.vec = MT_V2Normalize(stroke.vec);
		// stroke.vec.x = stroke.vec.x * 100;
		// stroke.vec.y = stroke.vec.y * 100;
		// SDL_Log("Normalized (%f,%f)", stroke.vec.x, stroke.vec.y);
		// stroke.start = input.mouse;
		for (int x = 0; x < LEN; x++)
		{

			if (
				(delta.x <= match[x].vec.x + ERR_MARGIN &&
				delta.x >= match[x].vec.x - ERR_MARGIN)
				&&
				(delta.y <= match[x].vec.y + ERR_MARGIN &&
				delta.y >= match[x].vec.y - ERR_MARGIN)
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
		SDL_RenderDrawLine(SDLX_DisplayGet()->renderer, stroke.start.x, stroke.start.y, stroke.start.x + match[i].vec.x,
																						 stroke.start.y + match[i].vec.y);
	}
	SDL_SetRenderDrawColor(SDLX_DisplayGet()->renderer, 255, 0, 0, 255);
	SDL_RenderDrawLine(SDLX_DisplayGet()->renderer, stroke.start.x, stroke.start.y, stroke.end.x, stroke.end.y);
	SDL_SetRenderDrawColor(SDLX_DisplayGet()->renderer, 0, 0, 0, 255);
}



void test_levelCleanup(void *arg)
{
	SDL_Log("Cleanup Test level\n");
	// SDLX_GUIElem_SetActive(ctx.buttons[1], SDLX_FALSE);
}
