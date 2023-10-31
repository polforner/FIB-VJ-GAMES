#include "Entity.h"

void Entity::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
    isActive = true;
    tileMapDispl = tileMapPos;
}

void Entity::render() {
	sprite->render();
}

void Entity::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}
	   
void Entity::setPosition(const glm::vec2 &pos) {
    position = pos;
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
}