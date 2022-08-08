#include <FEngine/Skybox.hpp>
#include <iostream>

#define LOAD_AS_STRING(...) "#version 330 core \n"#__VA_ARGS__

void Skybox::init() {
	cube.init();

	shader.init(
		#include <FEngine/shaders/skybox/vertex.glsl>
		,
		#include <FEngine/shaders/skybox/fragment.glsl>
	);
}

void Skybox::render(const glm::mat4& projection, glm::mat4 view) {
	view[3][0] = 0;
	view[3][1] = 0;
	view[3][2] = 0;

	shader.bind();
	shader.set("projection", projection);
	shader.set("view", view);

	glDepthMask(GL_FALSE);
	glDisable(GL_CULL_FACE);
	cube.render();
	glEnable(GL_CULL_FACE);
	glDepthMask(GL_TRUE);

	shader.unbind();
}

void Skybox::destroy() {
	cube.destroy();
	shader.destroy();
}