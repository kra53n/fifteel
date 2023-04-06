#include "text.h"

SDL_Texture* TextGetAsTexture(SDL_Renderer* rer, TTF_Font* font, const char* text, Color color)
{
	SDL_Color c = { give_color(color) };
	SDL_Surface* surf = TTF_RenderText_Blended(font, text, c);
	if (!surf) exit(1);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(rer, surf);
	SDL_FreeSurface(surf);
	return texture;
}
