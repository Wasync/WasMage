# include "rush.h"

void main_levelInit(void *arg)
{
	SDLX_Anim	**a_beam;

	SDL_Texture *t_beam;
	SDL_Texture *t_pause;
	SDL_Texture *t_scroll;
	SDL_Rect scroll;
	SDL_Rect pause_src;
	SDL_Rect pause_dst;
	SDL_Rect beamrect;
	SDL_Rect dst;

	Context *ctx;
	int i;

	ctx = getCtx();
	t_beam = SDLX_LoadTexture("Assets/Spells/DrawBeam.png", SDLX_DisplayGet());
	t_scroll = SDLX_LoadTexture("Assets/scroll.png", SDLX_DisplayGet());
	t_pause = SDLX_LoadTexture("Assets/UI/LevelOver.png", SDLX_DisplayGet());

	a_beam = calloc(1, sizeof(SDLX_Anim *));
	a_beam[0] = SDLX_AnimLoadVertical(t_beam, 8, 128, 16, SDL_TRUE, 0, 0);

	pause_src.x = 160;
	pause_src.h = 28;
	pause_src.w = 32;

	pause_src.x = 160;
	pause_src.h = 28;
	pause_src.w = 32;



	scroll.h = 128 * 2.25;
	scroll.w = 64 *2.25;
	scroll.x = WIN_W - scroll.w - 10;
	scroll.y = WIN_H - scroll.h ;

	initSpells();
	initSpellData();


	dst.h = 10;
	dst.w = 0;

	ctx->level.drawing = SDLX_FALSE;

	// init_pause();

	init_enemies();
	init_enemyData();
	ctx->level.area = loadArea(0);
	NextWave(ctx->level.area);
}

void main_level(void *arg)
{
	SDLX_Input input;
	Context *ctx;
	int i;
	int ready;

	ctx = getCtx();
	input = SDLX_InputGet();
	i = 0;

	ready = ReadyCheck(ctx->player.current)
		&& input.mouse_click == SDL_MOUSEBUTTONDOWN;
	// if (ctx->level.area->waves[ctx->level.area->currentWave].nAlive <= 0)
	// 	NextWave(ctx->level.area);
	// while (i < ctx->nenmies)
	// {
	// 	if (ctx->enemy_data[i].info.id != 0)
	// 		ctx->enemy_data[i].info.func(&ctx->enemy_data[i]);
	// 	i++;
	// }
	i = 0;
	while(i < 1)
	{
		if (ctx->player.active[i].info.id && ctx->player.active[i].info.func(&ctx->player.active[i]))
		{
			ctx->player.active[i].info.id = 0;
			ctx->player.active[i].collider.active = SDLX_FALSE;
			ctx->player.active[i].p_anim.active = SDLX_FALSE;
			ctx->player.active[i].projectile._dst.x = STARTX - 64;
			ctx->player.active[i].projectile._dst.y = STARTY - 64;

		}

		if (ready && ctx->player.current->info.id != 0 && ctx->player.active[i].info.id == 0)
		{
			CopySpell(ctx->player.current, &ctx->player.active[i]);
			ActivateSpell(&ctx->player.active[i]);
			SDLX_Animator_StateSet(&(ctx->player.current->c_anim), 2, SDLX_FALSE);
			ready = SDLX_FALSE;
			ctx->player.active[i].step.x = (ctx->player.active[i].projectile._dst.x - (input.mouse.x - 64)) / 7;
			ctx->player.active[i].step.y = (ctx->player.active[i].projectile._dst.y - (input.mouse.y - 64)) / 7;
		}
		i++;
	}
	if (ctx->level.drawing == SDLX_TRUE)
	{
		DrawSpell();
		if (input.mouse_click == SDL_MOUSEBUTTONUP)
			CastSpell(GetSpell());
	}
	SDLX_PollCollisions();
	// SDL_Log("Poll");
	SDLX_ResolveCollisions();
	// SDL_Log("REsolve");
	// CollisionCheck(ctx->enemy_data, ctx->nenemies, ctx->player.active, 10);
	renderSprites();
}

void main_levelCleanup(void *arg)
{
	Context *ctx;

	ctx = getCtx();
	SDL_Log("Cleanup main lvl\n");
}
