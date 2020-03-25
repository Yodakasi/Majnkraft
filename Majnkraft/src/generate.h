#pragma once
#include <GL/glew.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"
#include "shader.h"
#include "chunk.h"



class Generate {
	blockStruct blockstab[5];

	bool loadTexture(std::string path, unsigned int* ptr, unsigned int index);
	Chunk *chunks[16][16];

public:
	Generate();
	~Generate();
	void generateWorld();
	void drawWorld(Shader& shader);
};