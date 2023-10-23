#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"


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


private:
	TileMap *background;
	TileMap *map;
	TileMap *entities;
	Player *player;
	ShaderProgram texProgram;
	float currentTime;
	glm::ivec2 posCamera;
	glm::mat4 projection, modelview;

};


#endif // _SCENE_INCLUDE

