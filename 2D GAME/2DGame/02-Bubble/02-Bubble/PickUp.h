#ifndef _PICKUP_INCLUDE
#define _PICKUP_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include "Entity.h"

class PickUp : public Entity {

public:
	virtual void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) override;
	virtual void update(int deltaTime) = 0;

	virtual bool collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) = 0;
	virtual bool collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size, int *posX) = 0;
	virtual bool collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) = 0;
	virtual bool collisionMoveUp(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) = 0;

    virtual int pick() = 0;

protected:
    bool isPicked;
private:
};


#endif
