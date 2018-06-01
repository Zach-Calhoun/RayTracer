#pragma once
#include "Primitives.h"
#include "Light.h"
#include <vector>
#include "config.h"
class Scene
{
public:
	Camera camera;
	std::vector<RayTraceable*> objects;
	std::vector<PointLight> lights;
	//

	Scene();
	~Scene();
	void InitDefault();
	bool Load(char * path);
	void Render();
	void RenderPart(int topY, int topX, int botY, int botX);
	//void Render(int frame);
	void Update();
	bool SaveToPpm(char * path);
	bool SaveToPpm(char *, int frame);
};