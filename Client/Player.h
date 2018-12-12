#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>

class Player
{
public:
	Player(SDL_Renderer* gRenderer);
	~Player();

	void update(SDL_Event & event);
	void render(SDL_Renderer* gRenderer);

private:
	//Loads individual image as texture
	SDL_Texture* loadTexture(std::string path, SDL_Renderer* gRenderer);

	//Current displayed texture
	SDL_Texture* gTexture = NULL;

	SDL_Rect sourceRect;
	SDL_Rect destRect;

	const int MAX_COUNT = 3000;

	SDL_Event event;
};
#endif // !PLAYER_H

