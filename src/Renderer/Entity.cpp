#include "Entity.hpp"

Entity::Entity(const Transform& transform, Model* model, Texture* texture){
     this->transform = transform;
     this->model = model;
     this->texture = texture;
}
