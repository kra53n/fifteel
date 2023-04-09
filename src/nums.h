#pragma once

#include <SDL.h>

#include "color.h"
#include "texture.h"

typedef struct Nums
{
	Texture data[10];
	int size;
} Nums;

int NumsInit(Nums* self, SDL_Renderer* rer);
void NumsDraw(Nums* self, SDL_Renderer* rer, const char* text, SDL_Rect box);
void NumsUninit(Texture* self, int len);
