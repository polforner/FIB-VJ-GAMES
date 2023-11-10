#ifndef _SCENEINSTR_INCLUDE
#define _SCENEINSTR_INCLUDE


#include <glm/glm.hpp>
#include <vector>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Scene.h"
#include "Sprite.h"

class SceneInstr : public Scene
{

public:
	SceneInstr();
	~SceneInstr();

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
