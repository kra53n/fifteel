#include "menu.h"
#include "util.h"
#include "color.h"

int MenuInit(Menu* self, SDL_Renderer* rer, SDL_Rect box)
{
	TTF_Font* font = TTF_OpenFont(TEXT_FONTNAME, MENU_TEXT_SIZE);

	Color c; set_color(c, 255);
	self->play = TextGetAsTexture(rer, font, MENU_PLAY_TEXT, c);
	self->quit = TextGetAsTexture(rer, font, MENU_QUIT_TEXT, c);

	self->status = MENU_ACTIVE;

	centerizeRect(&self->play.rect, &box);
	centerizeRect(&self->quit.rect, &box);
	self->play.rect.y -= self->quit.rect.h + 30;

	TTF_CloseFont(font);
}

int MenuUpdate(Menu* self)
{
	SDL_Point mouse;
	SDL_GetMouseState(&mouse.x, &mouse.y);

	if (SDL_PointInRect(&mouse, &self->play.rect))      self->status = MENU_UNACTIVE;
	else if (SDL_PointInRect(&mouse, &self->quit.rect)) exit(1);
}

int MenuDraw(Menu* self, SDL_Renderer* rer)
{
	SDL_RenderCopy(rer, self->play.data, 0, &self->play.rect);
	SDL_RenderCopy(rer, self->quit.data, 0, &self->quit.rect);
}