#pragma once
#ifndef SHARK_H
#define SHARK_H

#include "fish.h"

/** Class Shark
* Represent enemy in game
moving object
*/
class Shark : public Fish {
public:
	Shark();
	Shark(Graphics& graphics, float startX, float startY, float endX, float endY, float x, float y);
	virtual void update(float time, Graphics& graphics);

private:
	float startX;
	float startY;
	float endX;
	float endY;
};


#endif // !SHARK_H