#pragma once
//
//#define SCREEN_WIDTH 1280
//#define SCREEN_HEIGHT 780
#define SCREEN_WIDTH 427
#define SCREEN_HEIGHT 260
#define MAX_REFLECTION_DEPTH 4

enum RenderModes { SHADELESS = 1, DIFFUSE = 2, SPECULAR = 4, SHADOWS = 8, REFLECTIONS = 16 };

#define V_FOV 90
//#define H_FOV 120
#define H_FOV 120
#define AMBIENT_LEVEL 0.05

#define MAX_BOUNCE 16
