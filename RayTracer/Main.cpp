// RayCaster.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "config.h"
#include "Primitives.h"

int main()
{
	Sphere sp = Sphere(Vector(0, 0, 100), 10);

	for (int i = 0; i < SCREEN_HEIGHT;i++)
	{
		for (int j = 0; j < SCREEN_WIDTH; j++)
		{
			Ray r = Ray(); //defaults to world origin and forward direction ( +z )

		}
	}

    return 0;
}

