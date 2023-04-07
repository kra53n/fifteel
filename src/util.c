#include "util.h"

void centerizeRect(SDL_Rect* r1, SDL_Rect* r2)
{
	r2->x = r1->x + (r1->w - r2->w) / 2;
	r2->y = r1->y + (r1->h - r2->h) / 2;
}