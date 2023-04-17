#pragma once

#include <SDL.h>

#include "text.h"

#define MENU_PLAY_TEXT     "Play"
#define MENU_RECORDS_TEXT  "Records"
#define MENU_SETTINGS_TEXT "Settings"
#define MENU_QUIT_TEXT     "Quit"
#define MENU_FIELD_3X_TEXT "3x3"
#define MENU_FIELD_4X_TEXT "4x4"
#define MENU_FIELD_5X_TEXT "5x5"
#define MENU_FIELD_6X_TEXT "6x6"
#define MENU_TEXT_SIZE     50
#define MENU_TEXT_PADDING  30

enum MENU_STATUS
{
	MENU_ACTIVE,
	MENU_UNACTIVE,
	MENU_SETTINGS,
	MENU_CHANGED_FIELD,
};

enum MENU_TEXTURES {
	MENU_TEXTURE_PLAY,
	MENU_TEXTURE_RECORDS,
	MENU_TEXTURE_SETTINGS,
	MENU_TEXTURE_QUIT,
	MENU_TEXTURE_FIELD_3X_TEXT,
	MENU_TEXTURE_FIELD_4X_TEXT,
	MENU_TEXTURE_FIELD_5X_TEXT,
	MENU_TEXTURE_FIELD_6X_TEXT,
};

#define MENU_TEXTURES_NUM 8
#define menu_offset(status) (status == MENU_SETTINGS ? MENU_TEXTURES_NUM / 2 : 0)

typedef struct Menu
{
	Texture  textures[MENU_TEXTURES_NUM];
	SDL_Rect rect;
	int      status;
	int      textSize;
	int      field;
} Menu;

int MenuInit(Menu* self, SDL_Renderer* rer, SDL_Rect box);
int MenuUpdate(Menu* self);
int MenuDraw(Menu* self, SDL_Renderer* rer);
