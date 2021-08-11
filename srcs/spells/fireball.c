#include "rush.h"

int Fireball(Spell *spell)
{
	if (spell->info.duration > 4)
	{
		spell->sprite.dstptr->x -= spell->step.x;
		spell->sprite.dstptr->y -= spell->step.y;
	}
	spell->info.duration--;

	return (spell->info.duration != 0);
}
