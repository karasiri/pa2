#include  "SDL2/SDL.h"
#include "graphics.h"
#include <iostream>
#include <string>
#include "fish.h"

Fish::Fish(){}

Fish::Fish(Graphics& graphics) {
	width = 64;
	height = 64;
	newX = 0;
	newY = 0;
	speed = 0.3f;
	maxHealth = 3;
	currentHealth = 3;
	for (int i = 0; i < 3; i++) {
		keys.push_back(false);
	}
	loadImage(graphics, "src/images/heroRight.bmp");
}
Fish::~Fish() {

}

SDL_Texture* Fish::getTexture() {
	return texture;
}
/* void update
 * Moves the fish
 */
void Fish::update(float time, Graphics &graphics) {
	x += newX * time*speed;
	y += newY * time*speed;	
}
void Fish::draw(Graphics& graphics) {
	SDL_Rect dstrect = { (int)x, (int)y, (int)width, (int)height };
	SDL_RenderCopy(graphics.getRenderer(), texture, NULL, &dstrect);
}


float Fish::getNewY() {
	return newY;
}
float Fish::getNewX() {
	return newX;
}

void Fish::setNewX(float new_x) {
	newX = new_x;
}
void Fish::setNewY(float new_y) {
	newY = new_y;
}
bool Fish::getKey(int position) {
	return keys[position];
}
void Fish::setKey(int position, bool key) {
	keys[position] = key;
}
/** setX 
* return Fish current position on x axis
*/
void Fish::setX(float new_x) {
	x = new_x;
}
/** setY
* return Fish current position on y axis
*/
void Fish::setY(float new_y) {
	y = new_y;
}
/** updateKeys 
* add information about taken keys
*/
void Fish::updateKeys(bool key1, bool key2, bool key3) {
		keys[0] = key1;
		keys[1] = key2;
		keys[2] = key3;
}

std::ostream& operator <<(std::ostream& os, const Fish& fish) {
	os << fish.x << " " << fish.y << " " << fish.currentHealth << " ";
	
	for (int i = 0; i < 3; i++) {
		if (fish.keys[i]) {
			os << "1";
		}
		else {
			os << "0";
		}
		if (i < 2) os << " ";
		else os << '$';
	}
	return os;
}
int Fish::getCurrentHealth() {
	return currentHealth;
}
void Fish::setCurrentHealth(int value) {
	currentHealth = value;
}

void Fish::dead(Graphics & graphics) {
	loadImage(graphics, "src/images/heroDead.bmp");
}
