#pragma once
#include <GL/glew.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unordered_map> 
#include <memory>



#include "stb_image.h"
#include "shader.h"
#include "chunk.h"


struct hash {

	// Use sum of lengths of first and last names 
	// as hash function. 
	std::size_t operator()(const glm::vec2& k) const
	{
		std::size_t res = 17;
		res = res * 31 + (int)k.x;
		res = res * 31 + (int)k.y;
		//std::cout << res << " " << (int)k.x << " " << (int)k.y << std::endl;
		return res;

	}
};



class Generate {
	blockStruct blockstab[5];

	bool loadTexture(std::string path, unsigned int* ptr, unsigned int index);
	std::unordered_map<glm::vec2, std::shared_ptr<Chunk>, hash> umap;
	int renderDistance;
	bool needToGen;

public:
	Generate();
	~Generate();
	void init(int redDis);
	void generateWorld(glm::vec2 start, Noise &noisy);
	void drawWorld(Shader& shader, glm::vec2 pos);
	
	
};