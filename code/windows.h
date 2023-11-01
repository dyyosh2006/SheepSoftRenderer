#pragma once
#include <Windows.h>

#include "maths.h"

typedef struct mouse
{
	// for camera orbit
	vec2 orbit_pos;
	vec2 orbit_delta;
	// for first-person view (diabled now)
	vec2 fv_pos;
	vec2 fv_delta;
	// for mouse wheel
	float wheel_delta;
}mouse_t;

typedef struct window
{
	HWND h_window;
	HDC mem_dc;
	HBITMAP bm_old;
	HBITMAP bm_dib;
	unsigned char* window_fb;
	int width;
	int height;
	char keys[512];
	char buttons[2];
	int is_close;
	mouse_t mouse_info;
}window_t;

extern window_t* window;

int window_init(int width, int height);
int window_destroy();
void window_draw(unsigned char* framebuffer);
void msg_dispatch();
vec2 get_mouse_pos();