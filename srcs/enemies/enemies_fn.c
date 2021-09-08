#include "rush.h"

int skullfn(Enemy *self)
{
	if (self->info.hp <= 0)
	{
		self->info.id = 0;
		self->collider.active = SDL_FALSE;
		self->sprite.animator->state = 2;
	}
	if (self->sprite.dstptr->y + self->sprite.dstptr->h >= WIN_H - 128)
	{
		self->info.id = 0;
		self->collider.active = SDL_FALSE;
		self->sprite.animator->state = 1;
	}
	else
	{
		self->sprite.dstptr->y += self->info.speed;
	}

	return 1;
}

void e_react(SDLX_Collider *self, SDLX_Collider *other)
{
	SDL_Log("Enemy collided");
}
