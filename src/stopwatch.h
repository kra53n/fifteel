#pragma once

#include "texture.h"

typedef struct Stopwatch
{
	int       lastUpdate;
	int       secs;
	SDL_Point coords;
} Stopwatch;