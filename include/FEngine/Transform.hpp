#pragma once

#include <glm/gtc/matrix_transform.hpp>

namespace FEngine
{
	class Transform
	{
	public:
		Transform();

		glm::mat4 getMatrix() const;

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
	};
}