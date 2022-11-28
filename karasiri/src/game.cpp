#include  "SDL2/SDL.h"
#include "game.h"
#include "graphics.h"
#include <iostream>
#include <fstream>
#include "level.h"
#include "fish.h"
#include "block.h"
#include "color.h"
#include <sstream>
#include "color.h"

/* Game class
 * This class holds information for game loop and detects collisions
 */

namespace {
	const int frame = 50;
	const int maxFrame = 1000 / frame;
	clock_t startTime;
	clock_t timePassed;
	clock_t currentTime;
	double secondsPassed;
}


Game::Game() {
	SDL_Init(SDL_INIT_EVERYTHING);
	graphics = new Graphics();
	Level::loadLevels(*graphics, levels);
	currentLevel = 0;
	level = levels[currentLevel];
	fish = new Fish(*graphics);
	fish->setX(level->getSpawnX());
	fish->setY(level->getSpawnY());
	startTime = 0;
	gameOver = false;
	this->gameLoop();

}
Game::~Game() {
	//delete fish;
	//
	//delete graphics;
	//graphics->~Graphics();
	//level->~Level();
	//delete level;
	//for (Level* level : levels) delete level;
}
void Game::gameLoop() {
	
	SDL_Event event;

	
	bool q = true;
	int lastUpdate = SDL_GetTicks(); 

	// The game loop 
	while (q) {	
		while (SDL_PollEvent(&event)) {
//			std::cout << "wile 2 tut" << std::endl;
			if (event.type == SDL_QUIT) {
				q = false;
		
			}
			switch (event.type) {
				
			case SDL_KEYDOWN: 				
				switch (event.key.keysym.sym) {
				case SDLK_F1:
					// start a new game
					newGame();
					break;
				case SDLK_F7:
					// save game 
					if (gameOver) {
						break;
					}
					saveGame();
					break;
				case SDLK_F9:
					// load game
					newGame();
					loadGame();
					break;
				case SDLK_f:
					// open door if key has taken
					if (gameOver) {
						break;
					}
					if (checkDoorCollisions(true) ) {
					}
						break;
				
				case SDLK_UP:		
					if (gameOver) {
						break;
					}
					fish->setNewY(-1);
					break;
				case SDLK_DOWN:
					if (gameOver) {
						break;
					}
					fish->setNewY(1);
							
					break;
				case SDLK_LEFT:
					if (gameOver) {
						break;
					}
					fish->loadImage(*graphics, "src/images/heroLeft.bmp");
					fish->setNewX(-1);
						
					break;
				case SDLK_RIGHT:
					if (gameOver) {
						break;
					}
					fish->loadImage(*graphics, "src/images/heroRight.bmp");
					fish->setNewX(1);
						
					break;

				default:
					break;
				}
			break;
			case SDL_KEYUP :
						switch (event.key.keysym.sym) {
							case SDLK_UP:
								fish->setNewY(0);
								break;
							case SDLK_DOWN:
								fish->setNewY(0);
								break;
							case SDLK_LEFT:
								fish->setNewX(0);
								break;
							case SDLK_RIGHT:
								fish->setNewX(0);
								break;
							default:
								break;
							}
						break;
						 
			}
			
		}		
		const int currentTime = SDL_GetTicks();
		int elapsedTime = currentTime - lastUpdate;
		if (elapsedTime < maxFrame) this->update(elapsedTime);
		else this->update(maxFrame);		
		lastUpdate = currentTime;
		this->draw();
	}

	/*SDL_DestroyTexture(level.getTextureBG());
	SDL_DestroyTexture(level.getTextTexture());
	//SDL_DestroyTexture(fish.getTexture());
	SDL_DestroyRenderer(graphics.getRenderer()); 
	SDL_DestroyWindow(graphics.getWindow()); */
	SDL_Quit(); 
}
void Game::draw() {
	SDL_RenderClear((*graphics).getRenderer());
	level->draw(fish, *graphics);
	fish->draw((*graphics));
	SDL_RenderPresent((*graphics).getRenderer());
}
void Game::update(float time) {
	level->update(*graphics);
	if (checkCollisions()) {
		return;
	}
	fish->update(time, *graphics);
	//std::cout << "tut" << fish.getX() << " " << fish.getY()<< std::endl;
}

/** Check all collisions */
bool Game::checkCollisions() {
	if (checkWallCollisions()) return true;
	checkKeyCollisions();
	if (checkDoorCollisions(false)) return true;
	checkExitCollisions();
	if (checkEnemyCollisions(level->getSpikes())) return true;
	if (checkEnemyCollisions(level->getEnemies())) return true;
	return false;
}

/** checkWallCollisions 
check if wall collisions has occurred 
*/

bool Game::checkWallCollisions() {
	for (unsigned int i = 0; i < level->getVecOfWalls().size(); i++) {
		if (checkBlockCollisions((*level->getVecOfWalls()[i]))) {
			return true;
		}
	}
	return false;
}

/** checkKeyCollisions
check if collisions with keys has occurred and 
add information about taken keys 
*/

