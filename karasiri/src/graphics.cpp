
#include  "SDL2/SDL.h"
#include "graphics.h"

Graphics::Graphics() {
	SDL_CreateWindowAndRenderer(1024, 768, 0, &window, &renderer);
	SDL_SetWindowTitle(window, "Sea World");

}

Graphics::~Graphics() {
	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);
}

SDL_Surface* Graphics::addImage(const std::string &image) {
	SDL_Surface* img = SDL_LoadBMP(image.c_str());
	return img;
}


SDL_Renderer* Graphics::getRenderer() {
	return renderer;
}
