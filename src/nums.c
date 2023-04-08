#include <malloc.h>
#include <SDL_ttf.h>

#include "nums.h"
#include "text.h"

int NumsInit(Texture** self, SDL_Renderer* rer, int rows, int cols, Color textColor, int textSize)
{
	TTF_Font* font = TTF_OpenFont(TEXT_FONTNAME, textSize);

	int size = (rows * cols - 1);
	*self = (Texture*)malloc(sizeof(Texture) * size);
	for (int i = 0; i < size; i++)
	{
		char text[4];
		SDL_itoa(i+1, text, 10);
		(*self)[i] = TextGetAsTexture(rer, font, text, textColor);
	}

	TTF_CloseFont(font);
}

void NumsUninit(Texture* self, int len)
{
	for (int i = 0; i < len; i++) SDL_DestroyTexture(self[i].data);
	free(self);
}