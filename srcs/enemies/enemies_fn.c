#include "rush.h"

int skullfn(Enemy *self)
{
	if (self->info.hp <= 0)
	{
		self->info.id = 0;
		self->collider.active = SDL_FALSE;
		self->animator.state = 2;
	}
	if (self->sprite.dst->y + self->sprite.dst->h >= WIN_H - 128)
	{
		self->info.id = 0;
		self->collider.active = SDL_FALSE;
		self->animator.state = 1;
	}
	else
	{
		self->sprite.dst->y += self->info.speed;
		self->sprite.dst->w += self->info.speed;
		// self->sprite.dst->h += ;
	}

	return 1;
}

void e_react(SDLX_Collider *self, SDLX_Collider *other)
{
	SDL_Log("Enemy collided");
}
