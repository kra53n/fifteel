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

void BoxFillCells(Box* self)
{
	for (int i = 1; i < self->rows * self->cols; i++) self->cells[i-1] = i;
	self->cells[self->rows * self->cols - 1] = 0;
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
	if (
		idx < 0 ||
		idx >= self->rows * self->cols ||
		self->cells[idx] == 0
	) return 0;
	int empty = BoxGetEmptyCellIndex(self);
	return (
		idx == empty - self->cols ||
		idx == empty + self->cols ||
		(idx % self->cols == 0 && idx + 1 == empty) ||
		((idx+1) % self->cols == 0 && idx - 1 == empty) ||
		(idx % self->cols != 0 && (idx+1) % self->cols != 0 && (idx + 1 == empty || idx - 1 == empty))
	);
}

void BoxMoveCell(Box* self, int srcIdx, int dstIdx)
{
	int tmp = self->cells[dstIdx];
	self->cells[dstIdx] = self->cells[srcIdx];
	self->cells[srcIdx] = tmp;
}

void BoxMoveCellRandomly(Box* self)
{
	int empty = BoxGetEmptyCellIndex(self);
	int possibleIdxs[4] = { empty - 1, empty + 1, empty - self->cols, empty + self->cols };
	int idx;
	do {
		idx = rand() % 4;
	} while(!BoxCellIsMovable(self, possibleIdxs[idx]));
	BoxMoveCell(self, empty, possibleIdxs[idx]);
}

int BoxInitCells(Box* self)
{
	self->cells = (int*)malloc(sizeof(int) * self->rows * self->cols);
	BoxFillCells(self);
	do {
		int n = self->rows * self->cols;
		for (int i = 0; i < n*n; i++) BoxMoveCellRandomly(self);
	} while (BoxIsComplete(self));
}

int BoxInit(Box* self, int rows, int cols)
{
	int padding = 40;
	int h = GAME_HEIGHT - padding * 2;
	SDL_Rect r = { (GAME_WIDTH - h) / 2, padding, h, h };
	self->rect = r;

	self->rows = rows;
	self->cols = cols;
	self->textSize = 40;
	self->moves = 0;
	// TODO: read values from file
	TimerInit(&self->timer);
	self->bestTime = 0;
	self->bestMoves = 0;

	BoxInitCells(self);
	self->cellPadding = 5;

	set_color(self->bg, 20);
	set_color(self->cellColorBg, 50);
	set_color(self->cellColorFg, 120);
	set_color(self->cellColorText, 255);
}

int BoxUninit(Box* self)
{
	if (self->cells) free(self->cells);
	self->cells = NULL;
}

int BoxGetCellIndex(Box* self, const SDL_Point* mouse)
{
	SDL_Rect r = { self->rect.x, self->rect.y, self->rect.w / self->cols, self->rect.h / self->rows };
	for (int i = 0; i < self->rows * self->cols; i++)
	{
		if (i % self->cols == 0 && i != 0)
		{
			r.x = self->rect.x;
			r.y += r.h;
		}
		if (SDL_PointInRect(mouse, &r)) return i;
		r.x += r.w;
	}
}

int BoxUpdate(Box* self)
{
	SDL_Rect mouse;
	SDL_GetMouseState(&mouse.x, &mouse.y);
	int idx = BoxGetCellIndex(self, &mouse);

	if (SDL_PointInRect(&mouse, &self->rect) && BoxCellIsMovable(self, idx))
	{
		self->moves++;
		BoxMoveCell(self, BoxGetEmptyCellIndex(self), idx);
	}
}

void BoxDrawMoves(Box* self, SDL_Renderer* rer, Texture* movesText,  Nums* nums)
{
	SDL_Rect r = {
		self->timer.coords.x,
		self->timer.coords.y * 2 + TEXT_SIZE,
		movesText->rect.w,
		movesText->rect.h,
	};
	SDL_RenderCopy(rer, movesText->data, 0, &r);
	int decades = 0;
	for (int i = self->moves / 60; i > 0; i /= 10, decades++);
	int w = nums->data[0].rect.w * (decades + 1);
	r.x += r.w;
	r.w = w;
	char text[5];
	SDL_itoa(self->moves, text, 10);
	NumsDraw(nums, rer, text, r);
}

void BoxDrawCell(Box* self, SDL_Renderer* rer, Nums* nums, SDL_Rect r, int idx)
{
	if (!idx) return;

	r.x += self->cellPadding;
	r.y += self->cellPadding;
	r.w -= self->cellPadding * 2;
	r.h -= self->cellPadding * 2;

	SDL_SetRenderDrawColor(rer, give_color(self->cellColorBg));
	SDL_RenderFillRect(rer, &r);

	SDL_SetRenderDrawColor(rer, give_color(self->cellColorText));
	char num[3]; SDL_itoa(idx, num, 10);
	NumsDraw(nums, rer, num, r);
}

void BoxDrawCells(Box* self, SDL_Renderer* rer, Nums* nums)
{
	SDL_Rect r = { self->rect.x, self->rect.y, self->rect.w / self->cols, self->rect.h / self->rows };
	for (int i = 0; i < self->rows * self->cols; i++)
	{
		if (i % self->cols == 0 && i != 0)
		{
			r.x = self->rect.x;
			r.y += r.h;
		}
		BoxDrawCell(self, rer, nums, r, self->cells[i]);
		r.x += r.w;
	}
}

int BoxDraw(
	Box* self,
	SDL_Renderer* rer,
	Texture* timeTexture,
	Texture* movesTexture,
	Texture* bsetTimeTexture,
	Texture* bestMovesTexture,
	Nums* nums)
{
	SDL_SetRenderDrawColor(rer, give_color(self->bg));
	BoxDrawMoves(self, rer, movesTexture, nums);
	TimerDraw(&self->timer, rer, timeTexture, nums);
	SDL_RenderFillRect(rer, &self->rect);
	BoxDrawCells(self, rer, nums);
}
