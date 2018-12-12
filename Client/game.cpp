#include "game.h"

Game::Game() {

	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());

		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());

			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());

				}
			}
		}
	}

	if (!grassTexture.loadFromFile("grass.jpg", gRenderer))
	{
		printf("Failed to load dot texture!\n");
	}
	if (!loseTexture.loadFromFile("lose.png", gRenderer))
	{
		printf("Failed to load dot texture!\n");
	}
	if (!winTexture.loadFromFile("win.png", gRenderer))
	{
		printf("Failed to load dot texture!\n");
	}
	
	if (client.run()) {
		client.sendMessage("Join, Hello,");
	}
	
	
}

Game::~Game() {

	//Free loaded image
	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

	//Destroy window    
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

void Game::update() {
	if (gameRound == 1) {
		score++;
	}
	if (gameRound == 2 && !client.gameOver && !win) {
		score--;
	}
	if (client.win) {
		win = true;
	}
	if (!client.gameOver && !win) {
		if (joined) {
			dot2->move(SCREEN_WIDTH, SCREEN_HEIGHT);
		}
		if (client.enemyJoin) {
			dot->move(SCREEN_WIDTH, SCREEN_HEIGHT);
		}
		client.receive();
		if (client.number == 2 && !joined) {
			dot2 = new Dot(true);
			dot2->Init(gRenderer);
			joined = true;
		}
		else if (client.number == 3 && !joined) {
			dot2 = new Dot(false);
			dot2->Init(gRenderer);
			joined = true;

			dot = new Dot(true);

			dot->Init(gRenderer);

			enemyJoined = true;
			client.enemyJoin = true;
		}
		if (client.enemyJoin && !enemyJoined) {

			dot = new Dot(false);

			dot->Init(gRenderer);

			enemyJoined = true;
		}

		if (joined) {
			client.sendMessage(dot2->message);
		}

		if (client.posUpdate.size() > 1) {
			dot->SetPosition(client.posUpdate.at(0), client.posUpdate.at(1));
		}

		if (joined && enemyJoined && dot2->isChaser) {
			if (dot2->Checkcollision(dot->GetCenterX(), dot->GetCenterY())) {
				if (gameRound == 1) {
					client.sendMessage("Restart,");
					gameRound = 2;
					if (dot2->isChaser) {
						dot2 = new Dot(false);
						dot = new Dot(true);
					}
					else {
						dot2 = new Dot(true);
						dot = new Dot(false);
					}
					dot2->Init(gRenderer);
					dot->Init(gRenderer);
				}
				else {
					if (score < 0) {
						client.sendMessage("Win,");
						client.gameOver = true;
					}
					else {
						client.sendMessage("End,");
						win = true;
					}
					
					
				}
				
			}
			
		}
		client.receive();
		if (client.restart) {
			client.restart = false;
			if (dot2->isChaser) {
				dot2 = new Dot(false);
				dot = new Dot(true);
			}
			else {
				dot2 = new Dot(true);
				dot = new Dot(false);
			}
			dot2->Init(gRenderer);
			dot->Init(gRenderer);
			gameRound = 2;
		}
	}
	else {
		if (dot2->isChaser) {
			if (score < 0) {
				client.sendMessage("Win,");
			}
			else {
				client.sendMessage("End,");
			}
		}
		
	}
	
	client.receive();

}

void Game::render() {
	//Clear screen
	SDL_RenderClear(gRenderer);

	if (!client.gameOver && !win) {
		grassTexture.render(0, 0, gRenderer);
		if (client.enemyJoin) {
			dot->render(gRenderer);
		}
		if (joined) {
			dot2->render(gRenderer);
		}
	}
	else if(win){
		winTexture.render(0, 0, gRenderer);
	}
	else {
		loseTexture.render(0, 0, gRenderer);
	}

	
	

	//Update screen
	SDL_RenderPresent(gRenderer);

	
}

void Game::run() {
	bool quit = false;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
			//dot->handleEvent(event);
			if (joined) {
				dot2->handleEvent(event);
			}
			
			
			update();
			render();
		}
		
		update();
		render();

	}
}

