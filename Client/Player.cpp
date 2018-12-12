#include "Player.h"

Player::Player(SDL_Renderer* gRenderer) {
	destRect.x = 100;
	destRect.y = 100;
	destRect.w = 100;
	destRect.h = 100;

	sourceRect.x = 0;
	sourceRect.y = 0;
	sourceRect.w = 60;
	sourceRect.h = 50;

	gTexture = loadTexture("grid.png", gRenderer);
}

Player::~Player() {

}

void Player::update(SDL_Event & event) {
	if(event.key.keysym.sym == SDLK_UP)
		destRect.y -= 5; 
	if (event.key.keysym.sym == SDLK_DOWN)
		destRect.y += 5;
	if (event.key.keysym.sym == SDLK_LEFT)
		destRect.x -= 5;
	if (event.key.keysym.sym == SDLK_RIGHT)
		destRect.x += 5;
	
	
}

void Player::render(SDL_Renderer* gRenderer) {
	//Render texture to screen
	SDL_RenderCopy(gRenderer, gTexture, &sourceRect, &destRect);
}

SDL_Texture* Player::loadTexture(std::string path, SDL_Renderer* gRenderer) {
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}