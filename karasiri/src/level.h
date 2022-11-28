#pragma once
#ifndef LEVEL_H
#define LEVEL_H
#include "level.h"
#include "fish.h"
#include "wall.h"
#include "key.h"
#include "door.h"
#include "spike.h"
#include "shark.h"
#include "health.h"
class Wall;
#include <vector>
/** Class Level
* Holds all information about levels in game
* Load levels from file*/
class Collisions;

struct SDL_Rect;

class Level {

public:
	Level();
	Level(Graphics& graphics);
	~Level();
	
	void loadImage(Graphics& graphics, const std::string path);
	SDL_Texture* getTextTexture();
	void draw(Fish* fish, Graphics& graphics);
	void update(Graphics& graphics);
	int currentLevel;
	static void loadLevels(Graphics& graphics, std::vector<Level*>& levels);
	void loadText(Graphics& graphics, const std::string path);
	std::vector<Wall*>& getVecOfWalls();
	void addWall(Wall * w); 
	static Level* readFile(int numOfLevel, Graphics& graphics);
	std::vector<Door*>& getDoors();
	std::vector<Key*>& getKeys();
	std::vector<Block*>& getSpikes();
	std::vector<Block*>& getEnemies();
	void addDoor(Door* d, int color);
	void addKey(Key* k, int color);
	void addSpike(Spike* s);
	void addShark(Shark* shark);
	void incrementLevel();
	float getSpawnX();
	float getSpawnY();
	void setTextTexture(SDL_Texture* texture);
	std::vector<bool> & getDoorsPresent();
	std::vector<bool> & getKeysPresent();
	void setDoorsPresent(int index, bool present);
	void setKeysPresent(int index, bool present);
	friend std::ostream& operator <<(std::ostream& os, const Level& level);
	bool randomBool();
private:
	SDL_Texture* textureBG;
	SDL_Texture* textureBG1;
	SDL_Texture* textTexture;
	SDL_Surface* background;
	float spawnX;
	float spawnY;
	std::vector<Wall*> vecOfWalls;
	Graphics* graphics;
	//Key* key;
	std::vector<bool> doorsPresent;
	std::vector<bool> keysPresent;
	std::vector<Door*> doors;
	std::vector<Key*> keys;
	std::vector<Block*> spikes;
	std::vector<Block*> enemies;
	int timer;
	Health* health;
	bool gameOver;
	//bool openDoor;


};

#endif // !LEVEL_H
