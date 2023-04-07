#include <malloc.h>
#include <SDL_ttf.h>

#include "cell.h"
#include "text.h"

int CellsInit(Cell** self, SDL_Renderer* rer, int rows, int cols, Color textColor, int textSize)
{
	TTF_Font* font = TTF_OpenFont(TEXT_FONTNAME, textSize);

	*self = (Cell*)malloc(sizeof(Cell));
	Cell* tmp = *self;
	for (int i = 1; i < rows * cols; i++)
	{
		char text[4];
		SDL_itoa(i, text, 10);
		tmp->texture = TextGetAsTexture(rer, font, text, textColor);
		if (i + 1 != rows * cols) tmp->nxt = (Cell*)malloc(sizeof(Cell));
		else tmp->nxt = NULL;
		tmp = tmp->nxt;
	}

	TTF_CloseFont(font);
}

void CellsFree(Cell* self)
{
	while (self)
	{
		Cell* tmp = self->nxt;
		free(self);
		self = tmp;
	}
	self = NULL;
}

void CellsDraw(Cell* self, SDL_Renderer* rer)
{
	SDL_SetRenderDrawColor(rer, 255, 255, 255, 255);
	int x = 0;
	for (Cell* i = self; i; i = i->nxt)
	{
		SDL_Rect r = { x, 0, i->texture.rect.w, i->texture.rect.h };
		SDL_RenderCopy(rer, i->texture.data, 0, &r);
		x += 50;
	}
}