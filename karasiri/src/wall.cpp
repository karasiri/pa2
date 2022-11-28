#include "wall.h"
#include  "SDL2/SDL.h"

Wall::Wall() {

}

Wall::Wall(float wx, float wy) {
	x = wx;
	y = wy;
	height = 64;
	width = 64;
	
}
Wall::Wall(float wx, float wy, int color) {
	x = wx;
	y = wy;
	height = 64;
	width = 64;
	this->color = color;
}
Wall::~Wall() {

}

void Wall::update(float time, Graphics& graphics) {

}
