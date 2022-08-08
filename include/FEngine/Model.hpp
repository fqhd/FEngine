#pragma once

#include <FEngine/OBJLoader.hpp>
#include <FEngine/Vertex.hpp>
#include <glad.h>

class Model {
public:

	void init(const std::string& path);
	void draw() const;
	void destroy();

private:

	GLuint m_numVertices = 0;
	GLuint m_vaoID = 0;
	GLuint m_vboID = 0;
	GLuint m_eboID = 0;

};