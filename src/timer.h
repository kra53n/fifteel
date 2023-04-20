#pragma once

#include "texture.h"

typedef struct Timer
{
	int       lastUpdate;
	int       secs;
	SDL_Point coords;
} Timer;

int TimerInit(Timer* self);
int TimerRestart(Timer* self);
int TimerUpdate(Timer* self);
int TimerDraw(Timer* self, SDL_Renderer* rer, Texture* timeTexture, Nums* nums);
