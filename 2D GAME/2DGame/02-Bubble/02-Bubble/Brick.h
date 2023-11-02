#ifndef _BRICK_INCLUDE
#define _BRICK_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include "Entity.h"

class Brick : public Entity{

public:
    void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) override;
    void update(int deltaTime) override;

	bool collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) override;
	bool collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size, int *posX) override;
	bool collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) override;
	bool collisionMoveUp(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) override;
private:
    bool isHit, isDestroyed;
};
#endif
