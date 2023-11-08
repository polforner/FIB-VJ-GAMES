#ifndef _SCENEMAIN_INCLUDE
#define _SCENEMAIN_INCLUDE


#include <glm/glm.hpp>
#include <vector>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Scene.h"

#include "Player.h"
#include "Entity.h"
#include "Block.h"
#include "PickUp.h"
#include "Enemy.h"

class Lvl2Scene : public Scene
{

public:
	Lvl1Scene();
	~Lvl1Scene();

	void init() override;
	void update(int deltaTime) override;
	void render() override;

private:
	void initShaders();
	void updateCamera();
	void prepareEntities();

	TileMap *background, *map, *entities;
	Player *player;
	float currentTime;
	ShaderProgram texProgram;
	glm::ivec2 posCamera;
	glm::mat4 projection, modelview;
	vector<Block*> blocks;
	vector<PickUp*> pickUps;
	vector<Enemy*> enemies;	
	Spritesheet spritesheet;
	Sprite smallSprite;
};
#endif // _SCENE_INCLUDE
