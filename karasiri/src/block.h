#pragma once
#ifndef BLOCK_H
#define BLOCK_H
#include  "SDL2/SDL.h"
#include "graphics.h"
//struct SDL_Texture;
struct SDL_Surface;
class Block {
public:
	Block();
	virtual ~Block();
	virtual float getX();
	virtual float getY();
	virtual float getWidth();
	virtual float getHeight();

	virtual void setX(float newX);
	virtual void setY(float newY);

	virtual void loadImage(Graphics& graphics, const std::string path);
	virtual SDL_Texture* getTexture();
	virtual void update(float time, Graphics& graphics) = 0;
	virtual void draw(Graphics& graphics);
	virtual void setTexture(SDL_Texture* newTexture);
protected:
	float x, y, width, height;
	SDL_Texture* texture;
	SDL_Surface* surface;

};


#endif // BLOCK_H
