#include "rush.h"

void fireball_react(SDLX_Collider *self, SDLX_Collider *other)
{
	SpellInfo *spell;
	Enemy_Info *enemy;

	spell = self->data;
	enemy = other->data;
	if ((self->layerMask & other->layerMask) == L_ENEMY)
	{
		SDL_Log("Fireball Hit enemy, deals %d damage has %d",
		weaknessTable[spell->type][enemy->type],  enemy->hp);
		enemy->hp -= weaknessTable[spell->type][enemy->type] * spell->damage;
	}
}

int Fireball(Spell *spell)
{

	if (*spell->info.elapsed < 8)
	{
		spell->projectile.dst->x -= spell->step.x;
		spell->projectile.dst->y -= spell->step.y;
	}
	spell->info.active = *spell->info.elapsed == 8;

	return (*spell->info.elapsed == spell->info.duration);
}
