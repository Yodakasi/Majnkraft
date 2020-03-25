#pragma once

#include "block.h"

struct blockStruct {
	unsigned int top;
	unsigned int side1;
	unsigned int side2;
	unsigned int bot;
};

class Chunk {
	blockStruct blockstab[5];
	glm::vec3 position;
	Block *blocks[256];
public:
	Chunk();
	~Chunk();
	void generateChunk();
	void initChunk(blockStruct blockss[5], glm::vec3 pos);
	void drawChunk(Shader& shader);

};