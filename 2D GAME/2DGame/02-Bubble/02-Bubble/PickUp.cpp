#include "PickUp.h"

void PickUp::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
    Entity::init(tileMapPos, shaderProgram);
    isPicked = false;
}
