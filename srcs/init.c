# include "rush.h"

static Context ctx;
static MainLevel mainlvl;

Context *getCtx(void){return &ctx;}

Context *init_game(void)
{
	SDL_Texture *tex;

    SDLX_Start("Rush", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_H, WIN_W, SDL_WINDOW_SHOWN);
	SDLX_InputMap(SDL_SCANCODE_UP,		SDLX_KEYBOARD, SDLX_UP, 	0b00000001, -1);
	SDLX_InputMap(SDL_SCANCODE_W,		SDLX_KEYBOARD, SDLX_UP,		0b00000001, -1);
	SDLX_InputMap(SDL_SCANCODE_DOWN,	SDLX_KEYBOARD, SDLX_DOWN,	0b00000001, -1);
	SDLX_InputMap(SDL_SCANCODE_S, 		SDLX_KEYBOARD, SDLX_DOWN,	0b00000001, -1);
	SDLX_InputMap(SDL_SCANCODE_LEFT,	SDLX_KEYBOARD, SDLX_LEFT,	0b00000001, -1);
	SDLX_InputMap(SDL_SCANCODE_A,		SDLX_KEYBOARD, SDLX_LEFT, 	0b00000001, -1);
	SDLX_InputMap(SDL_SCANCODE_RIGHT,	SDLX_KEYBOARD, SDLX_RIGHT, 	0b00000001, -1);
	SDLX_InputMap(SDL_SCANCODE_D,		SDLX_KEYBOARD, SDLX_RIGHT, 	0b00000001, -1);
	SDLX_InputMap(SDL_SCANCODE_SPACE, 	SDLX_KEYBOARD, SDLX_PAUSE, 	0b00000001, -1);
	SDLX_InputMap(SDL_SCANCODE_KP_ENTER,SDLX_KEYBOARD, SDLX_PAUSE, 	0b00000001, -1);

	SDLX_GUI_KeyMap(SDLX_UP, SDLX_DOWN, SDLX_LEFT, SDLX_RIGHT, SDLX_PAUSE);

	// tex = SDL_CreateTextureFromSurface(SDLX_DisplayGet()->renderer, IMG_Load("Assets/phBG.png"));
	// SDLX_BackgroundSet(tex);

	// SDLX_LevelManagerAdd(0, main_menuInit, main_menu, main_menuCleanup);
	SDLX_LevelManagerAdd(0, main_levelInit, main_level, main_levelCleanup);
	// SDLX_LevelManagerAdd(1, test_levelInit, test_level, test_levelCleanup);
	// SDLX_LevelManagerAdd(2, test_levelInit, test_level, test_levelCleanup);
	SDLX_LevelManagerStart(0, &ctx);
	SDL_Log("Init Game\n");
	return &ctx;
}

// init

void nhover(SDLX_GUIElem *elem)
{
	SDL_Log("Exit");
}

