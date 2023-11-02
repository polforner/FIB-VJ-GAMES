#include "Entity.h"

void Entity::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
    isActive = true;
    tileMapDispl = tileMapPos;
}

void Entity::render() {
	sprite->render();
}

bool Entity::collision(const glm::ivec2 &pos1,const glm::ivec2 &size1,const glm::ivec2 &pos2,const glm::ivec2 &size2) {
    return pos1.x < (pos2.x + size2.x) && pos2.x < pos1.x + size1.x
    && pos1.y < (pos2.y + size2.y) && pos2.y < pos1.y + size1.y;
}

void Entity::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}
	   
void Entity::setPosition(const glm::vec2 &pos) {
    position = pos;
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
}