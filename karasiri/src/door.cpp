#include "door.h"

Door::Door() {
	open = false;
}
Door::~Door() {

}

std::vector<Block*>& Door::getBlocks () {
	return blocks;
}
void Door::setTexture(Graphics &graphics, const std::string path) {
	for (int i = 0; i < 2; i++) {
		blocks[i]->loadImage(graphics, path.c_str());
	}
}
void Door::setColor(Color color) {
	this->color = color;
}

Color Door::getColor() {
	return color;
}
void Door::draw(Graphics& graphics) {
	for (int i = 0; i < 2; i++) {
	//	SDL_DestroyTexture(blocks[i]->getTexture());
		blocks[i]->draw(graphics);
	}
}


void Door::deleteDoor(){
	for (int i = 0; i < 2; i++) {
	SDL_DestroyTexture(blocks[i]->getTexture());
		delete blocks[i];
	}
}
