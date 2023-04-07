#pragma once

#include <SDL.h>

#define GAME_TITLE  "fifteel (fifiteen puzzle game)"
#define GAME_WIDTH  1280
#define GAME_HEIGHT 720

#include "box.h"
#include "menu.h"

typedef struct Game
{
	SDL_Window*   win;
	SDL_Renderer* rer;
	int           run;
	Box           box;
	Menu          menu;
} Game;

int GameInit(Game* game);
int GameRun(Game* game);