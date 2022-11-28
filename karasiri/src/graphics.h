#pragma once
#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <string>
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
/** Graphics class
 * Holds all information about graphics in the game
 */
class Graphics {
public: 
	Graphics();
	~Graphics();
	/* SDL_Renderer* getRenderer
	 * Returns the renderer
	 */
	SDL_Renderer* getRenderer();

	SDL_Surface* addImage(const std::string &image);

private:
	SDL_Window* window;
	SDL_Renderer* renderer;

};

#endif // GRAPHICS_H