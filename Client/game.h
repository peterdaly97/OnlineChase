#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "Dot.h"
#include "Client.h"

class Game
{
public:
	Game();
	~Game();

	void run();

	void update();
	void render();

	bool master = false;

private:
	//Screen dimension constants
	const int SCREEN_WIDTH = 720;
	const int SCREEN_HEIGHT = 400;

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//The window renderer
	SDL_Renderer* gRenderer = NULL;

	//Current displayed texture
	SDL_Texture* gTexture = NULL;

	SDL_Rect sourceRect;
	SDL_Rect destRect;

	const int MAX_COUNT = 3000;

	SDL_Event event;

	Dot* dot;
	Dot* dot2;
	
	Client client = Client("10.203.69.1", 54000);

	bool joined = false;
	bool enemyJoined = false;

	bool win = false;

	LTexture grassTexture;
	LTexture winTexture;
	LTexture loseTexture;

	int gameRound = 1;
	int score = 0;
};
#endif // !GAME_H
