#include "rush.h"

int Fireball(Spell *spell)
{

	if (*spell->info.elapsed < 8)
	{
		spell->projectile.dstptr->x -= spell->step.x;
		spell->projectile.dstptr->y -= spell->step.y;
	}
	spell->info.active = spell->info.elapsed == 8;

	return (*spell->info.elapsed == spell->info.duration);
}
