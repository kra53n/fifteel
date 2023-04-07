#pragma once

#include <SDL.h>

#include "text.h"

#define MENU_PLAY_TEXT "Play"
#define MENU_QUIT_TEXT "Quit"
#define MENU_TEXT_SIZE 50

enum MENU_STATUS
{
	MENU_ACTIVE, MENU_UNACTIVE
};

typedef struct Menu
{
	Texture play;
	Texture quit;
	int     status;
	int     textSize;
} Menu;

int MenuInit(Menu* self, SDL_Renderer* rer, SDL_Rect box);
int MenuUpdate(Menu* self);
int MenuDraw(Menu* self, SDL_Renderer* rer);