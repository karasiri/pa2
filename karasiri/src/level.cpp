#include  "SDL2/SDL.h"
#include "level.h"
#include "graphics.h"
#include <string>
#include <iostream>
#include "block.h"
#include "wall.h"
#include <fstream>
#include <string.h>
#include <sstream>
#include <stdio.h>
#include "key.h"
#include "door.h"

clock_t startTime2;
clock_t timePassed2;
clock_t currentTime2;
double secondsPassed2;
Level::Level() {
}
Level::Level(Graphics& graphics){
	textTexture = NULL;
	timer = 0;
	currentLevel = 1;
	this->graphics = &graphics;
	health = new Health();
	health->loadImage(graphics, "src/images/heart.bmp");
	startTime2 = 0;
}

Level::~Level(){
	 delete background;
	 SDL_DestroyTexture(textureBG);
	 SDL_DestroyTexture(textureBG1);
	 for (Key * key: keys) {
	 		SDL_DestroyTexture(key->getTexture());
	 		delete key;
	 }
	 for (Wall * wall: vecOfWalls ) {
	 		SDL_DestroyTexture(wall->getTexture());
	 		delete wall;
	 }
	 for (Door * door: doors) {
	 	 	//SDL_DestroyTexture(door->getTexture());
	 		//delete door->getTexture();
	 		door->deleteDoor();
		  delete door;
	 }
	 for (Block* spike: spikes) {
	 	 	SDL_DestroyTexture(spike->getTexture());
	 		delete spike;
	 }
	 for (Block* enemy: enemies) {
	 	 	SDL_DestroyTexture(enemy->getTexture());
	 		delete enemy;
	 }
	 
 //delete textureBG;
//delete textureBG1;

}
/** load all images and textures*/
void Level::loadImage(Graphics& graphics, const std::string path) {
	background = graphics.addImage(path.c_str());
	textureBG = SDL_CreateTextureFromSurface(graphics.getRenderer(),
		background);
	background = graphics.addImage("src/images/sea_background2.bmp");
	textureBG1 = SDL_CreateTextureFromSurface(graphics.getRenderer(),
		background);
	SDL_FreeSurface(background);
}
// load text texture if needed
void Level::loadText(Graphics& graphics, const std::string path) {
	background = graphics.addImage(path.c_str());
	textTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(),
		background);
	SDL_FreeSurface(background);
}


/** update level*/
void Level::update(Graphics &graphics) {
	for (Block* shark : enemies) {
		shark->update(0,graphics);
	}
}
/** load all levels*/
 void Level::loadLevels(Graphics& graphics, std::vector<Level*> &levels) {	 
	for (int i = 1; i < 4; i++) {
		Level * l = readFile(i, graphics);

		l->loadImage(graphics, "src/images/sea_background1.bmp");
		levels.push_back(l);
	}
}
 /** return texture of text */
SDL_Texture* Level::getTextTexture() {
	return textTexture;
}

void Level::addWall(Wall * w) {
	vecOfWalls.push_back(w);
	(*w).loadImage(*graphics, "src/images/wall.bmp");
}
void Level::addSpike(Spike* s) {
	spikes.push_back(s);
	(*s).loadImage(*graphics, "src/images/ship4.bmp");
}

/** add door and door texture depending on color*/
void Level::addDoor(Door* d, int color) {
	doors.push_back(d);
	doorsPresent.push_back(true);
	if (color == 0) {
		(*d).setTexture(*graphics, "src/images/yellowDoor.bmp");
		d->setColor(YELLOW);
		std::cout << "DOOR COLOR " << d->getColor() << std::endl;
	}
	if (color == 1) {
		(*d).setTexture(*graphics, "src/images/redDoor.bmp");
		d->setColor(RED);
	}
	if (color == 2) {
		(*d).setTexture(*graphics, "src/images/blueDoor.bmp");
		d->setColor(BLUE);
	}
}
/** add key and key texture depending on color*/
void Level::addKey(Key* k, int color) {
	keys.push_back(k);
	keysPresent.push_back(true);
	if (color == 0) {
		(*k).loadImage(*graphics, "src/images/yellowKey.bmp");
		k->setColor(YELLOW);
	}
	if (color == 1) {
		(*k).loadImage(*graphics, "src/images/redKey.bmp");
		k->setColor(RED);
	}
	if (color == 2) {
		(*k).loadImage(*graphics, "src/images/blueKey.bmp");
		k->setColor(BLUE);
	}
}
void Level::addShark(Shark* shark) {
	enemies.push_back(shark);
	shark->loadImage(*graphics, "src/images/enemyRight.bmp");
}

