#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include "color.h"
#include "texture.h"

#define TEXT_FONTNAME "data/JetBrainsMono-BoldItalic.ttf"

Texture TextGetAsTexture(SDL_Renderer* rer, TTF_Font* font, const char* text, Color color);
