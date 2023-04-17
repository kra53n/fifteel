#pragma once

#include <SDL.h>

#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

#define fill_rect(r, val) r.x = val; r.y = val; r.w = val; r.h = val

void centerizeRect(SDL_Rect* src, SDL_Rect* dst);