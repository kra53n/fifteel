#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "color.h"
#include "texture.h"

typedef struct Nums
{
	Texture data[10];
} Nums;

int NumsInit(Nums* self, SDL_Renderer* rer);
void NumsDraw(Nums* self, SDL_Renderer* rer, const char* text, SDL_Rect box);
void NumsUninit(Texture* self, int len);
