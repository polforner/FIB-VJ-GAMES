#ifndef _SCENECREDS_INCLUDE
#define _SCENECREDS_INCLUDE


#include <glm/glm.hpp>
#include <vector>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Scene.h"
#include "Sprite.h"

class SceneCreds : public Scene
{

public:
	SceneCreds();
	~SceneCreds();

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
