#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	void setMinCoords(const glm::vec2 &coord);

	glm::ivec2 getPosition();
	
private:
	bool bJumping;
	glm::ivec2 tileMapDispl, posPlayer, minCoords;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	bool isSmall; 
	bool inControl;
	bool isStar;
	bool isEliminated;
	double velocity;
};


#endif // _PLAYER_INCLUDE


