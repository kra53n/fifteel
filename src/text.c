#include "text.h"

Texture TextGetAsTexture(SDL_Renderer* rer, TTF_Font* font, const char* text, Color color)
{
	SDL_Color c = { give_color(color) };
	SDL_Surface* surf = TTF_RenderText_Blended(font, text, c);
	if (!surf) exit(1);
	SDL_Rect r = { 0, 0, surf->w, surf->h };
	SDL_Texture* data = SDL_CreateTextureFromSurface(rer, surf);
	SDL_FreeSurface(surf);
	Texture texture = { data, r };
	return texture;
}
