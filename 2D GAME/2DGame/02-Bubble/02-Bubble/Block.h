#ifndef _BLOCK_INCLUDE
#define _BLOCK_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include "Entity.h"

class Block : public Entity {

public:
	virtual void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) override;
	virtual void update(int deltaTime) = 0;

	virtual bool collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) = 0;
	virtual bool collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size, int *posX) = 0;
	virtual bool collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) = 0;
	virtual bool collisionMoveUp(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) = 0;

    virtual void hit() = 0;
    virtual void destroy() = 0;

protected:
    bool isHit, isDestroyed;
private:
};


#endif
