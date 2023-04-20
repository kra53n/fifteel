#include <SDL.h>

#include "nums.h"
#include "timer.h"

int TimerInit(Timer* self)
{
	self->lastUpdate = SDL_GetTicks();
	self->coords.x = 10;
	self->coords.y = 10;
	self->secs = 0;
}

int TimerRestart(Timer* self)
{
	self->secs = 0;
}

int TimerUpdate(Timer* self)
{
	int ticks = SDL_GetTicks();
	if (ticks - self->lastUpdate < 1'000) return 1;
	else self->lastUpdate = ticks;

	self->secs++;

	return 0;
}

int TimerDraw(Timer* self, SDL_Renderer* rer, Texture* timeTexture, Nums* nums)
{
	SDL_Rect r = { self->coords.x, self->coords.y, timeTexture->rect.w, timeTexture->rect.h };
	SDL_RenderCopy(rer, timeTexture->data, 0, &r);
	char text[3];
	int digitW = nums->data[0].rect.w;
	r.x += r.w;
	r.w = digitW;
	if (self->secs / 60 > 0)
	{
		SDL_itoa(self->secs / 60, text, 10);
		NumsDraw(nums, rer, text, r);
		int decades = 0;
		for (int i = self->secs / 60; i > 0; i /= 10, decades++);
		r.x += digitW + digitW * decades;
	}
	SDL_itoa(self->secs % 60, text, 10);
	NumsDraw(nums, rer, text, r);
}
