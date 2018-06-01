#include "Scene.h"

Scene::Scene()
{

}

void Scene::InitDefault()
{
	//camera.pos = Vector(0, 5, -2);
	//camera.rot.x = ((double)45 / 180) * 3.14;
	//camera.Setup(SCREEN_HEIGHT, SCREEN_WIDTH, V_FOV, H_FOV);
	//

	//objects.push_back(new Plane(Vector(0, 1, 0), 1, Vector(1, 1, 0)));
	//objects.push_back(new Plane(Vector(1, 0, 0), 7, Vector(1, 0, 0)));
	////objects.push_back(new Sphere(Vector(-200, 0, 200), 50, Vector(1, 0, 0)));
	//objects.push_back(new Sphere(Vector(0, 1, 3), 1, Vector(0, 0, 1)));
	//objects.push_back(new Sphere(Vector(-2, 2, 3.5), 0.5, Vector(0.5, 0.5, 1)));
	////objects.push_back(new Sphere(Vector(200, 150, 300), 10, Vector(0, 1, 1)));
	////objects.push_back(new Sphere(Vector(-100, -70, 180), 10, Vector(0, 1,0)));
	////objects.push_back(new Plane(Vector(1, 1, 0), 900, Vector(1, 0, 0)));

	//PointLight light = PointLight(Vector(1, 4, 1), Vector(1, 1, 1), 50);
	//lights.push_back(light);

	camera.pos = Vector(0, 0, -2);
	camera.Setup(SCREEN_HEIGHT, SCREEN_WIDTH, V_FOV, H_FOV);
	objects.push_back(new Plane(Vector(0, 1, 0), 1, Vector(1, 1, 0)));
	objects.push_back(new Sphere(Vector(0, 0, 2), 1, Vector(0, 0, 1)));
	PointLight light = PointLight(Vector(0, 0, 4), Vector(1, 1, 1), 50);
	lights.push_back(light);
}

bool Scene::Load(char * path)
{
	return false;
}

void Scene::Render()
{
	camera.Render(*this);
}

void Scene::RenderPart(int topY, int topX, int botY, int botX)
{
	camera.RenderPart(*this, topY, topX, botY, botX);
}
bool Scene::SaveToPpm(char * path)
{
	return camera.SavePpm(path);
}

bool Scene::SaveToPpm(char * path, int frame)
{
	return camera.SavePpm(path, frame);
}

void Scene::Update()
{
	//camera.pos = camera.pos + camera.transform * Vector(0, 0, -0.1);
	camera.pos = camera.pos + Vector(0, 0, -0.5);
}

Scene::~Scene()
{
	objects.clear();
	lights.clear();
}

