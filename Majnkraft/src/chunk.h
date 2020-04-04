#pragma once


#include "noise.h"
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
	Block *blocks[128];
	unsigned int visibleBlocks;
	
	
public:
	Chunk();
	~Chunk();
	void generateChunk(Noise &noisy);
	void initChunk(blockStruct *blockss, glm::vec3 pos);
	void drawChunk(Shader& shader);
	


};