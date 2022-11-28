#pragma once
#ifndef __GAME_H
#define ____GAME_H
#include "fish.h"
#include "level.h"
#include "graphics.h"
#include "block.h"
#include <vector>
#include  "SDL2/SDL.h"
//struct SDL_Texture;
class Graphics;

/* Game class
 * This class holds information for game loop and detects collisions
 */

class Game {
public:
	Game();
	~Game();
private:
	Fish * fish;
	Level *level;
//	Graphics graphics;
	Graphics *graphics;
//	SDL_Texture* spriteText;
	SDL_Texture* texture;
	int currentLevel;
	std::vector<Level*> levels;
	bool gameOver;
	void gameLoop();
	void draw();
	void update(float time);
	bool checkCollisions();
	bool checkBlockCollisions(Block& block);
	bool checkIntersection(float x, float y, Block& wall);
	bool checkWallCollisions();
	void checkKeyCollisions();
	bool checkEnemyCollisions(std::vector<Block*> enemies);
	bool checkDoorCollisions(bool fIsPressed);
	void checkExitCollisions();
	void saveGame();
	void loadGame();
	void newGame();



};

#endif // ____GAME_H
