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

struct RenderRect {
	Scene* scenePtr;
	int sy, sx, ey, ex;
};


DWORD WINAPI renderPart(LPVOID lpParam)
{
	RenderRect *rect = (RenderRect*)lpParam;
	rect->scenePtr->RenderPart(rect->sy, rect->sx, rect->ey, rect->ex);
	return 0;
}

DWORD WINAPI render(LPVOID lpParam)
{
	Scene *scene = (Scene*)lpParam;
	//prepare 4 threads for rendering
	int h = scene->camera.getHeight();
	int w = scene->camera.getWidth();

	RenderRect reg1 = { scene, 0,0, h / 2, w / 2 };
	RenderRect reg2 = { scene, 0, w / 2, h / 2, w };
	RenderRect reg3 = { scene, h / 2, 0, h, w / 2 };
	RenderRect reg4 = { scene, h / 2, w / 2, h, w };

	for (int frame = 0; frame < 10; frame++)
	{
		//scene->Render();
		//renderer.DrawCameraBuffer();
		std::vector<HANDLE> handles;
	
		HANDLE hdl = CreateThread(NULL, 0, renderPart, &reg1, 0, 0);
		handles.push_back(hdl);
		hdl = CreateThread(NULL, 0, renderPart, &reg2, 0, 0);
		handles.push_back(hdl);
		hdl = CreateThread(NULL, 0, renderPart, &reg3, 0, 0);
		handles.push_back(hdl);
		hdl = CreateThread(NULL, 0, renderPart, &reg4, 0, 0);
		handles.push_back(hdl);
		WaitForMultipleObjects(4, handles.data(), true, INFINITE);

		scene->Update();
		scene->SaveToPpm("movtest", frame);

	}
	return 0;
}




int main(int argc, char *args[])
{
	Scene defaultScene;
	defaultScene.InitDefault();
	SDLCameraRenderer renderer = SDLCameraRenderer(defaultScene.camera);
	std::getc(stdin);
	HANDLE hdl = CreateThread(NULL, 0, render, &defaultScene, 0, 0);

	while (true)
	{
		DWORD res = WaitForSingleObject(hdl, 0);
		renderer.DrawCameraBuffer();
		if (res == WAIT_OBJECT_0)
		{
			break;
		}
	}
	/*for (int frame = 0; frame < 1; frame++)
	{
		defaultScene.Render();
		renderer.DrawCameraBuffer();
		defaultScene.Update();
		defaultScene.SaveToPpm("movtest",frame);
		
	}*/
	
	

    return 0;
}

