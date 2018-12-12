/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

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