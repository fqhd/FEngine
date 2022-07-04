#include "Transform.hpp"

Transform::Transform(){
	position = glm::vec3(0);
	rotation = glm::vec3(0);
	scale = glm::vec3(1);
}

glm::mat4 Transform::getMatrix() const {
	glm::mat4 matrix;
    glm::translate(matrix, position);
    glm::rotate(matrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));
    glm::rotate(matrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
    glm::rotate(matrix, glm::radians(rotation.x), glm::vec3(1, 0, 0));
	glm::scale(matrix, scale);
	return matrix;
}