#include "Enemy.h"

void Enemy::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
    Entity::init(tileMapPos, shaderProgram);
}

void Enemy::setCollisions(TileMap *m, vector<Block*> &b) {
    map = m;
    blocks = b;
}