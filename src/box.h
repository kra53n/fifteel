#pragma once

#include <SDL.h>

#include "nums.h"
#include "color.h"

typedef struct Box
{
	SDL_Rect   rect;
	int        rows;
	int        cols;
	int        textSize;
	Color      bg;
	Color      cellColorBg;
	Color      cellColorFg;
	Color      cellColorText;
	Texture*   nums;
	int*       cells;
} Box;

int BoxInit(Box* self);
int BoxDraw(Box* self, SDL_Renderer* rer);