#include "key.h"
#include  "SDL2/SDL.h"
Key::Key() {

}
Key::Key(float wx, float wy) {
	x = wx;
	y = wy;
	height = 64;
	width = 64;
}
Key::~Key() {
	 //SDL_DestroyTexture(texture);
	//delete texture;
}

/*void Wall::loadImage(Graphics& graphics, const std::string path){
	SDL_Surface* img = graphics.addImage(path.c_str());
	texture = SDL_CreateTextureFromSurface(graphics.getRenderer(),
		img);
	SDL_FreeSurface(img);
}*/

void Key::update(float time, Graphics& graphics) {

}
void Key::setColor(Color col) {
	color = col;
}
Color Key::getColor() {
	return color;
}

