#include "Transform.hpp"

Transform::Transform(){
	position = glm::vec3(0);
	rotation = glm::vec3(0);
	scale = glm::vec3(1);
}

glm::mat4 Transform::getMatrix() const {
	glm::mat4 matrix(1);
    matrix = glm::translate(matrix, position);
    matrix = glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    matrix = glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    matrix = glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	matrix = glm::scale(matrix, scale);
	return matrix;
}