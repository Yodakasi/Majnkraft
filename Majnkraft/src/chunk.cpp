#include "chunk.h"


Chunk::Chunk() {
    //gen = new noise::module::Perlin();
    for (int i = 0; i < 128; i++) {
        blocks[i] = new Block();
    }
}

Chunk::~Chunk() {
    for (int i = 0; i < 128; i++) {
        delete blocks[i];
    }

}
void Chunk::generateChunk(Noise &noisy) {
    int index = 0;
        for (double j = 0; j < 4; j++) {
            for (double g = 0; g < 4; g++) { 
                double wtf = noisy.noiseFun((double)position.x + j, (double)position.z + g);
                double height = -round(wtf * 64);

                glm::vec3 pos = glm::vec3(position.x + j, height, position.z + g);
                int sides = 1;
                
                double heightBeforeY = -round(noisy.noiseFun((double)position.x + j, (double)position.z + g - 1) * 64);
                if (heightBeforeY < height) {
                    sides += 2;
                }
                if (height - heightBeforeY > 1) {
                    for (int i = 0; i < height - heightBeforeY; i++) {
                        blocks[index]->initBlock(blockstab[0].top, blockstab[0].side1, blockstab[0].side2, blockstab[0].bot, glm::vec3(pos.x, pos.y-i-1, pos.z), 2);
                        index++;
                    }
                }
                double heightAfterY = -round(noisy.noiseFun((double)position.x + j, (double)position.z + g + 1) * 64);
                if (heightAfterY < height) {
                    sides += 4;
                }
                if (height - heightAfterY > 1) {
                    for (int i = 0; i < height - heightAfterY; i++) {
                        blocks[index]->initBlock(blockstab[1].top, blockstab[1].side1, blockstab[1].side2, blockstab[1].bot, glm::vec3(pos.x, pos.y - i - 1, pos.z), 4);
                        index++;
                    }
                }
                
                double heightBeforeX = -round(noisy.noiseFun((double)position.x + j - 1, (double)position.z + g) * 64);
                if (heightBeforeX < height) {
                    sides += 8;
                }
                if (height - heightBeforeX > 1) {
                    for (int i = 0; i < height - heightBeforeX; i++) {
                        blocks[index]->initBlock(blockstab[1].top, blockstab[1].side1, blockstab[1].side2, blockstab[1].bot, glm::vec3(pos.x, pos.y - i - 1, pos.z), 8);
                        index++;
                    }
                }
                double heightAfterX = -round(noisy.noiseFun((double)position.x + j + 1, (double)position.z + g) * 64);
                if (heightAfterX < height) {
                    sides += 16;
                }
                if (height - heightAfterX > 1) {
                    for (int i = 0; i < height - heightAfterX; i++) {
                        blocks[index]->initBlock(blockstab[1].top, blockstab[1].side1, blockstab[1].side2, blockstab[1].bot, glm::vec3(pos.x, pos.y - i - 1, pos.z), 16);
                        index++;
                    }
                }
                
                 blocks[index]->initBlock(blockstab[0].top, blockstab[0].side1, blockstab[0].side2, blockstab[0].bot, pos, sides);
              
                
                index++;
            }
        }
        visibleBlocks = index;
    //}
}

void Chunk::initChunk(blockStruct *blockss, glm::vec3 pos) {
    for (int i = 0; i < 5; i++) {
        blockstab[i].top = blockss[i].top;
        blockstab[i].side1 = blockss[i].side1;
        blockstab[i].side2 = blockss[i].side2;
        blockstab[i].bot = blockss[i].bot;
    }
    
    position = pos;
}


void Chunk::drawChunk(Shader& shader) {
    //std::cout << visibleBlocks << std::endl;
    for (int i = 0; i < visibleBlocks; i++) {
        blocks[i]->drawBlock(shader);
    }
}







