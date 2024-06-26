#include <stdio.h>
#include <stdlib.h>
#include <SDL_ttf.h>

#include "game.h"
#include "util.h"

int GameInitTextures(Game* self)
{
	TTF_Font* font = TTF_OpenFont(TEXT_FONTNAME, TEXT_SIZE);

	Color c; set_color(c, 255);
	self->textures[GAME_TEXTURE_TIME]            = TextGetAsTexture(self->rer, font, "Time: ", c);
	self->textures[GAME_TEXTURE_MOVES]           = TextGetAsTexture(self->rer, font, "Moves: ", c);
	self->textures[GAME_TEXTURE_BEST_TIME]       = TextGetAsTexture(self->rer, font, "B Time: ", c);
	self->textures[GAME_TEXTURE_BEST_MOVES]      = TextGetAsTexture(self->rer, font, "B Moves: ", c);
	self->textures[GAME_TEXTURE_RESTART_MESSAGE] = TextGetAsTexture(self->rer, font, GAME_RESTART_MESSAGE_TEXT, c);

	SDL_Rect winScreen = { 0, 0, GAME_WIDTH, GAME_HEIGHT };
	centerizeRect(&self->textures[GAME_TEXTURE_RESTART_MESSAGE].rect, &winScreen);

	TTF_CloseFont(font);
}

int GameInit(Game* self)
{
	srand(time());

	int status;

	if (status = SDL_Init(SDL_INIT_EVERYTHING))
	{
		return status;
	}

	if (status = TTF_Init())
	{
		return status;
	}

	self->win = SDL_CreateWindow(
		GAME_TITLE,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		GAME_WIDTH,
		GAME_HEIGHT,
		0
	);
	if (!self->win) return 1;

	self->rer = SDL_CreateRenderer(self->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!self->rer) return 1;

	SDL_Rect winScreen = { 0, 0, GAME_WIDTH, GAME_HEIGHT };
	GameInitTextures(self);
	NumsInit(&self->nums, self->rer);
	MenuInit(&self->menu, self->rer, winScreen);
	BoxInit(&self->box, BOX_DEFAULT_ROWS_SIZE, BOX_DEFAULT_COLS_SIZE);

	self->lastUpdate = SDL_GetTicks();
	self->flags = GAME_RUN | GAME_FIRST_STARTED;

	return 0;
}

int GameRestart(Game* self)
{
	BoxUninit(&self->box);
	BoxInit(&self->box, self->box.rows, self->box.cols);
}

int GameUninit(Game* game)
{
	SDL_DestroyRenderer(game->rer);
	SDL_DestroyWindow(game->win);
	TTF_Quit();
	SDL_Quit();
	exit(0);
}

void GameQuitFromBox(Game* self)
{
	self->menu.status = MENU_ACTIVE;
	GameRestart(self);
}

int GameProcessEvents(Game* self)
{
	self->flags = self->flags & ~GAME_WAS_KEY_DOWN;
	SDL_Event ev;
	while (SDL_PollEvent(&ev))
	{
		switch (ev.type)
		{
		case SDL_QUIT: GameQuitFromBox(self); break;
		case SDL_MOUSEBUTTONDOWN:
		{
			self->flags = self->flags | GAME_WAS_KEY_DOWN;

			if (BoxIsComplete(&self->box)) continue;

			switch (self->menu.status)
			{
			case MENU_ACTIVE:
			case MENU_SETTINGS: MenuUpdate(&self->menu); break;
			case MENU_UNACTIVE: BoxUpdate(&self->box); break;
			}
		} break;
		case SDL_KEYDOWN:
		{
			self->flags = self->flags | GAME_WAS_KEY_DOWN;
			switch (ev.key.keysym.scancode)
			{
			case SDL_SCANCODE_R:      GameRestart(self); break;
			case SDL_SCANCODE_ESCAPE: GameQuitFromBox(self); break;
			} break;
		}
		}
	}
}

void GameUpdate(Game* self)
{
	SDL_UpdateWindowSurface(self->win);
	GameProcessEvents(self);

	if (!BoxIsComplete(&self->box))
		TimerUpdate(&self->box.timer);

	if (self->menu.status == MENU_CHANGED_FIELD)
	{
		self->menu.status = MENU_UNACTIVE;
		BoxUninit(&self->box);
		BoxInit(&self->box, self->menu.field, self->menu.field);
	}
}

void GameDraw(Game* self)
{
	self->flags = self->flags & ~GAME_FIRST_STARTED;

	SDL_SetRenderDrawColor(self->rer, 0, 0, 0, 255);
	SDL_RenderClear(self->rer);

	switch (self->menu.status)
	{
	case MENU_SETTINGS:
	case MENU_ACTIVE: {
		MenuDraw(&self->menu, self->rer);
	} break;
	case MENU_UNACTIVE: {
		BoxDraw(
			&self->box,
			self->rer,
			&self->textures[GAME_TEXTURE_TIME],
			&self->textures[GAME_TEXTURE_MOVES],
			&self->textures[GAME_TEXTURE_BEST_TIME],
			&self->textures[GAME_TEXTURE_BEST_MOVES],
			&self->nums
		);
	} break;
	}

	if (BoxIsComplete(&self->box))
	{
		SDL_RenderCopy(
			self->rer,
			self->textures[GAME_TEXTURE_RESTART_MESSAGE].data,
			0,
			&self->textures[GAME_TEXTURE_RESTART_MESSAGE].rect
		);
	}

	SDL_RenderPresent(self->rer);
}

int GameRun(Game* self)
{
	while (self->flags & GAME_RUN)
	{
		GameUpdate(self);
		GameDraw(self);
	}
	GameUninit(self);
	return 0;
}
