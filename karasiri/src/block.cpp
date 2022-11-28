#include "block.h"
#include <iostream>
#include  "SDL2/SDL.h"

/** Class block 
Contain all information about basic elements in game

*/
Block::Block() {

}
Block::~Block() {
	 SDL_DestroyTexture(texture);

}


float Block::getX() {
	return x;
}
float Block::getY() {
	return y;
}
void Block::setX(float newX) {
	x = newX;
}
void Block::setY(float newY) {
	y = newY;
}
float Block::getWidth() {
	return width;
}
float Block::getHeight() {
	return height;
}
void Block::loadImage(Graphics& graphics, const std::string path) {
	SDL_Surface* img = graphics.addImage(path.c_str());
	texture = SDL_CreateTextureFromSurface(graphics.getRenderer(),
		img);
	SDL_FreeSurface(img);
}
SDL_Texture* Block::getTexture() {
	return texture;
}
void Block::setTexture(SDL_Texture* newTexture) {
	texture = newTexture;
}

void Block::draw(Graphics& graphics) {
	SDL_Rect dstrect = { (int)x, (int)y, (int)width, (int)height };
	SDL_RenderCopy(graphics.getRenderer(), texture, NULL, &dstrect);
}
