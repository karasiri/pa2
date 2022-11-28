#pragma once
#ifndef DOOR_H
#define DOOR_H
#include "block.h"
#include "color.h"
#include "graphics.h"
#include "vector"
/** Class Door
Represents all information about door in game
*/
class Door {
public:
	Door();
	~Door();
	std::vector<Block*> &getBlocks();
	void setTexture(Graphics& graphics, const std::string path);
	void setColor(Color color);
	Color getColor();
	void draw(Graphics& graphics);
	void deleteDoor();
private:
	Color color;
	bool open;
	std::vector<Block*> blocks;
};




#endif // DOOR_H



