#pragma once
#include "Scene.h"
#include "Primitives.h"
#include "Camera.h"
#include <Windows.h>

struct RenderDivisionParam {
	Renderer* instance;
	int horizontalDivs;
	int verticalDivs;
	int maxThreads;
};
struct RenderRegionParam {
	//Scene* scenePtr;
	Renderer* instance;
	int sy, sx, ey, ex;
};


class Renderer
{
private:
	int h, w;
	int renderMode;
	void RenderFull();
	void RenderPart(int topY, int topX, int botY, int botX);

	HANDLE mainRenderThreadHandle;

	static DWORD WINAPI renderPartThreadHandle(LPVOID param);
	static DWORD WINAPI setupRenderThreadsHandle(LPVOID param);
	DWORD renderPartThread(LPVOID param);
	DWORD setupRenderThreads(LPVOID param);
	
public:
	Scene* scene;
	Camera* camera;

	Renderer();
	Renderer(Scene& scene);
	~Renderer();

	void SetCamera(Camera& camera);
	void SetScene(Scene& scene);
	void SetRenderMode(int mode);

	void RenderSingleThread();
	void RenderMultiThread(int horDivs, int verDivs, int maxThreads = 4);

	bool DoneRendering();

	
	


	/*void Render(Scene& scene, int frame);
	bool SavePpm(char * path);
	bool SavePpm(char * path, int frame);*/

};
