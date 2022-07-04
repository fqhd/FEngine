#pragma once
#include <GL/glad.h>
#include <string>
#include <fstream>

#include "Utils.hpp"


class Shader{

public:

	void bind();
	void unbind();
	void destroy();

protected:

	void loadShader(const std::string& vs, const std::string& fs);

	GLuint m_programID;
	GLuint m_vertexID;
	GLuint m_fragmentID;
};
