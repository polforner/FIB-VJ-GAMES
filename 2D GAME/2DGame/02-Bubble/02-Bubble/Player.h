#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Entity.h"
#include<vector>


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
	void setEntities(const vector<Entity*> &entities) {ent = entities;};

	glm::ivec2 getPosition();
	
private:

	void configureSmallSprite(ShaderProgram &shaderProgram);

	bool bJumping;
	glm::ivec2 tileMapDispl, posPlayer, minCoords;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
	int state;
	bool inControl;
	bool isEliminated;
	double velocity;
	vector<Entity*> ent;
};


#endif // _PLAYER_INCLUDE


