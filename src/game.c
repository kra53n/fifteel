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

	BoxInit(&self->box);

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

int GameProcessEvents(Game* game)
{
	SDL_Event ev;
	while (SDL_PollEvent(&ev))
	{
		switch (ev.type)
		{
		case SDL_QUIT: GameUninit(game); break;
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
	BoxDraw(&self->box, self->rer);
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