//* draw current level */
void Level::draw(Fish * fish, Graphics& graphics) {
	if (timer >= 1400) {
		timer = 0;
	}
	if (timer < 700 ) {
		SDL_RenderCopy(graphics.getRenderer(), textureBG, NULL, NULL);
	}
	if (timer >= 700) {
		SDL_RenderCopy(graphics.getRenderer(), textureBG1, NULL, NULL);
	}
	timer++;
	
	for (unsigned int i = 0; i < vecOfWalls.size(); i++) {

		vecOfWalls[i]->draw(graphics);
	}
	for (unsigned int i = 0; i < keys.size(); i++) {
		if (keysPresent[i]) {
			keys[i]->draw(graphics);
		}
	}
	for (unsigned int i = 0; i < doors.size(); i++) {
		if (doorsPresent[i]) {
			doors[i]->draw(graphics);
		}
	}
	for (unsigned int i = 0; i < spikes.size(); i++) {
		spikes[i]->draw(graphics);
	}
	for (unsigned int i = 0; i < enemies.size(); i++) {
		enemies[i]->draw(graphics);
	}
	int shift = 0;
	for (int i = 0; i < fish->getCurrentHealth(); i++) {
		SDL_Rect dstrect = { shift, 16, 32, 32 };
		SDL_RenderCopy(graphics.getRenderer(), health->getTexture(), NULL, &dstrect);
		shift += 32;
	}
	if (textTexture != NULL) {
		SDL_Rect dstrect = { 200, 280, 600, 70 };
		SDL_RenderCopy(graphics.getRenderer(), textTexture, NULL, &dstrect);
	}
}

void Level::setTextTexture(SDL_Texture * texture) {
	textTexture = texture;
}

/** read data from file */
 Level* Level::readFile(int numOfLevel, Graphics &graphics) {
	Level* level = new Level(graphics);
	std::ifstream file("src/files/level"+ std::to_string(numOfLevel)+".txt");
	std::string input;
	std::stringstream ss;
	std::stringstream delim;
	float x;
	float y;
	int color;
	int next = 0;
	while (!file.eof()) {
		std::getline(file, input, '$');
		std::stringstream ss;
		ss << input;
		while (!ss.eof()) {
			
			if (ss.eof()) break;
			if (next == 0) {
				ss >> x;
				ss >> y;
				level->addWall(new Wall(x, y));
			}
			if (next == 1) {
				ss >> x;
				ss >> y;
				ss >> color;
				//Key* wall = new Key(x, y);
				level->addKey(new Key(x, y), color);
			}
			if (next == 2) {
				Door* door = new Door();
				for (int i = 0; i < 2; i++) {
					ss >> x;
					ss >> y;
					ss >> color;
					Wall* wall = new Wall(x, y, color);
					door->getBlocks().push_back(wall);
				}
				level->addDoor(door, color);
			}
			if (next == 3) {
				ss >> x;
				ss >> y;
				level->spawnX = x;
				level->spawnY = y;
			}
			if (next == 4) {
				ss >> x;
				ss >> y;
				level->addSpike(new Spike(x, y));
				std::cout << "spike x " << x << " spike y " << y << std::endl;
			}
			if (next == 5) {
				float startX, startY, endX, endY;
				ss >> startX;
				ss >> startY;
				ss >> endX;
				ss >> endY;
				ss >> x;
				ss >> y;
				level->addShark(new Shark(graphics,startX,startY,endX,endY, x, y));
			}
		}
		next++;
	}
	file.close();
	return level;
}
std::vector<Wall*> & Level::getVecOfWalls() {
	return vecOfWalls;
}

std::vector<Door*> & Level::getDoors() {
	return doors;
}

std::vector<Key*> & Level::getKeys() {
	return keys;
}
/** return information about door condition 
if door is open or close 
*/
std::vector<bool> & Level::getDoorsPresent() {
	return doorsPresent;
}

/** add information about doors condition
if door is open or close
*/
void Level::setDoorsPresent(int index, bool present) {
	doorsPresent[index] = present;
}
/** add information about keys condition
*/
void Level::setKeysPresent(int index, bool present) {
	keysPresent[index] = present;
}
/** return information about keys condition
if key has taken or not
*/
std::vector<bool> & Level::getKeysPresent() {
	return keysPresent;
}
void Level::incrementLevel() {
	currentLevel++;
}

/** return place on the x-axis, where player will spawn */
float Level::getSpawnX() {
	return spawnX;
}
/** return place on the y-axis, where player will spawn */
float Level::getSpawnY() {
	return spawnY;
}

std::vector<Block*>& Level::getSpikes() {
	return spikes;
}

std::vector<Block*>& Level::getEnemies() {
	return enemies;
}
std::ostream& operator <<(std::ostream& os, const Level& level) {
	for (unsigned int i = 0; i < level.doorsPresent.size(); i++) {
		os << ((level.doorsPresent[i] == true) ? "1" : "0");
		if (i < level.doorsPresent.size()-1) os << " ";
	}
	os << "$";
	for (unsigned int i = 0; i < level.keysPresent.size(); i++) {
		os << ((level.keysPresent[i] == true) ? "1" : "0");
		if (i < level.keysPresent.size() - 1) os << " ";
	}
	os << "$";
	return os;
}


