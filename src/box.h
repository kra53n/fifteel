#pragma once

#include <SDL.h>

#include "nums.h"
#include "color.h"

typedef struct Box
{
	SDL_Rect  rect;
	int       rows;
	int       cols;
	int       textSize;
	int       moves;
	Color     bg;
	Color     cellColorBg;
	Color     cellColorFg;
	Color     cellColorText;
	Texture*  nums;
	int*      cells;
	int       cellPadding;
} Box;

#define BOX_DEFAULT_ROWS_SIZE 4
#define BOX_DEFAULT_COLS_SIZE 4

int BoxInit(Box* self, int rows, int cols);
int BoxUninit(Box* self);
int BoxDraw(Box* self, SDL_Renderer* rer, Nums* nums);
int BoxUpdate(Box* self);
int BoxIsComplete(Box* self);