void main_menuInit(void *arg)
{
	SDLX_Animator *animator;
	SDLX_Anim	**anim;
	SDL_Texture *tex;
	SDL_Rect dst;

	dst.x = WIN_W / 2 - (32 * W_SCALE);
	dst.y = WIN_W / 2 - (64 * H_SCALE);
	dst.w = 64 * W_SCALE;
	dst.h = 64 * 1.25;

	tex = SDL_CreateTextureFromSurface(SDLX_DisplayGet()->renderer, IMG_Load("Assets/Button_SpriteSheet.png"));
	anim = calloc(3, sizeof(SDLX_Anim));
	anim[2] = SDLX_AnimLoadHorizontal(tex, 2, 64, 64, SDL_FALSE, 64 * 8, 0);
	anim[0] = SDLX_AnimLoadHorizontal(tex, 1, 64, 64, SDL_TRUE, 0, 0);
	anim[1] = SDLX_AnimLoadHorizontal(tex, 8, 64, 64, SDL_FALSE, 64, 0);
	ctx.buttons[0] = SDLX_GUIElem_Create(NULL, "Start", &SDLX_DefaultGUISelect, &MenuHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &StartClick);
	animator = SDLX_AnimatorCreate(NULL, anim, 3, &dst, &ctx.buttons[0]->sprite);

	animator->state = 0;
	dst.x = WIN_W / 2 - (32 * W_SCALE);
	dst.y = WIN_W - 80;
	dst.w = 64 * W_SCALE;
	dst.h = 64 * 1.25;
	anim = calloc(3, sizeof(SDLX_Anim));
	anim[2] = SDLX_AnimLoadHorizontal(tex, 2, 64, 64, SDL_FALSE, 64 * 8, 64);
	anim[0] = SDLX_AnimLoadHorizontal(tex, 1, 64, 64, SDL_TRUE, 0, 64);
	anim[1] = SDLX_AnimLoadHorizontal(tex, 8, 64, 64, SDL_FALSE, 64, 64);
	ctx.buttons[1] = SDLX_GUIElem_Create(NULL, "Exit", &SDLX_DefaultGUISelect, &MenuHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &ExitClick);
	animator = SDLX_AnimatorCreate(NULL, anim, 3, &dst, &ctx.buttons[1]->sprite);
	animator->state = 0;
	// // ANimator SetSprite () ?

	ctx.buttons[0]->autotrigger = SDLX_TRUE;
	// ctx.buttons[1]->autotrigger = SDLX_TRUE;
	ctx.buttons[0]->triggered = SDLX_FALSE;
	// ctx.buttons[1]->triggered = SDLX_FALSE;

	SDL_Log("Button %p", ctx.buttons[0]);
	SDLX_GUIElem_SetActive(ctx.buttons[0], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx.buttons[1], SDLX_TRUE);
	// SDLX_GUIElem_SetKbTarget(SDLX_FALSE, ctx.buttons[0], NULL, NULL, NULL, NULL);
	// SDLX_GUIElem_SetDefaultTarget(ctx.buttons[0]);
	SDL_Log("MainMenu Init \n");
	// SDL_Log("Args [ %s ] \n", (char *)arg);
}

void test_levelInit(void *arg)
{
	(void)arg;
}

