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

	tex = SDL_CreateTextureFromSurface(SDLX_DisplayGet()->renderer, IMG_Load("Assets/phBG.png"));
	SDLX_BackgroundSet(tex);

	SDLX_LevelManagerAdd(0, main_menuInit, main_menu, main_menuCleanup);
	SDLX_LevelManagerAdd(1, main_levelInit, main_level, main_levelCleanup);
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
	ctx.buttons[0] = SDLX_GUIElem_Create(NULL, "Start", NULL, &MenuHover, &NullGUIFunc, &NullGUIFunc, &StartClick);
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
	ctx.buttons[1] = SDLX_GUIElem_Create(NULL, "Exit",NULL, &MenuHover, &NullGUIFunc, &NullGUIFunc, &ExitClick);
	animator = SDLX_AnimatorCreate(NULL, anim, 3, &dst, &ctx.buttons[1]->sprite);
	animator->state = 0;
	// // ANimator SetSprite () ?

	ctx.buttons[0]->autotrigger = SDLX_TRUE;
	// ctx.buttons[1]->autotrigger = SDLX_TRUE;
	ctx.buttons[0]->triggered = SDLX_FALSE;
	// ctx.buttons[1]->triggered = SDLX_FALSE;


	SDLX_GUIElem_SetActive(ctx.buttons[0], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx.buttons[1], SDLX_TRUE);
	SDLX_GUIElem_SetKbTarget(SDLX_FALSE, ctx.buttons[0], NULL, NULL, NULL, NULL);
	SDLX_GUIElem_SetDefaultTarget(ctx.buttons[0]);
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

	tex = SDL_CreateTextureFromSurface(SDLX_DisplayGet()->renderer, IMG_Load("Assets/DrawBeam.png"));
	beam = calloc(1, sizeof(SDLX_Anim));
	beam[0] = SDLX_AnimLoadVertical(tex, 8, 128, 16, SDL_TRUE, 0, 0);

	tex = SDL_CreateTextureFromSurface(SDLX_DisplayGet()->renderer, IMG_Load("Assets/scroll.png"));
	anim = calloc(1, sizeof(SDLX_Anim));
	anim[0] = SDLX_AnimLoadHorizontal(tex, 1, 192, 192, SDL_FALSE, 0, 0);
	scroll.x = WIN_W - 200;
	scroll.y = WIN_H - 200;
	scroll.w = 192;
	scroll.h = 192;
	animator = SDLX_AnimatorCreate(NULL, anim, 1, &scroll, NULL);

	tex = SDL_CreateTextureFromSurface(SDLX_DisplayGet()->renderer, IMG_Load("Assets/circle.png"));
	anim = calloc(1, sizeof(SDLX_Anim));

	dst.x = scroll.x + (scroll.w / 6);
	dst.y = scroll.y + ((scroll.h / 6) * 0.5);
	dst.w = (scroll.w / 6);
	dst.h = (scroll.h / 6);
	beamrect = dst;
	beamrect.w = 0;
	anim[0] = SDLX_AnimLoadHorizontal(tex, 1, 1800, 1800, SDL_TRUE, 0, 0);
	animator->state = 0;
	ctx.buttons[2] = SDLX_GUIElem_Create(animator->spriteptr, "1", NULL, &DrawButtonHover, &NullGUIFunc, &NullGUIFunc, &DrawButtonTrigger);
	ctx.buttons[2]->data = (void *)SDLX_AnimatorCreate(NULL, beam, 1, &beamrect, NULL);
	animator = SDLX_AnimatorCreate(NULL, anim, 1, &dst, &ctx.buttons[2]->sprite);

	// dst.x += (scroll.w / 6) * 1.5;
	// beamrect.x = dst.x;
	// animator = SDLX_AnimatorCreate(NULL, anim, 1, &dst);
	// animator->state = 0;
	// ctx.buttons[3] = SDLX_GUIElem_Create(animator, "2", NULL, &DrawButtonHover, &NullGUIFunc, &NullGUIFunc, &DrawButtonTrigger);
	// ctx.buttons[3]->data = (void *)SDLX_AnimatorCreate(NULL, beam, 1, &beamrect);

	// dst.x += (scroll.w / 6) * 1.5;
	// beamrect.x = dst.x;
	// animator = SDLX_AnimatorCreate(NULL, anim, 1, &dst);
	// animator->state = 0;
	// ctx.buttons[4] = SDLX_GUIElem_Create(animator, "3", NULL, &DrawButtonHover, &NullGUIFunc, &NullGUIFunc, &DrawButtonTrigger);
	// ctx.buttons[4]->data = (void *)SDLX_AnimatorCreate(NULL, beam, 1, &beamrect);

	// dst.x = scroll.x + (scroll.w / 6);
	// dst.y += (scroll.h / 6) * 1.6;
	// beamrect.x = dst.x;
	// beamrect.y = dst.y;
	// animator = SDLX_AnimatorCreate(NULL, anim, 1, &dst);
	// animator->state = 0;
	// ctx.buttons[5] = SDLX_GUIElem_Create(animator, "4", NULL, &DrawButtonHover, &NullGUIFunc, &NullGUIFunc, &DrawButtonTrigger);
	// ctx.buttons[5]->data = (void *)SDLX_AnimatorCreate(NULL, beam, 1, &beamrect);

	// dst.x += (scroll.w / 6) * 1.5;
	// beamrect.x = dst.x;
	// animator = SDLX_AnimatorCreate(NULL, anim, 1, &dst);
	// animator->state = 0;
	// ctx.buttons[6] = SDLX_GUIElem_Create(animator, "5", NULL, &DrawButtonHover, &NullGUIFunc, &NullGUIFunc, &DrawButtonTrigger);
	// ctx.buttons[6]->data = (void *)SDLX_AnimatorCreate(NULL, beam, 1, &beamrect);

	// dst.x += (scroll.w / 6) * 1.5;
	// beamrect.x = dst.x;
	// animator = SDLX_AnimatorCreate(NULL, anim, 1, &dst);
	// animator->state = 0;

	// dst.x = scroll.x + (scroll.w / 6);
	// dst.y += (scroll.h / 6) * 1.6;
	// beamrect.x = dst.x;
	// beamrect.y = dst.y;
	// ctx.buttons[7] = SDLX_GUIElem_Create(animator, "6", NULL, &DrawButtonHover, &NullGUIFunc, &NullGUIFunc, &DrawButtonTrigger);
	// ctx.buttons[7]->data = (void *)SDLX_AnimatorCreate(NULL, beam, 1, &beamrect);


	// animator = SDLX_AnimatorCreate(NULL, anim, 1, &dst);
	// animator->state = 0;
	// dst.x += (scroll.w / 6) * 1.5;
	// beamrect.x = dst.x;
	// ctx.buttons[8] = SDLX_GUIElem_Create(animator, "7", NULL, &DrawButtonHover, &NullGUIFunc, &NullGUIFunc, &DrawButtonTrigger);
	// ctx.buttons[8]->data = (void *)SDLX_AnimatorCreate(NULL, beam, 1, &beamrect);

	// animator = SDLX_AnimatorCreate(NULL, anim, 1, &dst);
	// animator->state = 0;
	// dst.x += (scroll.w / 6) * 1.5;
	// beamrect.x = dst.x;
	// ctx.buttons[9] = SDLX_GUIElem_Create(animator, "8", NULL, &DrawButtonHover, &NullGUIFunc, &NullGUIFunc, &DrawButtonTrigger);
	// ctx.buttons[9]->data = (void *)SDLX_AnimatorCreate(NULL, beam, 1, &beamrect);

	// animator = SDLX_AnimatorCreate(NULL, anim, 1, &dst);
	// animator->state = 0;
	// dst.x += (scroll.w / 6) * 1.5;
	// beamrect.x = dst.x;
	// ctx.buttons[10] = SDLX_GUIElem_Create(animator, "9", NULL, &DrawButtonHover, &NullGUIFunc, &NullGUIFunc, &DrawButtonTrigger);
	// ctx.buttons[10]->data = (void *)SDLX_AnimatorCreate(NULL, beam, 1, &beamrect);

	//probably replace the below with query texture to get the dimensions correct, just in case

	// ctx.buttons[11] = SDLX_GUIElem_Create(animator, "8", NULL, &NullGUIFunc, &NullGUIFunc, &NullGUIFunc, &NullGUIFunc);

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
	SDLX_GUIElem_SetDefaultTarget(ctx.buttons[2]);

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
	SDLX_GUIElem_SetActive(ctx.buttons[3], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx.buttons[4], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx.buttons[5], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx.buttons[6], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx.buttons[7], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx.buttons[8], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx.buttons[9], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx.buttons[10], SDLX_FALSE);
}

void test_levelCleanup(void *arg)
{
	SDL_Log("Cleanup Test level\n");
	SDLX_GUIElem_SetActive(ctx.buttons[1], SDLX_FALSE);
}
