#pragma once

#include <string>
#include <fstream>
#include <unordered_map>
#include <glm/glm.hpp>
#include <GL/glew.h>

class Shader {
public:

	void init(const char* vs, const char* fs);
	void bind();
	void unbind();
	void destroy();

	void set(const std::string& name, const glm::vec3& vec);
	void set(const std::string& name, const glm::mat4& matrix);
	void set(const std::string& name, float f);
	void set(const std::string& name, int i);
	void set(const std::string& name, bool b);

private:

	GLint getUniformLocation(const std::string& name);

	std::unordered_map<std::string, GLint> m_uniformLocations;

	GLuint m_programID = 0;
	GLuint m_vertexID = 0;
	GLuint m_fragmentID = 0;

};

