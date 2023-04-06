#include "box.h"
#include "game.h"

int BoxInit(Box* self)
{
	int padding = 40;
	int h = GAME_HEIGHT - padding * 2;
	SDL_Rect r = {(GAME_WIDTH - h) / 2, padding, h, h };
	self->rect = r;

	self->rows = 4;
	self->cols = 4;
	self->textSize = 30;

	set_color(self->bg, 20, 20, 20);
	set_color(self->cellColorBg, 30);
	set_color(self->cellColorFg, 120);
	set_color(self->cellColorText, 255);
}

int BoxDraw(Box* self, SDL_Renderer* rer)
{
	SDL_SetRenderDrawColor(rer, give_color(self->bg));
	SDL_RenderFillRect(rer, &self->rect);
	SDL_RenderPresent(rer);
}
