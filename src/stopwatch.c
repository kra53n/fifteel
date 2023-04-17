#include <SDL.h>

#include "nums.h"
#include "stopwatch.h"

int StopwatchInit(Stopwatch* self)
{
	self->lastUpdate = SDL_GetTicks();
	self->coords.x = 10;
	self->coords.y = 10;
}

int StopwatchUpdate(Stopwatch* self)
{
	int ticks = SDL_GetTicks();
	if (ticks - self->lastUpdate < 1'000) return 1;
	else self->lastUpdate = ticks;

	self->secs;

	return 1;
}

int StopwatchDraw(Stopwatch* self, Texture* timeTexture, Nums* nums)
{
}
