#pragma once

#include <FEngine/Shader.hpp>
#include <FEngine/Cube.hpp>

namespace FEngine
{
	class Skybox
	{
	public:
		void init();
		void render(const glm::mat4 &projection, glm::mat4 view);
		void destroy();

	private:
		Cube cube;
		Shader shader;
	};
}