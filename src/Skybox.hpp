#pragma once

#include "Shader.hpp"
#include "Cube.hpp"

class Skybox {
public:

	void init();
	void render(const glm::mat4& projection, glm::mat4 view);
	void destroy();

private:

	Cube cube;
	Shader shader;

};