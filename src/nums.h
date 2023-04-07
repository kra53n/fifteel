#pragma once

#include <SDL.h>

#include "color.h"
#include "texture.h"

int NumsInit(Texture** self, SDL_Renderer* rer, int rows, int cols, Color textColor, int textSize);
