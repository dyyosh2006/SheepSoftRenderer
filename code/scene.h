#pragma once
#include "./tgaimage.h"
#include "shader.h"

typedef struct
{
	const char* scene_name;
	void (*build_scene)(Model** model, int& m, IShader** shader_use, IShader** shader_skybox, mat4 perspective, Camera* camera);
} scene_t;

TGAImage* texture_from_file(const char* file_name);
void load_ibl_map(payload_t& p, const char* env_path);
void build_pbr_scene(IShader* shader_use,Model* model, mat4 perspective, Camera* camera);