#include "SDL_Renderer.h"
#include "config.h"
#include <iostream>

SDLCameraRenderer::SDLCameraRenderer()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	}
	Window = SDL_CreateWindow("Ray Tracer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	Screen = SDL_GetWindowSurface(Window);
}

SDLCameraRenderer::SDLCameraRenderer(Camera& camera)
{
	cameraReference = &camera;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	}
	Window = SDL_CreateWindow("Ray Tracer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, camera.screenWidth, camera.screenHeight, SDL_WINDOW_SHOWN);
	Screen = SDL_GetWindowSurface(Window);
}

void SDLCameraRenderer::DrawCameraBuffer()
{
	for (int i = 0; i < cameraReference->screenHeight; i++)
	{
		for (int j = 0; j < cameraReference->screenWidth; j++)
		{
			putpixel(i, j, cameraReference->buffer[i][j]);
		}
	}
	SDL_UpdateWindowSurface(Window);
}

SDLCameraRenderer::~SDLCameraRenderer()
{
	SDL_FreeSurface(Screen);
	SDL_DestroyWindow(Window);
	SDL_Quit();
}

void SDLCameraRenderer::putpixel(int y, int x, Vector color)
{
	if (y < 0 || y > cameraReference->screenHeight || x < 0 || x > cameraReference->screenWidth)
		return;

	int bytesPerPixel = Screen->format->BytesPerPixel;
	uint32_t pixel = color.r() << 16;
	pixel |= color.g() << 8;
	pixel |= color.b();

	Uint8 *p = (Uint8 *)Screen->pixels + y * Screen->pitch + x * bytesPerPixel;

	switch (bytesPerPixel) {
	case 1:
		*p = pixel;
		break;

	case 2:
		*(Uint16 *)p = pixel;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
			p[0] = (pixel >> 16) & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = pixel & 0xff;
		}
		else {
			p[0] = pixel & 0xff;
			p[1] = (pixel >> 8) & 0xff;
			p[2] = (pixel >> 16) & 0xff;
		}
		break;

	case 4:
		*(Uint32 *)p = pixel;
		break;
	}
}