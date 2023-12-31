#ifndef _LVL2SCENE_INCLUDE
#define _LVL2SCENE_INCLUDE


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
#include "Text.h"

class Lvl2Scene : public Scene
{

public:
	Lvl2Scene();
	~Lvl2Scene();

	void init() override;
	void update(int deltaTime) override;
	void render() override;

private:
	void initShaders();
	void updateCamera();
	void prepareEntities();

	TileMap *background, *map, *entities;
	Player *player;
	ShaderProgram texProgram;
	glm::ivec2 posCamera;
	glm::mat4 projection, modelview;
	vector<Block*> blocks;
	vector<PickUp*> pickUps;
	vector<Enemy*> enemies;
	Text *painter;
};
#endif // _SCENE_INCLUDE
