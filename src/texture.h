#pragma once

#include <SDL.h>

typedef struct Texture
{
	SDL_Texture* data;
	SDL_Rect     rect;
} Texture;