#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

#include "game.h"



Game::Game() : noisy(), gen(), camera() {
    

}

void Game::init(GLFWwindow* window, Shader& s, GLuint* VAO, GLuint* VBO, const unsigned int width, const unsigned int height, int renDis) {
    this->VAO = VAO;
    this->VBO = VBO;
    deltaTime = 0.0f;
    lastFrame = 0.0f;
    firstMouse = true;
    lastX = width / 2.0;
    lastY = height / 2.0;
    gen.init(renDis);
    s.loadShaders("res/shaders/vertex.vs", "res/shaders/fragment.fs");
    glDisable(GL_CULL_FACE);
    glDisable(GL_BLEND);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glEnable(GL_DEPTH_TEST);
    glGenVertexArrays(1, VAO);
    glGenBuffers(1, VBO);

    glBindVertexArray(*VAO);

    glBindBuffer(GL_ARRAY_BUFFER, *VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
    model = glm::mat4(1.0f);
    gen.generateWorld(glm::vec2(0.0f, 0.0f), this->noisy);
    camera.CameraSetPos(glm::vec3(0.0f, -round(noisy.noiseFun(0.0f, 0.0f) * 64)+2.0f, 0.0f));
}

void Game::run(GLFWwindow* window, Shader &s) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    processInput(window);
    int modelLoc = glGetUniformLocation(s.getId(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    s.setMat4("view", camera.GetViewMatrix());

    int projLoc = glGetUniformLocation(s.getId(), "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);


    glBindVertexArray(*VAO);


    if (camera.getCameraMoved())
        gen.generateWorld(camera.get2dPos(), this->noisy);
    gen.drawWorld(s, camera.get2dPos());
}

void Game::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    float cameraSpeed = 2.5 * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(0, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(1, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(2, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(3, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessKeyboard(4, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        camera.ProcessKeyboard(5, deltaTime);
        
}

void Game::ProcessMouseMovement(float xoffset, float yoffset) {
    camera.ProcessMouseMovement(xoffset, yoffset);
}

