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

	void configureSmallSprite(ShaderProgram &shaderProgram);
	void configureBigSprite(ShaderProgram &shaderProgram);
	void configureSmallStarSprite(ShaderProgram &shaderProgram);
	void configureBigStarSprite(ShaderProgram &shaderProgram);
	void configureSprites(ShaderProgram &shaderProgram);

	bool isBlockCollision(const int &dir);
	bool isPickUpCollision(const int &dir);
	bool isEnemyCollision(const int &dir);
	void hit();

	void selectSprite();


	bool bJumping;
	glm::ivec2 tileMapDispl, posPlayer, minCoords, size;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite *sprite, *smallSprite, *bigSprite, *smallStarSprite, *bigStarSprite;
	TileMap *map;
	int state;
	bool changeState;
	bool inControl;
	bool isEliminated;
	double velocity;


	vector<Block*> blocks;
	vector<PickUp*> pickUps;
	vector<Enemy*> enemies;
	int coins, score;
};


#endif // _PLAYER_INCLUDE


