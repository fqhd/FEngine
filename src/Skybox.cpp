#include <FEngine/Skybox.hpp>
#include <iostream>

void Skybox::init() {
	cube.init();
	shader.init("../res/shaders/skybox");
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