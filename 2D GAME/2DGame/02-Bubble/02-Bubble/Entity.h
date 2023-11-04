#ifndef _ENTITY_INCLUDE
#define _ENTITY_INCLUDE

#include "Sprite.h"
#include "TileMap.h"

class Entity {

public:
	virtual void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	virtual void update(int deltaTime) = 0;
	void render();

	virtual bool collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) = 0;
	virtual bool collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size, int *posX) = 0;
	virtual bool collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) = 0;
	virtual bool collisionMoveUp(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) = 0;

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	bool isEntityActive() {return isActive;}


protected:
	glm::ivec2 tileMapDispl, position;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	bool isActive;
	bool collision(const glm::ivec2 &pos1,const glm::ivec2 &size1,const glm::ivec2 &pos2,const glm::ivec2 &size2);

private:
};


#endif
