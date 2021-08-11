#include "rush.h"

void renderSprites(void)
{
	SDLX_Display *display;
	Context *ctx;

	int i;

	i = 0;
	ctx = getCtx();
	while (i < ctx->nsprites)
	{
		SDLX_RenderQueueAdd(0, ctx->sprites[i]);
		i++;
	}
}
