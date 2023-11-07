#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include "Entity.h"
#include "Block.h"

class Enemy : public Entity {

public:
	virtual void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) override;
	virtual void update(int deltaTime) = 0;

	virtual bool collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) = 0;
	virtual bool collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size, int *posX) = 0;
	virtual bool collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) = 0;
	virtual bool collisionMoveUp(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) = 0;

	virtual void hit() = 0;
	void setCollisions(TileMap *map, vector<Block*> &blocks);

protected:
	vector<Block*> blocks;
	TileMap *map;
	bool isHit;
private:
};


#endif
