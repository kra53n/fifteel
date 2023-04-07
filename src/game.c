#include <stdio.h>
#include <stdlib.h>
#include <SDL_ttf.h>

#include "game.h"

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

	return 0;
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
	switch (self->menu.status)
	{
	case MENU_ACTIVE:   MenuDraw(&self->menu, self->rer); break;
	case MENU_UNACTIVE: BoxDraw(&self->box, self->rer); break;
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
