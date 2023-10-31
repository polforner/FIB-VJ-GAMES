#ifndef _ENTITY_INCLUDE
#define _ENTITY_INCLUDE

#include "Sprite.h"
#include "TileMap.h"

class Entity {

public:
	virtual void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	virtual void update(int deltaTime) = 0;
	void render();

	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);

protected:
	glm::ivec2 tileMapDispl, position;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;

	bool isActive;
};


#endif
