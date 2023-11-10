#ifndef _SCENEMAIN_INCLUDE
#define _SCENEMAIN_INCLUDE


#include <glm/glm.hpp>
#include <vector>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Scene.h"
#include "Sprite.h"

class SceneMain : public Scene
{

public:
	SceneMain();
	~SceneMain();

	void init() override;
	void update(int deltaTime) override;
	void render() override;

private:
	void initShaders();

	ShaderProgram texProgram;
	glm::mat4 projection, modelview;
	Texture spritesheet;
	Sprite *sprite;
};
#endif
