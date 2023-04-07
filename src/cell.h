#pragma once

#include <SDL.h>

#include "color.h"
#include "texture.h"

typedef struct
{
	Texture     texture;
	struct Cell* nxt;
} Cell;

int CellsInit(Cell** self, SDL_Renderer* rer, int rows, int cols, Color textColor, int textSize);
