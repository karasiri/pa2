
#ifndef WALL_H
#define WALL_H
class Graphics;
#include "block.h"

/** Class Wall
* Represent wall in game
*/
class Wall : public Block {
public:
	Wall();
	Wall(float wx, float wy);
	Wall(float wx, float wy, int color);
	~Wall();

	virtual void update(float time, Graphics& graphics);
private:
	int color;
};

 

#endif // !WALL_H

