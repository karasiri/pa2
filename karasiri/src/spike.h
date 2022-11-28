#ifndef SPIKE_H
#define SPIKE_H
class Graphics;
#include "block.h"
/** Class Spike
Represent enemy in game
stationary object
*/

class Spike : public Block {
public:
	Spike();
	Spike(float wx, float wy);
	Spike(float wx, float wy, int color);
	~Spike();

	virtual void update(float time, Graphics& graphics);
private:
	int color;
};

#endif //SPIKE_H
