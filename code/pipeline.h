#pragma once
#include "./macro.h"
#include "./maths.h"

#include "shader.h"
#include "windows.h"

const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 800;

void draw_triangles(unsigned char* framebuffer, float* zbuffer, IShader & shader, int nface);
