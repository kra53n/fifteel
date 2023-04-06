#include "game.h"

int main(int argc, char** argv)
{
	Game game;
	GameInit(&game);
	GameRun(&game);
	return 0;
}