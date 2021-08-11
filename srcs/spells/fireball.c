#include "rush.h"

int Fireball(Spell *spell)
{
	if (spell->duration > 4)
	{
		spell->sprite.dstptr->x -= spell->step.x;
		spell->sprite.dstptr->y -= spell->step.y;
	}
	spell->duration--;

	return (spell->duration != 0);
}
