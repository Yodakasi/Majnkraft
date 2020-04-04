#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <noise/noise.h>
#include <cmath>


#include "stb_image.h"
#include "shader.h"
#include "camera.h"
#include "generate.h"
#include "noise.h"
#include "game.h"
#include "menu.h"


const unsigned int SCR_WIDTH = 1600;
const unsigned int SCR_HEIGHT = 900;
const int renderDistance = 16;

Game game = Game();
float deltaTime = 0.0f;
float lastFrame = 0.0f;
bool firstMouse = true;
float lastX = SCR_WIDTH / 2.0;
float lastY = SCR_HEIGHT / 2.0;
bool createGame = true;


void mouse_callback(GLFWwindow* window, double xpos, double ypos);

int main(void)
{
    GLFWwindow* window;


    /* Initialize the library */
    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Majnkraft", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;

    }

    glfwMakeContextCurrent(window);

  
    if (glewInit() != GLEW_OK)
        std::cout << "ERROR" << std::endl;



    Shader shader = Shader("res/shaders/menu.vs", "res/shaders/menu.fs");
 
    GLuint VAO;
    GLuint VBO;
  
    
    Menu menu = Menu(SCR_WIDTH, SCR_HEIGHT, shader, &VAO, &VBO);
    

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (menu.getRenderMenu()) {
            menu.run(shader, window, SCR_WIDTH, SCR_HEIGHT);
        }
        else {
            if (createGame) {
                game.init(window, shader, &VAO, &VBO, SCR_WIDTH, SCR_HEIGHT, renderDistance);
                glfwSetCursorPosCallback(window, mouse_callback);
                createGame = false;
            }
            game.run(window, shader);
            shader.use();
       }
        
            
     

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}




void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;
    game.ProcessMouseMovement(xoffset, yoffset);
}