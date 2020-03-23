#pragma once

#include <GL/glew.h>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader {
private:
	unsigned int id;
public:

	Shader(const char *vertexPath, const char *fragmentPath);
	//~Shader();
	unsigned int getId();

	void use();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void setColor(const std::string& name, float r, float g, float b, float a) const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;
};