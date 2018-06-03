// RayCaster.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "config.h"
#include "Primitives.h"
#include "Light.h"
#include <fstream>
#include <vector>
#include "Scene.h"
#include "SDL_Renderer.h"
#include <vector>
#include <Windows.h>
#include <SDL.h>
#include "Renderer.h"

#define NUM_THREADS 1
int main(int argc, char *args[])
{
	Scene defaultScene;
	defaultScene.InitDefault();
	SDLCameraRenderer sdlPreview(defaultScene.camera);// = SDLCameraRenderer(defaultScene.camera);
	Renderer renderer(defaultScene);// = Renderer(defaultScene);
	renderer.RenderMultiThread(8, 8, NUM_THREADS);
	renderer.SetRenderMode(SHADELESS | DIFFUSE | SHADOWS);
	SDL_Event event;
	bool KeepRunning = true;
	bool SomethingHappened = false;
	while (KeepRunning)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
					{
						KeepRunning = false;
						break;
					}
					case SDLK_w:
					{
						SomethingHappened = true;
						defaultScene.camera.pos += defaultScene.camera.transform * Vector(0, 0, 0.5);
						break;
					}
					case SDLK_s:
					{
						SomethingHappened = true;
						defaultScene.camera.pos += defaultScene.camera.transform * Vector(0, 0, -0.5);
						break;
					}
					case SDLK_d:
					{
						SomethingHappened = true;
						defaultScene.camera.pos += defaultScene.camera.transform * Vector(0.5 , 0, 0);
						break;
					}
					case SDLK_a:
					{
						SomethingHappened = true;
						defaultScene.camera.pos += defaultScene.camera.transform * Vector(-0.5, 0, 0);
						break;
					}
					case SDLK_r:
					{
						SomethingHappened = true;
						//defaultScene.camera.pos += defaultScene.camera.transform * Vector(0, 0.5, 0);
						defaultScene.camera.pos +=  Vector(0, 0.5, 0);
						break;
					}
					case SDLK_f:
					{
						SomethingHappened = true;
						//defaultScene.camera.pos += defaultScene.camera.transform * Vector(0, -0.5, 0);
						defaultScene.camera.pos += Vector(0, -0.5, 0);
						break;
					}

					case SDLK_UP:
					{
						SomethingHappened = true;
						Vector rot = defaultScene.camera.rot;
						rot.x += -5.0 / 180 * M_PI;
						defaultScene.camera.SetRotation(rot);
						break;
					}
					case SDLK_DOWN:
					{
						SomethingHappened = true;
						Vector rot = defaultScene.camera.rot;
						rot.x += +5.0 / 180 * M_PI;
						defaultScene.camera.SetRotation(rot);
						break;
					}
					case SDLK_LEFT:
					{
						SomethingHappened = true;
						Vector rot = defaultScene.camera.rot;
						rot.y += -5.0 / 180 * M_PI;
						defaultScene.camera.SetRotation(rot);
						break;
					}
					case SDLK_RIGHT:
					{
						SomethingHappened = true;
						Vector rot = defaultScene.camera.rot;
						rot.y += +5.0 / 180 * M_PI;
						defaultScene.camera.SetRotation(rot);
						break;
					}

				}
			}
		}

		if (SomethingHappened && renderer.DoneRendering())
		{
			//trigger frame update only if something change and not currently rendering
			renderer.RenderMultiThread(8, 8, NUM_THREADS);
			SomethingHappened = false;
		}

		sdlPreview.DrawCameraBuffer();

	}
	//wait for renderer to complete;

	while (!renderer.DoneRendering())
	{
		sdlPreview.DrawCameraBuffer();
	}

	return 0;
}

