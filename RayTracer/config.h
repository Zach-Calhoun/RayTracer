#pragma once

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

enum RenderModes { NO_LIGHT = 1, DIFFUSE = 2, SPECULAR = 4, SHADOWS = 8, REFLECTIONS = 16 };

#define V_FOV 90
//#define H_FOV 120
#define H_FOV 90
#define AMBIENT_LEVEL 0.05

#define MAX_BOUNCE 16
