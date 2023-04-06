#pragma once

#include <SDL.h>

typedef struct
{
	SDL_Texture* texture;
	struct Cell* nxt;
} Cell;