void Game::checkKeyCollisions() {
	for (unsigned int i = 0; i < level->getKeys().size(); i++) {
		if (checkBlockCollisions((*level->getKeys()[i]))) {
			fish->setKey(level->getKeys()[i]->getColor(), true);
			(level->getKeysPresent())[i] = false;
		}
	}
}
/** checkDoorCollisions
check if doors collisions has occurred
and open door if key with corresponding color has taken 
and button 'F' was pressed
*/
bool Game::checkDoorCollisions(bool fIsPressed) {
	for (unsigned int i = 0; i < level->getDoors().size(); i++) {
		if (!(level->getDoorsPresent())[i]) {
			continue;
		}
		for (int j = 0; j < 2; j++) {
			Block * block = ((level->getDoors()[i])->getBlocks())[j];
			if (checkBlockCollisions(*block)) {
				if (fIsPressed && fish->getKey(level->getDoors()[i]->getColor()) ){
					(level->getDoorsPresent())[i] = false;
					//(level->getDoors()).erase(level->getDoors().begin() + i);
					return false;
				}
				return true;
			}
		}
	}
	return false;
}

/** check if collisions with enemy 
and change current lives if collisions has occurred*/
bool Game::checkEnemyCollisions(std::vector<Block*> enemies) {
	for (unsigned int i = 0; i < enemies.size(); i++) {
		if (checkBlockCollisions(*(enemies[i]))) {
			currentTime = clock();
			timePassed = currentTime - startTime;
			secondsPassed = timePassed / (double)CLOCKS_PER_SEC;
			std::cout << "secondsPassed " << secondsPassed << std::endl;
			if (secondsPassed > 1) {
				startTime = clock();
				int health = fish->getCurrentHealth();
				fish->setCurrentHealth(health - 1);
				if (fish->getCurrentHealth() == 0) {
					fish->dead(*graphics);
					level->loadText(*graphics, "src/images/gameOver.bmp");
					gameOver = true;
				}
			}
			return true;
		}
	}
	return false;
}
/** check if collisions with exit has occurred
and update level*/
void Game::checkExitCollisions() {
	if (fish->getX() >= 1024+32) {
		if (currentLevel < (int)levels.size() - 1) {
			level = levels[++currentLevel];
			fish->setX(level->getSpawnX());
			fish->setY(level->getSpawnY());
			fish->updateKeys(0,0,0);
		}
	}
}

/** check block collisions */
bool Game::checkBlockCollisions(Block &block) {
	int x1 = fish->getX() + fish->getNewX();
	int y1 = fish->getY() + fish->getNewY();
	int x2 = x1 + 64;
	int y2 = y1;
	int x3 = x1;
	int y3 = y1 + 64;
	int x4 = x1 + 64;
	int y4 = y1 + 64;

	if (checkIntersection(x1, y1, block) ||
		checkIntersection(x2, y2, block) ||
		checkIntersection(x3, y3, block) ||
		checkIntersection(x4, y4, block)) {
			return true;
	}


	return false;
}
/** save current game */
void Game::saveGame() {
	std::ofstream of("src/files/save.txt");
	of << currentLevel << " " << *fish << *level << std::endl;
	of.close();
}
/** start new game */
void Game::newGame() {
	currentLevel = 0;
	level->setTextTexture(NULL);
	level = levels[currentLevel];
	for (Level* l : levels) {
		for (unsigned int i = 0; i < l->getDoorsPresent().size(); i++) {
			l->getDoorsPresent()[i] = true;
		}
		for (unsigned int i = 0; i < l->getKeysPresent().size(); i++) {
			l->getKeysPresent()[i] = true;
		}
	}

	fish->setX(level->getSpawnX());
	fish->setY(level->getSpawnY());
	fish->setCurrentHealth(3);
	fish->loadImage(*graphics, "src/images/heroRight.bmp");
	gameOver = false;
}
/** load saved game */
void Game::loadGame(){
	std::cout << "set level " << std::endl;
	std::ifstream file("src/files/save.txt");
	float value;
	bool key1, key2, key3;
	std::string input;
	std::stringstream ss;
	std::getline(file, input, '$');
	ss << input;
	ss >> currentLevel;
	level = levels[currentLevel];
	ss >> value;
	std::cout << " fish x " << value << std::endl;
	fish->setX(value);
	ss >> value;
	std::cout << " fish y " << value << std::endl;
	fish->setY(value);
	ss >> value;
	fish->setCurrentHealth(value);
	ss >> key1 >> key2 >> key3;
	fish->updateKeys(key1, key2, key3);
	int index = 0;
	std::getline(file, input, '$');
	std::stringstream s1;
	s1 << input;
	while (!s1.eof()) {		
		s1 >> value;
		level->setDoorsPresent(index, value);
		index++;
	}
	index = 0;
	std::getline(file, input, '$');
	std::stringstream s2;
	s2 << input;
	while (!s2.eof()) {
		s2 >> value;
		level->setKeysPresent(index, value);
		index++;
	}

	file.close();
}
/** check block intersection */
bool Game::checkIntersection(float x, float y, Block& wall) {
	float x1 = wall.getX();
	float y1 = wall.getY();
	float x2 = wall.getX() + wall.getWidth();
//	int y2 = wall.getY();
//	int x3 = wall.getX();
	float y3 = wall.getY() + wall.getHeight();
//	int x4 = wall.getX() + wall.getWidth();
	//int y4 = wall.getY() + wall.getHeight();;
	if (x >= x1 && x <= x2 && y >= y1 && y <= y3) {
		return true;
	}
	return false;
}

