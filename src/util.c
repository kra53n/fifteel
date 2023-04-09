#include "util.h"

void centerizeRect(SDL_Rect* src, SDL_Rect* dst)
{
	src->x = dst->x + (dst->w - src->w) / 2;
	src->y = dst->y + (dst->h - src->h) / 2;
}