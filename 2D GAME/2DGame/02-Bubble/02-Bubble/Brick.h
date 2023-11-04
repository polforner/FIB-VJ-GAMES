#ifndef _BRICK_INCLUDE
#define _BRICK_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include "Block.h"

class Brick : public Block{

public:
    void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) override;
    void update(int deltaTime) override;

	bool collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) override;
	bool collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size, int *posX) override;
	bool collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) override;
	bool collisionMoveUp(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) override;

	void hit() override;
    void destroy() override;
private:

	int type, numCoins;
	int jumpAngle, originalY;
	int breakingTime;
};
#endif
