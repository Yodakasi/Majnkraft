#include "chunk.h"


Chunk::Chunk() {
    for (int i = 0; i < 256; i++) {
        blocks[i] = new Block();
    }
}

Chunk::~Chunk() {
    for (int i = 0; i < 256; i++) {
        delete blocks[i];
    }

}
void Chunk::generateChunk() {
    int index = 0;
    for (float i = 0; i < 16; i++) {
        for (float j = 0; j < 4; j++) {
            for (float g = 0; g < 4; g++) {
                glm::vec3 pos = glm::vec3(position.x + j, position.y - i, position.z + g);
                //std::cout << pos.x << std::endl;
                if (i == 0) {
                    blocks[index]->initBlock(blockstab[0].top, blockstab[0].side1, blockstab[0].side2, blockstab[0].bot, pos, 1);
                }
                else {
                    blocks[index]->initBlock(blockstab[1].top, blockstab[1].side1, blockstab[1].side2, blockstab[1].bot, pos, 0);
                }
                //std::cout << index << std::endl;
                index++;
            }
        }
    }
}

void Chunk::initChunk(blockStruct blockss[5], glm::vec3 pos) {
    for (int i = 0; i < 5; i++) {
        blockstab[i] = blockss[i];
    }
    
    position = pos;
}


void Chunk::drawChunk(Shader& shader) {
    for (int i = 0; i < 256; i++) {
        blocks[i]->drawBlock(shader);
    }
}