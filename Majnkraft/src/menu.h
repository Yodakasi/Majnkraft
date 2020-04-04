#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

class Menu {
private:

	struct Character {
		GLuint     TextureID;  // ID handle of the glyph texture
		glm::ivec2 Size;       // Size of glyph
		glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
		GLuint     Advance;    // Offset to advance to next glyph
	};
    GLuint* VAO;
    GLuint* VBO;
	
	glm::mat4 projection;

	std::map<GLchar, Character> Characters;
	bool renderMenu;
    
public:
	Menu(const unsigned int width, const unsigned int height, Shader& s, GLuint *VAO, GLuint *VBO);
	void RenderText(Shader &s, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	bool getRenderMenu();
	void run(Shader& s, GLFWwindow* window, const unsigned int width, const unsigned int height);

};