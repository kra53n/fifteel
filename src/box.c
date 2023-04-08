#include <stdlib.h>
#include <malloc.h>

#include "box.h"
#include "util.h"
#include "game.h"

int BoxIsComplete(Box* self)
{
	for (int i = 0; i < self->rows * self->cols - 1; i++)
	{
		if (self->cells[i] != i + 1) return 0;
	}
	return 1;
}

int BoxInitCells(Box* self)
{
	self->cells = (int*)malloc(sizeof(int) * self->rows * self->cols);
	for (int i = 0; i < self->rows * self->cols; i++) self->cells[i] = i;
	do {
		for (int i = 0; i < self->rows * self->cols; i++)
		{
			int j = rand() % self->rows * self->cols;
			int tmp = self->cells[i];
			self->cells[i] = self->cells[j];
			self->cells[j] = tmp;
		}
	// TODO: add correctness checking
	} while (BoxIsComplete(self) || 0);
}

int BoxInit(Box* self)
{
	int padding = 40;
	int h = GAME_HEIGHT - padding * 2;
	SDL_Rect r = {(GAME_WIDTH - h) / 2, padding, h, h };
	self->rect = r;

	self->rows = 4;
	self->cols = 4;
	self->textSize = 40;

	BoxInitCells(self);

	set_color(self->bg, 20);
	set_color(self->cellColorBg, 50);
	set_color(self->cellColorFg, 120);
	set_color(self->cellColorText, 255);
}

int BoxUninit(Box* self)
{
	NumsUninit(self->nums);
	if (self->cells) free(self->cells);
}

int BoxGetCellIndex(Box* self, const SDL_Point* mouse)
{
	SDL_Rect r = { self->rect.x, self->rect.y, self->rect.w / self->rows, self->rect.h / self->cols };
	for (int i = 0; i < self->rows * self->cols; i++)
	{
		if (i % self->rows == 0 && i != 0)
		{
			r.x = self->rect.x;
			r.y += r.h;
		}
		if (SDL_PointInRect(mouse, &r)) return i;
		r.x += r.w;
	}
}

int BoxGetEmptyCellIndex(Box* self)
{
	for (int i = 0; i < self->rows * self->cols; i++)
	{
		if (self->cells[i] == 0) return i;
	}
}

int BoxCellIsMovable(Box* self, int idx)
{
	if (self->cells[idx] == 0) return 0;
	int empty = BoxGetEmptyCellIndex(self);
	return (
		idx == empty - self->rows ||
		idx == empty + self->rows ||
		(idx % self->rows == 0 && idx + 1 == empty) ||
		(idx % self->rows == 1 && idx - 1 == empty) ||
		(idx % self->rows != 0 && (idx+1) % self->rows != 0 && (idx + 1 == empty || idx - 1 == empty))
	);
}

int BoxUpdate(Box* self)
{
	SDL_Rect mouse;
	SDL_GetMouseState(&mouse.x, &mouse.y);
	if (!SDL_PointInRect(&mouse, &self->rect)) return;

	int idx = BoxGetCellIndex(self, &mouse);
	if (!BoxCellIsMovable(self, idx)) return;

	int empty = BoxGetEmptyCellIndex(self);
	int tmp = self->cells[idx];
	self->cells[idx] = self->cells[empty];
	self->cells[empty] = tmp;
}

void BoxDrawCell(Box* self, SDL_Renderer* rer, SDL_Rect r, int idx)
{
	if (!idx) return;

	// TODO: exclude this tmp variable
	int pd = 5;
	r.x += pd;
	r.y += pd;
	r.w -= pd * 2;
	r.h -= pd * 2;

	SDL_SetRenderDrawColor(rer, give_color(self->cellColorBg));
	SDL_RenderFillRect(rer, &r);

	SDL_Rect numRect = self->nums[idx - 1].rect;
	centerizeRect(&r, &numRect);
	SDL_SetRenderDrawColor(rer, give_color(self->cellColorText));
	SDL_RenderCopy(rer, self->nums[idx - 1].data, NULL, &numRect);
}

void BoxDrawCells(Box* self, SDL_Renderer* rer)
{
	SDL_Rect r = { self->rect.x, self->rect.y, self->rect.w / self->rows, self->rect.h / self->cols };
	for (int i = 0; i < self->rows * self->cols; i++)
	{
		if (i % self->rows == 0 && i != 0)
		{
			r.x = self->rect.x;
			r.y += r.h;
		}
		BoxDrawCell(self, rer, r, self->cells[i]);
		r.x += r.w;
	}
}

int BoxDraw(Box* self, SDL_Renderer* rer)
{
	SDL_SetRenderDrawColor(rer, give_color(self->bg));
	SDL_RenderFillRect(rer, &self->rect);
	BoxDrawCells(self, rer);
	SDL_RenderPresent(rer);
}
