#include <stdio.h>
#include <stdlib.h>
#include <SDL_ttf.h>

#include "game.h"
#include "util.h"

int GameInitRestartMessage(Game* self, SDL_Rect box)
{
	TTF_Font* font = TTF_OpenFont(TEXT_FONTNAME, GAME_RESTART_MESSAGE_SIZE);
	Color c;
	set_color(c, 255);
	self->restartMessage = TextGetAsTexture(self->rer, font, GAME_RESTART_MESSAGE_TEXT, c);
	TTF_CloseFont(font);
	centerizeRect(&box, &self->restartMessage.rect);
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

	self->rer = SDL_CreateRenderer(self->win, -1, SDL_RENDERER_ACCELERATED);
	if (!self->rer) return 1;

	SDL_Rect winScreen = { 0, 0, GAME_WIDTH, GAME_HEIGHT };
	MenuInit(&self->menu, self->rer, winScreen);
	BoxInit(&self->box);
	NumsInit(&self->box.nums, self->rer, self->box.rows, self->box.cols, self->box.cellColorText, self->box.textSize);

	GameInitRestartMessage(self, winScreen);

	self->lastUpdate = SDL_GetTicks();

	return 0;
}

int GameRestart(Game* self)
{
	BoxUninit(&self->box);
	BoxInit(&self->box);
	NumsInit(&self->box.nums, self->rer, self->box.rows, self->box.cols, self->box.cellColorText, self->box.textSize);
}

int GameUninit(Game* game)
{
	SDL_DestroyRenderer(game->rer);
	SDL_DestroyWindow(game->win);
	TTF_Quit();
	SDL_Quit();
	exit(0);
}

int GameProcessEvents(Game* self)
{
	SDL_Event ev;
	while (SDL_PollEvent(&ev))
	{
		switch (ev.type)
		{
		case SDL_QUIT: GameUninit(self); break;
		case SDL_MOUSEBUTTONDOWN:
		{

			if (BoxIsComplete(&self->box)) continue;

			switch (self->menu.status)
			{
			case MENU_ACTIVE:   MenuUpdate(&self->menu); break;
			case MENU_UNACTIVE: BoxUpdate(&self->box); break;
			}
		} break;
		case SDL_KEYDOWN:
		{
			switch (ev.key.keysym.scancode)
			{
			case SDL_SCANCODE_R:
			{
				GameRestart(self);
			} break;
			} break;
		}
		}
	}
}

void GameUpdate(Game* game)
{
	SDL_UpdateWindowSurface(game->win);
	GameProcessEvents(game);
}

void GameDraw(Game* self)
{
	int ticks = SDL_GetTicks();
	if (ticks - self->lastUpdate < 60) return;
	else self->lastUpdate = ticks;

	SDL_SetRenderDrawColor(self->rer, 0, 0, 0, 255);
	SDL_RenderClear(self->rer);

	switch (self->menu.status)
	{
	case MENU_ACTIVE:   MenuDraw(&self->menu, self->rer); break;
	case MENU_UNACTIVE: BoxDraw(&self->box, self->rer); break;
	}

	if (BoxIsComplete(&self->box))
	{
		SDL_RenderCopy(self->rer, self->restartMessage.data, 0, &self->restartMessage.rect);
	}

	SDL_RenderPresent(self->rer);
}

int GameRun(Game* game)
{
	while (game->run)
	{
		GameUpdate(game);
		GameDraw(game);
	}
	GameUninit(game);
	return 0;
}
