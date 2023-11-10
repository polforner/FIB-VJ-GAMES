#include "Block.h"

void Block::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
    Entity::init(tileMapPos, shaderProgram);
    isHit = false;
    isDestroyed = false;
}