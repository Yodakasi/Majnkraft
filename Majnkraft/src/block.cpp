#include "block.h"



void Block::initBlock(unsigned int top, unsigned int side1, unsigned int side2, unsigned int bot, glm::vec3 pos, unsigned int sides) {
    block.top = top;
    block.side1 = side1;
    block.side2 = side2;
    block.bot = bot;
    position = pos;
    whichSides = sides;
   
}

void Block::drawBlock(Shader& shader) {
    
    glm::mat4 model = glm::mat4(1.0f); 
    model = glm::translate(model, position);
    shader.setMat4("model", model);
    shader.use();
    if (whichSides & 1) {
        glBindTexture(GL_TEXTURE_2D, block.top);
        glDrawArrays(GL_TRIANGLES, 30, 6);
    }
    if (whichSides & 2) {
        glBindTexture(GL_TEXTURE_2D, block.side1);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    if (whichSides & 4) {
        glBindTexture(GL_TEXTURE_2D, block.side1);
        glDrawArrays(GL_TRIANGLES, 6, 6);
    }
    if (whichSides & 8) {
        glBindTexture(GL_TEXTURE_2D, block.side2);
        glDrawArrays(GL_TRIANGLES, 12, 6);
    }
    if (whichSides & 16) {
        glBindTexture(GL_TEXTURE_2D, block.side2);
        glDrawArrays(GL_TRIANGLES, 18, 6);
    }
    if (whichSides & 32) {
        glBindTexture(GL_TEXTURE_2D, block.bot);
        glDrawArrays(GL_TRIANGLES, 24, 6);
    }
    
}


