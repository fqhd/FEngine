#include "Entity.hpp"

Entity::Entity(const Transform& t, Model* m, StaticColor c){
     transform = t;
     model = m;
     color = c;
}

void Entity::render(){
     model->render();
}
