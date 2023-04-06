#include <malloc.h>
#include <SDL_ttf.h>

#include "cell.h"
#include "text.h"

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

int CellsInit(Cell* self, SDL_Renderer* rer, int row, int col, Color textColor, int textSize)
{
	if (self) CellsFree(self);

	TTF_Font* font = TTF_OpenFont(TEXT_FONTNAME, textSize);

	//Cell* tmp = self;
	//for (int i = 1; i < row * col; i++)
	//{
	//	tmp = (Cell*)malloc(sizeof(Cell));
	//	tmp->nxt = (Cell*)malloc(sizeof(Cell));
	//}

	TTF_CloseFont(font);
}