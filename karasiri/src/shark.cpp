#include "shark.h"
#include<iostream>


Shark::Shark() {

}
Shark::Shark(Graphics& graphics,float startX, float startY, float endX, float endY, float x, float y) : Fish(graphics){
	direction = 1;
	this->x = x;
	this->y = y;
	this->startX = startX;
	this->startY = startY;
	this->endX = endX;
	this->endY = endY;
	width = 64;
	height = 64;
	speed = 0.7;
}

void Shark::update(float time, Graphics& graphics) {
	if (x > endX) {
		direction = 0;
		loadImage(graphics, "src/images/enemyLeft.bmp");
	}
	if (x < startX) {
		direction = 1;
		loadImage(graphics, "src/images/enemyRight.bmp");
	}
	if (direction) {
		x = x + speed;
	}
	else {
		x = x - speed;
	}
}
