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
	// SDLX_LevelManagerAdd(0, test_levelInit, test_level, test_levelCleanup);
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
}

void test_levelInit(void *arg)
{
	SDLX_Animator *animator;
	SDLX_Anim	**anim;
	SDL_Texture *tex;
	SDL_Rect dst;
	int i;

	(void)arg;

	// ctx.current = &ctx.spells[0];
	SDL_Log("SPrite %p anim %p", ctx.active[0].sprite.dstptr, ctx.spells[0].sprite.dstptr );

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
	int i;

	tex = SDLX_LoadTexture("Assets/DrawBeam.png", SDLX_DisplayGet());
	beam = calloc(1, sizeof(SDLX_Anim));
	beam[0] = SDLX_AnimLoadVertical(tex, 8, 128, 16, SDL_TRUE, 0, 0);

	tex = SDLX_LoadTexture("Assets/scroll.png", SDLX_DisplayGet());
	scroll.h = 128 * 2.25;
	scroll.w = 64 *2.25;
	scroll.x = WIN_W - scroll.w - 10;
	scroll.y = WIN_H - scroll.h ;

	SDLX_SpriteCreate(&ctx.sprites[0] , tex, NULL, &scroll);

	ctx.sprites[0].srcptr = NULL;
	ctx.nsprites++;


	anim = calloc(1, sizeof(SDLX_Anim));
	tex = SDLX_LoadTexture("Assets/Fireball.png", SDLX_DisplayGet());

	i = 0;
	dst.h = 128;
	dst.w = 128;
	dst.x = STARTX;
	dst.y = STARTY;
	while (i < 10)
	{
		// ctx.active[i] = NoSpell;
		SDLX_SpriteCreate(&ctx.active[i].sprite, NULL, NULL, &dst);
		SDLX_AnimatorCreate(NULL, NULL, 0, NULL, &ctx.active[i].sprite)->active = SDLX_FALSE;
		i++;
	}
	anim[0] = SDLX_AnimLoadHorizontal(tex, 11, 64, 64, SDLX_FALSE, 0, 0);
	SDLX_SpriteCreate(&ctx.spells[0].sprite, tex, NULL, &dst);
	SDLX_AnimatorCreate(NULL, anim, 1, NULL, &ctx.spells[0].sprite)->active = SDLX_FALSE;
	ctx.spells[0].id = 20616;
	ctx.spells[0].func = &Fireball;
	ctx.spells[0].duration = 11;
	ctx.current = &NoSpell;

///TOP MOST POINT///
	dst.h = 10;
	dst.w = 10;
	dst.w = 0;
	dst.x = scroll.x + 68;
	dst.y = scroll.y + 60;


	dst.x += 5;
	ctx.buttons[2] = SDLX_GUIElem_Create(NULL, "0", &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	SDLX_AnimatorCreate(NULL, beam, 1, &dst, &ctx.buttons[2]->sprite);
	ctx.buttons[2]->sprite.center = (SDL_Point){0, dst.h / 2};
	ctx.buttons[2]->sprite.animator->active = SDLX_FALSE;
	ctx.buttons[2]->data = &ctxFalse;


	dst.x = scroll.x + 32;
	dst.y = scroll.y + 93;
	ctx.buttons[3] = SDLX_GUIElem_Create(NULL, "1", &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	dst.x += 5;
	SDLX_AnimatorCreate(NULL, beam, 1, &dst, &ctx.buttons[3]->sprite);
	ctx.buttons[3]->sprite.center = (SDL_Point){0, dst.h / 2};
	ctx.buttons[3]->sprite.animator->active = SDLX_FALSE;
	ctx.buttons[3]->data = &ctxFalse;

	dst.x = scroll.x + 55;
	dst.y = scroll.y + 93;
	ctx.buttons[4] = SDLX_GUIElem_Create(NULL, "2", &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	dst.x += 5;
	SDLX_AnimatorCreate(NULL, beam, 1, &dst, &ctx.buttons[4]->sprite);
	ctx.buttons[4]->sprite.center = (SDL_Point){0, dst.h / 2};
	ctx.buttons[4]->sprite.animator->active = SDLX_FALSE;
	ctx.buttons[4]->data = &ctxFalse;

	dst.x = scroll.x + 80;
	dst.y = scroll.y + 93;
	ctx.buttons[5] = SDLX_GUIElem_Create(NULL, "3", &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	dst.x += 5;
	SDLX_AnimatorCreate(NULL, beam, 1, &dst, &ctx.buttons[5]->sprite);
	ctx.buttons[5]->sprite.center = (SDL_Point){0, dst.h / 2};
	ctx.buttons[5]->sprite.animator->active = SDLX_FALSE;
	ctx.buttons[5]->data = &ctxFalse;

	dst.x = scroll.x + 104;
	dst.y = scroll.y + 93;
	ctx.buttons[6] = SDLX_GUIElem_Create(NULL, "4", &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	dst.x += 5;
	SDLX_AnimatorCreate(NULL, beam, 1, &dst, &ctx.buttons[6]->sprite);
	ctx.buttons[6]->sprite.center = (SDL_Point){0, dst.h / 2};
	ctx.buttons[6]->sprite.animator->active = SDLX_FALSE;
	ctx.buttons[6]->data = &ctxFalse;


	dst.x = scroll.x + 45;
	dst.y = scroll.y + 128;
	ctx.buttons[7] = SDLX_GUIElem_Create(NULL, "5", &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	dst.x += 5;
	SDLX_AnimatorCreate(NULL, beam, 1, &dst, &ctx.buttons[7]->sprite);
	ctx.buttons[7]->sprite.center = (SDL_Point){0, dst.h / 2};
	ctx.buttons[7]->sprite.animator->active = SDLX_FALSE;
	ctx.buttons[7]->data = &ctxFalse;
	ctx.buttons[7]->autotrigger = SDLX_TRUE;

	dst.x = scroll.x + 68;
	dst.y = scroll.y + 128;
	ctx.buttons[8] = SDLX_GUIElem_Create(NULL, "6", &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	dst.x += 5;
	SDLX_AnimatorCreate(NULL, beam, 1, &dst, &ctx.buttons[8]->sprite);
	ctx.buttons[8]->sprite.center = (SDL_Point){0, dst.h / 2};
	ctx.buttons[8]->sprite.animator->active = SDLX_FALSE;
	ctx.buttons[8]->data = &ctxFalse;

	dst.x = scroll.x + 90;
	dst.y = scroll.y + 128;
	ctx.buttons[9] = SDLX_GUIElem_Create(NULL, "7", &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	dst.x += 5;
	SDLX_AnimatorCreate(NULL, beam, 1, &dst, &ctx.buttons[9]->sprite);
	ctx.buttons[9]->sprite.center = (SDL_Point){0, dst.h / 2};
	ctx.buttons[9]->sprite.animator->active = SDLX_FALSE;
	ctx.buttons[9]->data = &ctxFalse;




	dst.x = scroll.x + 32;
	dst.y = scroll.y + 160;
	ctx.buttons[10] = SDLX_GUIElem_Create(NULL, "8", &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	dst.x += 5;
	SDLX_AnimatorCreate(NULL, beam, 1, &dst, &ctx.buttons[10]->sprite);
	ctx.buttons[10]->sprite.center = (SDL_Point){0, dst.h / 2};
	ctx.buttons[10]->sprite.animator->active = SDLX_FALSE;
	ctx.buttons[10]->data = &ctxFalse;
	dst.x = scroll.x + 55;
	dst.y = scroll.y + 160;
	ctx.buttons[11] = SDLX_GUIElem_Create(NULL, "9", &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	dst.x += 5;
	SDLX_AnimatorCreate(NULL, beam, 1, &dst, &ctx.buttons[11]->sprite);
	ctx.buttons[11]->sprite.center = (SDL_Point){0, dst.h / 2};
	ctx.buttons[11]->sprite.animator->active = SDLX_FALSE;
	ctx.buttons[11]->data = &ctxFalse;

	dst.x = scroll.x + 80;
	dst.y = scroll.y + 160;
	ctx.buttons[12] = SDLX_GUIElem_Create(NULL, "10", &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	dst.x += 5;
	SDLX_AnimatorCreate(NULL, beam, 1, &dst, &ctx.buttons[12]->sprite);
	ctx.buttons[12]->sprite.center = (SDL_Point){0, dst.h / 2};
	ctx.buttons[12]->sprite.animator->active = SDLX_FALSE;
	ctx.buttons[12]->data = &ctxFalse;

	dst.x = scroll.x + 104;
	dst.y = scroll.y + 160;
	ctx.buttons[13] = SDLX_GUIElem_Create(NULL, "11", &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	dst.x += 5;
	SDLX_AnimatorCreate(NULL, beam, 1, &dst, &ctx.buttons[13]->sprite);
	ctx.buttons[13]->sprite.center = (SDL_Point){0, dst.h / 2};
	ctx.buttons[13]->sprite.animator->active = SDLX_FALSE;
	ctx.buttons[13]->data = &ctxFalse;



//BOTTOM MOST POINT
	dst.x = scroll.x + 68;
	dst.y = scroll.y + 195;
	ctx.buttons[14] = SDLX_GUIElem_Create(NULL, "12", &isHoverDraw, &DrawButtonHover, &SDLX_NullGUIFunc, &SDLX_NullGUIFunc, &DrawButtonTrigger);
	dst.x += 5;
	SDLX_AnimatorCreate(NULL, beam, 1, &dst, &ctx.buttons[14]->sprite);
	ctx.buttons[14]->sprite.center = (SDL_Point){0, dst.h / 2};
	ctx.buttons[14]->sprite.animator->active = SDLX_FALSE;
	ctx.buttons[14]->data = &ctxFalse;


	SDLX_GUIElem_SetActive(ctx.buttons[2], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx.buttons[3], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx.buttons[4], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx.buttons[5], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx.buttons[6], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx.buttons[7], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx.buttons[8], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx.buttons[9], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx.buttons[10], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx.buttons[11], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx.buttons[12], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx.buttons[13], SDLX_TRUE);
	SDLX_GUIElem_SetActive(ctx.buttons[14], SDLX_TRUE);
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
	SDLX_GUIElem_SetActive(ctx.buttons[3], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx.buttons[4], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx.buttons[5], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx.buttons[6], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx.buttons[7], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx.buttons[8], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx.buttons[9], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx.buttons[10], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx.buttons[11], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx.buttons[12], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx.buttons[13], SDLX_FALSE);
	SDLX_GUIElem_SetActive(ctx.buttons[14], SDLX_FALSE);
}

void test_levelCleanup(void *arg)
{
	SDL_Log("Cleanup Test level\n");
	// SDLX_GUIElem_SetActive(ctx.buttons[1], SDLX_FALSE);
}
