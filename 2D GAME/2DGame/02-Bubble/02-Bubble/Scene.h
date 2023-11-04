#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include<vector>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Entity.h"
#include "Block.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();

private:
	void initShaders();
	void updateCamera();
	void prepareEntities();


private:
	TileMap *background, *map, *entities;
	Player *player;
	ShaderProgram texProgram;
	float currentTime;
	glm::ivec2 posCamera;
	glm::mat4 projection, modelview;
	//vector<Entity*> solid, colectables, enemies, ent;
	vector<Block*> blocks;

};


#endif // _SCENE_INCLUDE

