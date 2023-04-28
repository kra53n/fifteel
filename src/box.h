#pragma once

#include <SDL.h>

#include "nums.h"
#include "color.h"
#include "timer.h"

typedef struct Box
{
	SDL_Rect  rect;

	int       rows;
	int       cols;
	int       textSize;
	int       moves;
	int       bestTime;
	int       bestMoves;

	Timer     timer;

	Color     bg;
	Color     cellColorBg;
	Color     cellColorFg;
	Color     cellColorText;

	int*      cells;
	int       cellPadding;
} Box;

#define BOX_DEFAULT_ROWS_SIZE 4
#define BOX_DEFAULT_COLS_SIZE 4

int BoxInit(Box* self, int rows, int cols);
int BoxUninit(Box* self);
int BoxDraw(
	Box* self,
	SDL_Renderer* rer,
	Texture* timeTexture,
	Texture* movesTexture,
	Texture* bestTimeTexture,
	Texture* bestMovesTexture,
	Nums* nums
);
int BoxUpdate(Box* self);
int BoxIsComplete(Box* self);