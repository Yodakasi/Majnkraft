#pragma once
#include <GL/glew.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "stb_image.h"
#include "shader.h"

class Block {
private:
	unsigned int grassStart = 0;
	struct blockStruct {
		unsigned int top;
		unsigned int side1;
		unsigned int side2;
		unsigned int bot;
	};
	blockStruct block;
	//unsigned int dirtStart = 3;
	glm::vec3 position;
	unsigned int whichSides;
	
	
public:
	Block() {}
	void initBlock(unsigned int top, unsigned int side1, unsigned int side2, unsigned int bot, glm::vec3 pos, unsigned int sides);
	void drawBlock(Shader &shader);
	bool isVisible();


};