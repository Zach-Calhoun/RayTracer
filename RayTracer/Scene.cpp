#include "Scene.h"
#define _USE_MATH_DEFINES 1
#include <math.h>

Scene::Scene()
{

}

void Scene::InitDefault()
{


	//TODO add factories

	Mesh* cubeMesh = new Mesh();
	cubeMesh->InitCube();
	MeshObject* Cube = new MeshObject(*cubeMesh, Material(Vector(0.5, 0.5, 1), Vector(1, 1, 1), 0.1));
	MeshObject* Cube2 = new MeshObject(*cubeMesh);
	Cube->SetPos(3, 0, 3);
	Cube2->SetPos(-3, 0, 3);
	//Cube2->SetRot(M_PI / 4, M_PI / 4, M_PI / 4);
	Cube2->SetRot(M_PI / 4, M_PI / 4, M_PI / 4);
	animated = Cube2;


	camera.pos = Vector(0, 5, 0);
	camera.rot = Vector(M_PI / 2, 0 , 0);
	camera.Setup(SCREEN_HEIGHT, SCREEN_WIDTH, V_FOV, H_FOV);
	objects.push_back(new Plane(Vector(0, 1, 0), 1, Material(Vector(1,1,0.01))));
	objects.push_back(new Sphere(Vector(0, 0, 2), 1, Material(Vector(0.2, 0.2, 1), Vector(1,1,1), 0)));
	objects.push_back(new Sphere(Vector(0, 0, -2), 1, Vector(1, .2, .2)));
	objects.push_back(new Sphere(Vector(2, 0, 0), 1, Vector(.2, 1, .2)));
	objects.push_back(new Sphere(Vector(-2, 0, 0), 1, Vector(.05, .05, 1)));
	objects.push_back(Cube);
	objects.push_back(Cube2);
	//objects.push_back(Triangle);
	PointLight light = PointLight(Vector(-4, 4, 4), Vector(1, 1, 1), 50);
	lights.push_back(light);
	lights.push_back(PointLight(Vector(2, 4, -2), Vector(1, 0.3, 0.3), 50));
}

bool Scene::Load(char * path)
{
	return false;
}


void Scene::Update()
{
	auto r = animated->GetRot();
	animated->SetRot(r + Vector(0.1, 0.1, 0.1));
	//camera.pos = camera.pos + camera.transform * Vector(0, 0, -0.1);
	//camera.pos = camera.pos + Vector(0, 0, -0.5);
}

Scene::~Scene()
{
	objects.clear();
	lights.clear();
}

