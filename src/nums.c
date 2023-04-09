#include <malloc.h>
#include <SDL_ttf.h>

#include "nums.h"
#include "text.h"
#include "util.h"

int NumsInit(Nums* self, SDL_Renderer* rer)
{
	self->size = 40;
	TTF_Font* font = TTF_OpenFont(TEXT_FONTNAME, self->size);
	Color c; set_color(c, 255);
	for (int i = 0; i < 10; i++)
	{
		const char text[2] = { i + '0', 0 };
		self->data[i] = TextGetAsTexture(rer, font, text, c);
	}
	TTF_CloseFont(font);
}

void NumsUninit(Texture* self, int len)
{
	// TODO:
	//for (int i = 0; i < len; i++) SDL_DestroyTexture(self[i].data);
	//free(self);
}

void NumsDraw(Nums* self, SDL_Renderer* rer, const char* text, SDL_Rect box)
{
	SDL_Rect r = { 0, 0, 0, 0 };
	int len;
	for (len = 0; text[len]; len++) r.w += self->data[text[len] - '0'].rect.w;
	r.h += self->data[text[0] - '0'].rect.h;
	centerizeRect(&r, &box);

	int x = r.x;
	for (int i = 0; i < len; i++)
	{
		int w = self->data[text[i] - '0'].rect.w;
		SDL_Rect tmp = { x, r.y, w, r.h };
		SDL_RenderCopy(rer, self->data[text[i] - '0'].data, 0, &tmp);
		x += w;
	}
}