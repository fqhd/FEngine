#include "Entity.hpp"

Entity::Entity(const Transform& t, Model* m){
     transform = t;
     model = m;
}

void Entity::render(){
     model->render();
}
