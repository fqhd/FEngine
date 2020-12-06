#pragma once
#include <GL/glew.h>
#include <string>
#include <fstream>

class Shader{

public:

	void bind();
	void unbind();
	void destroy();

protected:

	void loadShader(const char* vs, const char* fs);

	GLuint m_programID;
	GLuint m_vertexID;
	GLuint m_fragmentID;
};
