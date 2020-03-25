#include "generate.h"

bool Generate::loadTexture(std::string path, unsigned int* ptr, unsigned int index) {
    if (index != 2)
        stbi_set_flip_vertically_on_load(true);
    else
        stbi_set_flip_vertically_on_load(false);
    glGenTextures(index, ptr);
    glBindTexture(GL_TEXTURE_2D, *ptr);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
        return false;
    }
    stbi_image_free(data);
    return true;
}


Generate::Generate() {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            chunks[i][j] = new Chunk();
        }
    }
    loadTexture("res/textures/grass_top.jpg", &blockstab[0].top, 0);
    loadTexture("res/textures/grass_side.jpg", &blockstab[0].side1, 1);
    loadTexture("res/textures/grass_side.jpg", &blockstab[0].side2, 2);
    loadTexture("res/textures/grass_bot.jpg", &blockstab[0].bot, 3);

    loadTexture("res/textures/grass_bot.jpg", &blockstab[1].top, 4);
    loadTexture("res/textures/grass_bot.jpg", &blockstab[1].side1, 5);
    loadTexture("res/textures/grass_bot.jpg", &blockstab[1].side2, 6);
    loadTexture("res/textures/grass_bot.jpg", &blockstab[1].bot, 7);
}

Generate::~Generate() {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            delete chunks[i][j];
        }
    }
}

void Generate::generateWorld() {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            chunks[i][j]->initChunk(blockstab, glm::vec3(0.0f+(i*4), 0.0f, 0.0f+(j*4)));
            chunks[i][j]->generateChunk();
        }
    }
}

void Generate::drawWorld(Shader& shader) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            chunks[i][j]->drawChunk(shader);
        }
    }
}

