#include <ctime>
#include <iostream>

#include "windows.h"
#include "camera.h"
#include "shader.h"
#include "scene.h"
#include "pipeline.h"
#include "macro.h"
#include "tgaimage.h"
#include "model.h"

const vec3 Eye(1.5,0,-1.5);
const vec3 Up(0, 1, 0);
const vec3 Target(0, -0.1, 0);

const int  width = 800;
const int height = 600;

void ResetZBuffer(int width, int height, float* zbuffer)
{
	for (int i = 0; i < width * height; i++)
		zbuffer[i] = 100000;
}

void ResetFrameBuffer(int width, int height, unsigned char* framebuffer)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int index = (i * width + j) * 4;

			framebuffer[index] = 50;
			framebuffer[index + 1] = 50;
			framebuffer[index + 2] = 50;
		}
	}
}

mat4 M;
mat4 V;
mat4 P;
mat4 MVP;
void UpdateMatrix(PBRShader* shad,Camera & cam)
{
	M = mat4::identity();
	V = mat4_lookat(cam.eye, cam.target, cam.up);
	P = mat4_perspective(60, (float)(width) / height, -0.1, -10000);
	MVP = P * V * M;
	shad->payload.mvp_matrix = MVP;
}

int main()
{
	//set memory for zbuffer and frame buffer
	//zbuffer float frame buffer(0-255,rgba)
	float* zbuffer = (float*)malloc(sizeof(float) * width * height);
	unsigned char* framebuffer = (unsigned char*)malloc(sizeof(unsigned char) * width * height * 4);

	//camera
	Camera myCam(Eye, Target, Up, (float)(width) / height);



	///
	Model* mod;
	PBRShader* shader_pbr = new PBRShader();
	int vertex = 0, face = 0;
	mod = new Model("obj/helmet/helmet.obj", 0, 0);
	vertex += mod->nverts();
	face += mod->nfaces();
	shader_pbr->payload.model = mod;
	shader_pbr->payload.camera = &myCam;
	load_ibl_map(shader_pbr->payload, "obj/ibl");
	

	window_init(width, height);
	while (!window->is_close)
	{
		ResetZBuffer(width, height, zbuffer);
		ResetFrameBuffer(width, height, framebuffer);

		//update cam and cam matrix
		handle_events(myCam);
		UpdateMatrix(shader_pbr,myCam);

		for (int i = 0; i < shader_pbr->payload.model->nfaces(); i++)
		{
			draw_triangles(framebuffer, zbuffer, *shader_pbr, i);
		}

		// reset mouse information
		window->mouse_info.wheel_delta = 0;
		window->mouse_info.orbit_delta = vec2(0, 0);
		window->mouse_info.fv_delta = vec2(0, 0);

		window_draw(framebuffer);
		msg_dispatch();

	}

	return 0;
	
}

