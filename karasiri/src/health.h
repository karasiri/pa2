#pragma once

#ifndef HEALTH_H
#define HEALTH_H
class Graphics;
#include "block.h"

/**Class Health
Hold information about player's lives in game 
*/

class Health : public Block {
public:
	Health();
	~Health();

	virtual void update(float time, Graphics& graphics);
private:
	int color;
};
#endif //HEALTH_H
