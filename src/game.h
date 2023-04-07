#pragma once

#include <SDL.h>

#define GAME_TITLE  "fifteel (fifiteen puzzle game)"
#define GAME_WIDTH  1280
#define GAME_HEIGHT 720

#define GAME_RESTART_MESSAGE_TEXT "You are win! Press R to restart"
#define GAME_RESTART_MESSAGE_SIZE 50

#include "box.h"
#include "menu.h"

typedef struct Game
{
	SDL_Window*   win;
	SDL_Renderer* rer;
	int           run;
	Box           box;
	Menu          menu;
	Texture       restartMessage;
	int           lastUpdate;
} Game;

int GameInit(Game* game);
int GameRun(Game* game);