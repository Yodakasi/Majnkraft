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
    loadTexture("res/textures/grass_top.jpg", &blockstab[0].top, 0);
    loadTexture("res/textures/grass_side.jpg", &blockstab[0].side1, 1);
    loadTexture("res/textures/grass_side.jpg", &blockstab[0].side2, 2);
    loadTexture("res/textures/grass_bot.jpg", &blockstab[0].bot, 3);

    loadTexture("res/textures/grass_bot.jpg", &blockstab[1].top, 4);
    loadTexture("res/textures/grass_bot.jpg", &blockstab[1].side1, 5);
    loadTexture("res/textures/grass_bot.jpg", &blockstab[1].side2, 6);
    loadTexture("res/textures/grass_bot.jpg", &blockstab[1].bot, 7);
    renderDistance = 8;
    needToGen = true;
}

Generate::~Generate() {

}


void Generate::generateWorld(glm::vec2 start) {
    //std::cout << start.x << " " << start.y << std::endl;
    if (needToGen) {
        for (int i = -renderDistance - 16; i <= renderDistance + 16; i++) {
            for (int j = -renderDistance - 16; j <= renderDistance + 16; j++) {
                glm::vec2 ptr = glm::vec2((start.x * 4.0f) + i, (start.y * 4.0f) + j);
                auto got = umap.find(ptr);
                if (got == umap.end()) {
                    //std::cout << "found " << (start.x * 4.0f) + i << " " << (start.y * 4.0f) + j << std::endl;
                    std::shared_ptr<Chunk> chunk = std::make_shared<Chunk>();
                    chunk->initChunk(blockstab, glm::vec3((start.x * 4.0f) + i, 0.0f, (start.y * 4.0f) + j));
                    chunk->generateChunk();
                    umap.emplace(ptr, chunk);

                }


            }
        }
        needToGen = false;
    }
}

void Generate::drawWorld(Shader& shader, glm::vec2 start) {
    for (int i = -renderDistance; i <= renderDistance; i++) {
        for (int j = -renderDistance; j <= renderDistance; j++) {
            auto got = umap.find(glm::vec2((start.x * 4.0f) + i, (start.y * 4.0f) + j));
            if (got != umap.end()) {
                got->second->drawChunk(shader);
            }
            else {
                needToGen = true;
            }
        }
    }

}

