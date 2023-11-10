#include <iostream>
#include <cmath>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include "SceneInstr.h"
#include "Game.h"
#include "Brick.h"
#include "QuestionMark.h"
#include "Coin.h"
#include "Mushroom.h"
#include "Star.h"
#include "Goomba.h"

#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 0
#define INIT_PLAYER_Y_TILES 12

#define CAMERA_VELOCITY 2


SceneInstr::SceneInstr()
{
	map = background = entities = NULL;
	player = NULL;
}

SceneInstr::~SceneInstr()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
}

void SceneInstr::prepareEntities() {
	
}

void SceneInstr::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}

void SceneInstr::updateCamera() {
}

void SceneInstr::init()
{
	//clear todo
	//deleteAllEntities(); 
	initShaders();
	spritesheet.loadFromFile("images/pantallaControles.png", TEXTURE_PIXEL_FORMAT_RGBA);
	smallSprite = Sprite::createSprite(glm::ivec2(640,512), glm::vec2(0.125, 0.125), &spritesheet, &texProgram);
	posCamera = glm::ivec2(-SCREEN_WIDTH, -SCREEN_HEIGHT);
	//projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT), 0.f);
	modelview = glm::mat4(1.0f);
	currentTime = 0.0f;
}

void SceneInstr::update(int deltaTime)
{
	
}

void SceneInstr::render()
{
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	smallSprite->render();
}
