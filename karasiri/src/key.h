#pragma once
#ifndef KEY_H
#define KEY_H
#include "color.h"
#include "block.h"
/* Class Key 
 * This class holds information about keys in game
 */
class Key : public Block {
public:
	Key();
	Key(float wx, float wy);
	~Key();
	virtual void update(float time, Graphics& graphics);
	void setColor(Color color);
	Color getColor();
private: 
	Color color;
};


#endif // KEY_H




