#include "spike.h"
Spike::Spike() {

}

Spike::Spike(float wx, float wy) {
	x = wx;
	y = wy;
	height = 64;
	width = 64;

}
Spike::Spike(float wx, float wy, int color) {
	x = wx;
	y = wy;
	height = 64;
	width = 64;
	this->color = color;
}
Spike::~Spike() {

}

void Spike::update(float time, Graphics& graphics) {

}