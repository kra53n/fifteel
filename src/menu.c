#include "menu.h"
#include "util.h"
#include "color.h"

void MenuSpawnTextures(Menu* self, SDL_Rect box)
{
	fill_rect(self->rect, 0);
	for (int i = 0; i < MENU_TEXTURES_NUM / 2; i++)
	{
		SDL_Rect tmp = self->textures[i].rect;
		self->rect.w = max(self->rect.w, tmp.w);
		self->rect.h += tmp.h + MENU_TEXT_PADDING;
	}
	self->rect.h -= MENU_TEXT_PADDING;

	centerizeRect(&self->rect, &box);
}

int MenuInit(Menu* self, SDL_Renderer* rer, SDL_Rect box)
{
	TTF_Font* font = TTF_OpenFont(TEXT_FONTNAME, MENU_TEXT_SIZE);

	Color c; set_color(c, 255);

	self->textures[MENU_TEXTURE_PLAY]     = TextGetAsTexture(rer, font, MENU_PLAY_TEXT, c);
	self->textures[MENU_TEXTURE_RECORDS]  = TextGetAsTexture(rer, font, MENU_RECORDS_TEXT, c);
	self->textures[MENU_TEXTURE_SETTINGS] = TextGetAsTexture(rer, font, MENU_SETTINGS_TEXT, c);
	self->textures[MENU_TEXTURE_QUIT]     = TextGetAsTexture(rer, font, MENU_QUIT_TEXT, c);

	self->textures[MENU_TEXTURE_FIELD_3X_TEXT] = TextGetAsTexture(rer, font, MENU_FIELD_3X_TEXT, c);
	self->textures[MENU_TEXTURE_FIELD_4X_TEXT] = TextGetAsTexture(rer, font, MENU_FIELD_4X_TEXT, c);
	self->textures[MENU_TEXTURE_FIELD_5X_TEXT] = TextGetAsTexture(rer, font, MENU_FIELD_5X_TEXT, c);
	self->textures[MENU_TEXTURE_FIELD_6X_TEXT] = TextGetAsTexture(rer, font, MENU_FIELD_6X_TEXT, c);

	self->status = MENU_ACTIVE;

	MenuSpawnTextures(self, box);

	TTF_CloseFont(font);
}

int MenuUpdate(Menu* self)
{
	SDL_Point mouse;
	SDL_GetMouseState(&mouse.x, &mouse.y);

	int x = self->rect.x;
	int y = self->rect.y;

	for (int i = menu_offset(self->status); i < MENU_TEXTURES_NUM / 2 + menu_offset(self->status); i++)
	{
		SDL_Rect r = self->textures[i].rect;
		r.x = x + (self->rect.w - r.w) / 2;
		r.y = y;
		y += r.h + MENU_TEXT_PADDING;

		if (!SDL_PointInRect(&mouse, &r)) continue;

		switch (i)
		{
		case MENU_TEXTURE_PLAY:     self->status = MENU_UNACTIVE; break;
		case MENU_TEXTURE_SETTINGS: self->status = MENU_SETTINGS; break;
		case MENU_TEXTURE_QUIT:     exit(0);

		case MENU_TEXTURE_FIELD_3X_TEXT: self->status = MENU_CHANGED_FIELD; self->field = 3; break;
		case MENU_TEXTURE_FIELD_4X_TEXT: self->status = MENU_CHANGED_FIELD; self->field = 4; break;
		case MENU_TEXTURE_FIELD_5X_TEXT: self->status = MENU_CHANGED_FIELD; self->field = 5; break;
		case MENU_TEXTURE_FIELD_6X_TEXT: self->status = MENU_CHANGED_FIELD; self->field = 6; break;
		}
	}
}

int MenuDraw(Menu* self, SDL_Renderer* rer)
{
	int x = self->rect.x;
	int y = self->rect.y;
	for (int i = menu_offset(self->status); i < MENU_TEXTURES_NUM / 2 + menu_offset(self->status); i++)
	{
		SDL_Rect r = self->textures[i].rect;
		r.x = x + (self->rect.w - r.w) / 2;
		r.y = y;
		SDL_RenderCopy(rer, self->textures[i].data, 0, &r);
		y += r.h + MENU_TEXT_PADDING;
	}
}
