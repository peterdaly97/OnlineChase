//Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include <iostream>

#include "game.h"

int main(int argc, char* args[])
{
	Game * game = new Game();
	game->run();

	return 0;
}