#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Entity.h"
#include "Block.h"
#include "PickUp.h"
#include "Enemy.h"
#include <vector>


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
	void setBlocks(const vector<Block*> &b) {blocks = b;};
	void setPickUps(const vector<PickUp*> &p) {pickUps = p;};
	void setEnemies(const vector<Enemy*> &e) {enemies = e;};

	glm::ivec2 getPosition();
	
private:
	void configureSprites(ShaderProgram &shaderProgram);
	bool isBlockCollision(const int &dir);
	bool isPickUpCollision(const int &dir);
	bool isEnemyCollision(const int &dir);

	void hit();

	void selectSprite();

	glm::ivec2 tileMapDispl, posPlayer, minCoords, size;
	bool bJumping;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite, *smallSprite, *bigSprite;
	TileMap *map;
	int state;
	bool changeState;
	bool isSwaping;
	bool isStar;
	bool inControl;
	bool isEliminated;
	bool isRunning;

	int timer;
	double velocity;

	vector<Block*> blocks;
	vector<PickUp*> pickUps;
	vector<Enemy*> enemies;
	int coins, score;
};


#endif // _PLAYER_INCLUDE


