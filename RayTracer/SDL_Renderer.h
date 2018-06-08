#pragma once
#include <SDL.h>
#include "Vector.h"
#include "Camera.h"
class SDLCameraRenderer
{
private:
	void putpixel(int y, int x, Vector color);
public:
	SDL_Window *Window;
	SDL_Surface * Screen;
	//SDL_Event event;
	Camera* cameraReference;

	void DrawCameraBuffer();
	//bool 

	SDLCameraRenderer();
	SDLCameraRenderer(Camera& camera);
	~SDLCameraRenderer();

};