#pragma once
#ifndef FISH_H
#define FISH_H
#include "graphics.h"
struct SDL_Texture;
struct SDL_Surface;
#include "block.h"
#include "key.h"
#include<vector>
#include "health.h"
/** Class Fish
Holds all information dealing with player in game
*/
class Fish : public Block {

public:
	Fish();
	Fish(Graphics& graphics);
	~Fish();
	float getNewX();
	float getNewY();
	void setNewX(float newX);
	void setNewY(float newY);
	virtual SDL_Texture* getTexture();
	virtual void update(float time, Graphics& graphics);
	bool getKey(int position);
	void setKey(int position, bool key);
	void setX(float new_x);
	void setY(float new_y);
	void updateKeys(bool key1, bool key2, bool key3);
	virtual void draw(Graphics& graphics);
	friend std::ostream& operator <<(std::ostream& os, const Fish& fish);
	int getCurrentHealth();
	void setCurrentHealth(int value);
	void dead(Graphics& graphics);
protected:
	bool direction;
	float speed;
	float newX,newY;
	int maxHealth;
	int currentHealth;
	SDL_Texture* healthTexture;
	SDL_Surface* background;
	std::vector<bool> keys;
};

#endif // !FISH_H
