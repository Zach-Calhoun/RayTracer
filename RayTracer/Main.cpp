// RayCaster.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "config.h"
#include "Primitives.h"
#include "Light.h"
#include <fstream>
#include <vector>
#include "Scene.h"
int main()
{
	Scene defaultScene;
	defaultScene.InitDefault();
	defaultScene.Render();
	defaultScene.SaveToPpm("result1.ppm");

	

    return 0;
}