void main_levelInit(void *arg)
{
	SDLX_Animator *animator;
	SDLX_Anim	**anim;
	SDLX_Anim	**beam;
	SDL_Texture *tex;
	SDL_Rect scroll;
	SDL_Rect beamrect;
	SDL_Rect dst;
	SDLX_Sprite sprite;

	tex = SDLX_LoadTexture("Assets/DrawBeam.png", SDLX_DisplayGet());
	beam = calloc(1, sizeof(SDLX_Anim));
	beam[0] = SDLX_AnimLoadVertical(tex, 8, 128, 16, SDL_TRUE, 0, 0);

	tex = SDLX_LoadTexture("Assets/scroll.png", SDLX_DisplayGet());
	// SDL_Log("Spritens %p", ctx.sprites[0]);
	scroll.h = 128 * 2.25;
	scroll.w = 64 *2.25;
	scroll.x = WIN_W - scroll.w - 10;
	scroll.y = WIN_H - scroll.h ;

	SDL_Log("(%d, %d)", scroll.x, scroll.y);
	SDLX_SpriteCreate(&ctx.sprites[0] , tex, NULL, &scroll);

	ctx.sprites[0].srcptr = NULL;
	ctx.nsprites++;

	/*
		Mouse (547,655) (76,68)
		Mouse (510,689) (39,102)
		Mouse (532,688) (61,101)
		Mouse (559,687) (88,100)
		Mouse (575,687) (104,100)
		Mouse (567,722) (96,135)
		Mouse (540,724) (69,137)
		Mouse (518,724) (47,137)
		Mouse (515,752) (44,165)
		Mouse (529,754) (58,167)
		Mouse (559,755) (88,168)
		Mouse (581,755) (110,168)
		Mouse (545,791) (74,204)

		: Mouse (545,654) (74,67)
2021-08-07 12:26:41.547 rush[22737:393407] INFO: Shape
2021-08-07 12:26:41.548 rush[22737:393407] INFO: Shape 0
2021-08-07 12:26:45.035 rush[22737:393407] INFO: Mouse (532,686) (61,99)
2021-08-07 12:26:47.214 rush[22737:393407] INFO: Mouse (510,687) (39,100)
2021-08-07 12:26:49.097 rush[22737:393407] INFO: Mouse (553,688) (82,101)
2021-08-07 12:26:50.175 rush[22737:393407] INFO: Mouse (575,690) (104,103)
2021-08-07 12:26:51.063 rush[22737:393407] INFO: Mouse (565,723) (94,136)
2021-08-07 12:26:53.542 rush[22737:393407] INFO: Mouse (543,723) (72,136)
2021-08-07 12:26:54.793 rush[22737:393407] INFO: Mouse (521,723) (50,136)
2021-08-07 12:26:56.562 rush[22737:393407] INFO: Mouse (510,753) (39,166)
2021-08-07 12:26:58.348 rush[22737:393407] INFO: Mouse (531,753) (60,166)
2021-08-07 12:26:59.338 rush[22737:393407] INFO: Mouse (557,754) (86,167)
2021-08-07 12:27:00.506 rush[22737:393407] INFO: Mouse (580,757) (109,170)
2021-08-07 12:27:02.612 rush[22737:393407] INFO: Mouse (546,786) (75,199)
		*/

///TOP MOST POINT///
	dst.h = 10;
	dst.w = 10;
	tex = SDLX_LoadTexture("Assets/circle.png", SDLX_DisplayGet());
	dst.x = scroll.x + 68;
	dst.y = scroll.y + 60;
	SDLX_SpriteCreate(&ctx.sprites[ctx.nsprites] , tex, NULL, &dst);
	ctx.sprites[ctx.nsprites].srcptr = NULL;
	ctx.nsprites++;



	ctx.buttons[2] = SDLX_GUIElem_Create(NULL, "0", &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	SDLX_AnimatorCreate(NULL, beam, 1, &dst, &ctx.buttons[2]->sprite);
	ctx.buttons[2]->sprite.animator->active = SDLX_FALSE;
	ctx.buttons[2]->autotrigger = SDLX_TRUE;

// TOP LINE ///
	dst.x = scroll.x + 32;
	dst.y = scroll.y + 93;
	SDLX_SpriteCreate(&ctx.sprites[ctx.nsprites] , tex, NULL, &dst);
	ctx.sprites[ctx.nsprites].srcptr = NULL;
	ctx.nsprites++;
	// ctx.buttons[10]->data = (void *)SDLX_AnimatorCreate(NULL, beam, 1, &beamrect);
	dst.x = scroll.x + 55;
	dst.y = scroll.y + 93;
	SDLX_SpriteCreate(&ctx.sprites[ctx.nsprites] , tex, NULL, &dst);
	ctx.sprites[ctx.nsprites].srcptr = NULL;
	ctx.nsprites++;

	dst.x = scroll.x + 80;
	dst.y = scroll.y + 93;
	SDLX_SpriteCreate(&ctx.sprites[ctx.nsprites] , tex, NULL, &dst);
	ctx.sprites[ctx.nsprites].srcptr = NULL;
	ctx.nsprites++;

	dst.x = scroll.x + 104;
	dst.y = scroll.y + 93;
	SDLX_SpriteCreate(&ctx.sprites[ctx.nsprites] , tex, NULL, &dst);
	ctx.sprites[ctx.nsprites].srcptr = NULL;
	ctx.nsprites++;

//// MIDDLE LINE //////////

	dst.x = scroll.x + 45;
	dst.y = scroll.y + 128;
	SDLX_SpriteCreate(&ctx.sprites[ctx.nsprites] , tex, NULL, &dst);
	ctx.sprites[ctx.nsprites].srcptr = NULL;
	ctx.nsprites++;

	dst.x = scroll.x + 68;
	dst.y = scroll.y + 128;
	SDLX_SpriteCreate(&ctx.sprites[ctx.nsprites] , tex, NULL, &dst);
	ctx.sprites[ctx.nsprites].srcptr = NULL;
	ctx.nsprites++;

	dst.x = scroll.x + 90;
	dst.y = scroll.y + 128;
	SDLX_SpriteCreate(&ctx.sprites[ctx.nsprites] , tex, NULL, &dst);
	ctx.sprites[ctx.nsprites].srcptr = NULL;
	ctx.nsprites++;






//// BOTTOM LINE ////////
	dst.x = scroll.x + 32;
	dst.y = scroll.y + 160;
	SDLX_SpriteCreate(&ctx.sprites[ctx.nsprites] , tex, NULL, &dst);
	ctx.sprites[ctx.nsprites].srcptr = NULL;
	ctx.nsprites++;
	// ctx.buttons[10]->data = (void *)SDLX_AnimatorCreate(NULL, beam, 1, &beamrect);
	dst.x = scroll.x + 55;
	dst.y = scroll.y + 160;
	SDLX_SpriteCreate(&ctx.sprites[ctx.nsprites] , tex, NULL, &dst);
	ctx.sprites[ctx.nsprites].srcptr = NULL;
	ctx.nsprites++;

	dst.x = scroll.x + 80;
	dst.y = scroll.y + 160;
	SDLX_SpriteCreate(&ctx.sprites[ctx.nsprites] , tex, NULL, &dst);
	ctx.sprites[ctx.nsprites].srcptr = NULL;
	ctx.nsprites++;

	dst.x = scroll.x + 104;
	dst.y = scroll.y + 160;
	SDLX_SpriteCreate(&ctx.sprites[ctx.nsprites] , tex, NULL, &dst);
	ctx.sprites[ctx.nsprites].srcptr = NULL;
	ctx.nsprites++;


//BOTTOM MOST POINT
	dst.x = scroll.x + 68;
	dst.y = scroll.y + 195;
	SDLX_SpriteCreate(&ctx.sprites[ctx.nsprites] , tex, NULL, &dst);
	ctx.sprites[ctx.nsprites].srcptr = NULL;
	ctx.nsprites++;
	// ctx.buttons[10]->data = (void *)SDLX_AnimatorCreate(NULL, beam, 1, &beamrect);

	//probably replace the below with query texture to get the dimensions correct, just in case

	// ctx.buttons[11] = SDLX_GUIElem_Create(animator, "8", NULL, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc);

	SDLX_GUIElem_SetActive(ctx.buttons[2], SDLX_TRUE);
	// SDLX_GUIElem_SetActive(ctx.buttons[3], SDLX_TRUE);
	// SDLX_GUIElem_SetActive(ctx.buttons[4], SDLX_TRUE);
	// SDLX_GUIElem_SetActive(ctx.buttons[5], SDLX_TRUE);
	// SDLX_GUIElem_SetActive(ctx.buttons[6], SDLX_TRUE);
	// SDLX_GUIElem_SetActive(ctx.buttons[7], SDLX_TRUE);
	// SDLX_GUIElem_SetActive(ctx.buttons[8], SDLX_TRUE);
	// SDLX_GUIElem_SetActive(ctx.buttons[9], SDLX_TRUE);
	// SDLX_GUIElem_SetActive(ctx.buttons[10], SDLX_TRUE);
	// SDLX_GUIElem_SetActive(ctx.buttons[11], SDLX_TRUE);
	// SDLX_GUIElem_SetDefaultTarget(ctx.buttons[2]);

	mainlvl.norder = 0;
	mainlvl.drawing = SDLX_FALSE;
	ctx.lvl_data = &mainlvl;
	SDL_Log("Init test lvl\n");
}

void main_menuCleanup(void *arg)
{
	SDL_Log("Cleanup main menu\n");
	SDLX_GUIElem_SetActive(ctx.buttons[0], SDLX_FALSE);
}

void main_levelCleanup(void *arg)
{
	SDL_Log("Cleanup main lvl\n");
	SDLX_GUIElem_SetActive(ctx.buttons[2], SDLX_FALSE);
	// SDLX_GUIElem_SetActive(ctx.buttons[3], SDLX_FALSE);
	// SDLX_GUIElem_SetActive(ctx.buttons[4], SDLX_FALSE);
	// SDLX_GUIElem_SetActive(ctx.buttons[5], SDLX_FALSE);
	// SDLX_GUIElem_SetActive(ctx.buttons[6], SDLX_FALSE);
	// SDLX_GUIElem_SetActive(ctx.buttons[7], SDLX_FALSE);
	// SDLX_GUIElem_SetActive(ctx.buttons[8], SDLX_FALSE);
	// SDLX_GUIElem_SetActive(ctx.buttons[9], SDLX_FALSE);
	// SDLX_GUIElem_SetActive(ctx.buttons[10], SDLX_FALSE);
}

void test_levelCleanup(void *arg)
{
	SDL_Log("Cleanup Test level\n");
	SDLX_GUIElem_SetActive(ctx.buttons[1], SDLX_FALSE);
}
