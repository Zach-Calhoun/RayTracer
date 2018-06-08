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
	//Mesh* suzanneMesh = new Mesh("suzanne.txt");
	cubeMesh->InitCube();
	OpaqueTiles* tileMaterial = new OpaqueTiles(1, 1, Vector(1, 1, 1), Vector(0, 0, 0), 1);
	MeshObject* Cube = new MeshObject(*cubeMesh, new Material(Vector(0.5, 0.5, 0.5), Vector(1, 1, 1), 0.5));
	MeshObject* Cube2 = new MeshObject(*cubeMesh, tileMaterial);
	//MeshObject* Suzanne = new MeshObject(*suzanneMesh, new Material(Vector(1, 0.2, 0.2), Vector(0, 0, 0), 1));
	//Suzanne->SetRot(0, M_PI, 0);
	//Suzanne->SetPos(0, 1, 0);
	Cube->SetPos(3, 0, 3);
	Cube2->SetPos(-3, 0, 3);
	//Cube2->SetRot(M_PI / 4, M_PI / 4, M_PI / 4);
	Cube2->SetRot(M_PI / 4, M_PI / 4, M_PI / 4);
	animated = Cube2;


	camera.pos = Vector(0, 2, -2);
	camera.rot = Vector(M_PI/8, 0 , 0);
	camera.Setup(SCREEN_HEIGHT, SCREEN_WIDTH, V_FOV, H_FOV);
	objects.push_back(new Plane(Vector(0, 1, 0), 1, tileMaterial));
	objects.push_back(new Plane(Vector(1, 0, 0), 5, new Material(Vector(1,1,1), Vector(1,1,1), 0.1)));
	objects.push_back(new Sphere(Vector(0, 0, 2), 1, new Material(Vector(0.2, 0.2, 1), Vector(1,1,1), 0)));
	objects.push_back(new Sphere(Vector(0, 0, -2), 1, Vector(1, .2, .2)));
	objects.push_back(new Sphere(Vector(2, 0, 0), 1, Vector(.2, 1, .2)));
	objects.push_back(new Sphere(Vector(-2, 0, 0), 1, Vector(.05, .05, 1)));
	//objects.push_back(Suzanne);
	objects.push_back(Cube);
	objects.push_back(Cube2);
	//objects.push_back(Triangle);
	PointLight light = PointLight(Vector(-4, 4, 4), Vector(1, 1, 1), 50);
	//lights.push_back(light);
	lights.push_back(PointLight(Vector(2, 4, -2), Vector(1,1, 1), 50));
}

void Scene::InitAnimScene()
{
	OpaqueTiles* tileMaterial = new OpaqueTiles(1, 1, Vector(1, 1, 1), Vector(0, 0, 0), 1);
	camera.pos = Vector(0, 0, -6);
	//camera.rot = Vector(M_PI / 8, 0, 0);
	objects.push_back(new Plane(Vector(0, 0, -1), 5, tileMaterial));
	objects.push_back(new Sphere(Vector(0, 0, 0), 2, new Material(Vector(0.2, 0.2, 1), Vector(1, 1, 1), 0.3)));
	objects.push_back(new Sphere(Vector(0, 4, 0), 1, new Material(Vector(0.2, 0.2, 1), Vector(1, 1, 1), 0.3)));
	objects.push_back(new Sphere(Vector(0, -4, 0), 1, new Material(Vector(0.2, 0.2, 1), Vector(1, 1, 1), 0.3)));
	objects.push_back(new Sphere(Vector(-4, 0, 0), 1, new Material(Vector(0.2, 0.2, 1), Vector(1, 1, 1), 0.3)));
	objects.push_back(new Sphere(Vector(4, 0, 0), 1, new Material(Vector(0.2, 0.2, 1), Vector(1, 1, 1), 0.3)));
	objects.push_back(new Sphere(Vector(3, 3, 0), 1, new Material(Vector(0.2, 0.2, 1), Vector(1, 1, 1), 0.3)));
	objects.push_back(new Sphere(Vector(3, -3, 0), 1, new Material(Vector(0.2, 0.2, 1), Vector(1, 1, 1), 0.3)));
	objects.push_back(new Sphere(Vector(-3, 3, 0), 1, new Material(Vector(0.2, 0.2, 1), Vector(1, 1, 1), 0.3)));
	objects.push_back(new Sphere(Vector(-3, -3, 0), 1, new Material(Vector(0.2, 0.2, 1), Vector(1, 1, 1), 0.3)));

	PointLight light = PointLight(Vector(4, 4, -8), Vector(1, 1, 1), 100);
	//lights.push_back(light);
	lights.push_back(light);
}

bool Scene::Load(char * path)
{
	return false;
}


void Scene::Update()
{
	Matrix mat = Matrix::RotationZ(M_PI / 24);
	for (int i = 1; i < objects.size(); i++)
	{
		Vector p = objects[i]->GetPos();
		Matrix pMat = p.AsPosition();
		Matrix res = mat * pMat;
		Vector newP = res.AsVector();
		pMat.Release();
		res.Release();
		objects[i]->SetPos(newP);
	}
}

Scene::~Scene()
{
	objects.clear();
	lights.clear();
}

