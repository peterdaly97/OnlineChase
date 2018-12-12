#pragma once
#include "stdio.h"
#include "LTexture.h"
#include <SDL_image.h>
#include <string>

class Dot
{
public:
	//The dimensions of the dot
	static const int DOT_WIDTH = 50;
	static const int DOT_HEIGHT = 50;

	//Maximum axis velocity of the dot
	float DOT_VEL = 0.2f;

	Dot() {};
	//Initializes the variables
	Dot(bool chaser);
	~Dot();

	void Init(SDL_Renderer *gRenderer);
	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);

	//Moves the dot
	void move(int SCREEN_HEIGHT, int SCREEN_WIDTH);

	//Shows the dot on the screen
	void render(SDL_Renderer *gRenderer);

	std::string GetPosAsString();

	bool Checkcollision(int centerX, int centerY);

	bool GetLocal() { return isLocalplayer; };

	float GetCenterX();
	float GetCenterY();

	void SetPosition(float x, float y);

	std::string message = "";

	bool isChaser;

private:
	bool isLocalplayer;
	

	//The X and Y offsets of the dot
	float mPosX, mPosY;

	int width, height;

	float mCenterX, mCenterY;
	//The velocity of the dot
	float mVelX, mVelY;

	LTexture gDotTexture;
};