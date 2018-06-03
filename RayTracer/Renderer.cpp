#include "Renderer.h"
#include "Shader.h"
#include <queue>
Renderer::Renderer()
{
	curFrame = 0;
	horizontalDivisions = 1;
	verticalDivisions = 1;
	numThreads = 1;
}

void Renderer::Config(int horDivs, int verDivs, int maxThreads)
{
	horizontalDivisions = horDivs;
	verticalDivisions = verDivs;
	numThreads = maxThreads;
}

Renderer::Renderer(Scene& scene)
{
	curFrame = 0;
	mainRenderThreadHandle = NULL;
	h = scene.camera.getHeight();
	w = scene.camera.getWidth();
	this->scene = &scene;
	camera = &scene.camera;
}

void Renderer::SetCamera(Camera& camera)
{
	this->camera = &camera;
	h = camera.getHeight();
	w = camera.getWidth();
}

void Renderer::SetScene(Scene& scene)
{
	this->scene = &scene;
	SetCamera(scene.camera);
}

void Renderer::NextFrame()
{
	curFrame++;
	scene->Update();
	RenderMultiThread();

}

void Renderer::SetRenderMode(int renderMode)
{
	this->renderMode = renderMode;
}

void Renderer::RenderFull()
{
	RenderPart(0, 0, h, w);
}

void Renderer::RenderPart(int topY, int topX, int botY, int botX)
{
	for (int i = topY; i < botY; i++)
	{
		for (int j = topX; j < botX; j++)
		{			
			Ray r = camera->GenerateRay(i, j);
			Intersection hit = r.TraceObjects(scene->objects);

			

			if (hit.success)
			{
				if (renderMode & REFLECTIONS)
				{

				}
				int depth = 0;
				Vector pixel = Shader::CalculateShading(hit, r,scene, renderMode, depth);
				
				camera->buffer[i][j] = pixel;			
			}
			else
			{
				camera->buffer[i][j] = Vector(1, 1, 1);
			}
		}
	}
}

void Renderer::RenderSingleThread()
{
	/*RenderDivs divs = { 1,1 };
	HANDLE hdl = CreateThread(NULL, 0, this->setupRenderThreads, &divs, 0, 0);*/
	//setupRenderThreads()
	//RenderFull();
	RenderMultiThread(1, 1);
}

void Renderer::RenderMultiThread()
{
	RenderMultiThread(horizontalDivisions, verticalDivisions, numThreads);
}

void Renderer::RenderMultiThread(int horDivs, int verDivs, int maxThreads)
{
	if (mainRenderThreadHandle != NULL)
	{
		std::cout << "WARNING, called RENDER MULTI THREAD while a render cycle was running";
		return;
	}
	RenderDivisionParam* divs = new RenderDivisionParam();
	divs->instance = this;
	divs->horizontalDivs = horDivs;
	divs->verticalDivs = verDivs;
	divs->maxThreads = maxThreads;
	//{ this, horDivs, verDivs, maxThreads};
	mainRenderThreadHandle = CreateThread(NULL, 0, setupRenderThreadsHandle, divs, 0, 0);

	//HANDLE hdl = CreateThread(NULL, 0, this->setupRenderThreads, &divs, 0, 0);
}

bool Renderer::DoneRendering()
{
	if (mainRenderThreadHandle == NULL)
	{
		return true;
	}
	else
	{
		DWORD res = WaitForSingleObject(mainRenderThreadHandle, 0);
		if (res == WAIT_OBJECT_0) {
			mainRenderThreadHandle = NULL;
			return true;
		}
		return false;
	}
}

Renderer::~Renderer()
{

}

DWORD WINAPI Renderer::renderPartThreadHandle(LPVOID param)
{
	RenderRegionParam* rr = (RenderRegionParam*)param;
	Renderer* instance = rr->instance;
	return instance->renderPartThread(param);
	//return &instance->renderPartThread;
}
DWORD WINAPI Renderer::setupRenderThreadsHandle(LPVOID param)
{
	RenderDivisionParam* rd = (RenderDivisionParam*)param;
	Renderer* instance = rd->instance;
	return instance->setupRenderThreads(param);
	//return (DWORD&)instance->setupRenderThreads;
}

DWORD Renderer::setupRenderThreads(LPVOID param)
{
	std::vector<HANDLE> handles;
	std::vector<RenderRegionParam> renderRegions;
	std::queue<RenderRegionParam> renderQueue;
	RenderDivisionParam* divs = (RenderDivisionParam*)param;

	int h = scene->camera.getHeight();
	int w = scene->camera.getWidth();

	int rectH = h / divs->verticalDivs;
	int rectW = w / divs->horizontalDivs;

	int numRegions = divs->verticalDivs * divs->horizontalDivs;

	for (int i = 0; i < divs->verticalDivs; i++)
	{
		for (int j = 0; j < divs->horizontalDivs; j++)
		{
			RenderRegionParam newRect;
			newRect.instance = this;
			newRect.sy = i * rectH;
			newRect.sx = j * rectW;
			newRect.ey = i * rectH + rectH;
			newRect.ex = j * rectW + rectW;
			renderRegions.push_back(newRect);
			renderQueue.push(newRect);
		}
	}
	int paralelThreads = min(divs->maxThreads, numRegions);
	int currentRunningThreads = 0;
	//check handles to not leave render thread until child thread finish
	while (!renderQueue.empty() || handles.size() > 0)
	{
		if (currentRunningThreads < paralelThreads && !renderQueue.empty())
		{
			RenderRegionParam* region = new RenderRegionParam(renderQueue.front());
			renderQueue.pop();
			HANDLE hdl = CreateThread(NULL, 0, renderPartThreadHandle, region, 0, 0);
			handles.push_back(hdl);
			currentRunningThreads++;
		}
		DWORD sync = WaitForMultipleObjects(handles.size(), handles.data(), false, 0);
		if (sync != WAIT_TIMEOUT)
		{
			DWORD index = sync - WAIT_OBJECT_0;
			handles.erase(handles.begin() + index);
			currentRunningThreads--;
		}
	}

	delete divs;
	//scene->camera.SavePpm("testAnim01", curFrame);
	mainRenderThreadHandle = NULL;
	return 0;
}

DWORD Renderer::renderPartThread(LPVOID param)
{
	RenderRegionParam *rect = (RenderRegionParam*)param;
	RenderPart(rect->sy, rect->sx, rect->ey, rect->ex);
	return 0;
}
