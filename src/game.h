#pragma once

#include <SDL.h>

#include "box.h"
#include "menu.h"
#include "timer.h"
#include "texture.h"

#define GAME_TITLE  "fifteel (fifiteen puzzle game)"
#define GAME_WIDTH  1280
#define GAME_HEIGHT 720

#define GAME_RESTART_MESSAGE_TEXT "You are win! Press R to restart"
#define GAME_RESTART_MESSAGE_SIZE 50

enum GAME_TEXTURES
{
	GAME_TEXTURE_TIME,
	GAME_TEXTURE_MOVES,
	GAME_TEXTURE_BEST_TIME,
	GAME_TEXTURE_BEST_MOVES,
	GAME_TEXTURE_RESTART_MESSAGE,
};

#define GAME_TEXTURES_NUM 5

enum GAME_FLAGS
{
	GAME_RUN           = 0x1,
	GAME_WAS_KEY_DOWN  = 0x2,
	GAME_FIRST_STARTED = 0x4,
};

typedef struct Game
{
	SDL_Window*   win;
	SDL_Renderer* rer;
	int           flags;
	Box           box;
	Menu          menu;
	Nums          nums;
	Texture       textures[GAME_TEXTURES_NUM];
	int           lastUpdate;
} Game;

int GameInit(Game* game);
int GameRun(Game* game);
