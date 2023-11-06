#ifndef _MUSHROOM_INCLUDE
#define _MUSHROOM_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include "PickUp.h"

class Mushroom : public PickUp {

public:
    void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) override;
    void update(int deltaTime) override;

	bool collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) override;
	bool collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size, int *posX) override;
	bool collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) override;
	bool collisionMoveUp(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) override;

	void setPosition(const glm::vec2 &pos) override;
	int pick() override;
private:
};
#endif
