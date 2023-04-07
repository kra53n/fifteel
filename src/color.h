#pragma once

#include <SDL.h>

typedef struct Color
{
	Uint8 r;
	Uint8 g;
	Uint8 b;
} Color;

#define give_color(c) c.r, c.g, c.b, 255
#define set_color(c, red, green, blue) c.r = red; c.g = green; c.b = blue
#define set_color(c, val) c.r = val; c.g = val; c.b = val
