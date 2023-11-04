#include <iostream>
#include <cmath>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Game.h"
#include "Brick.h"
#include "QuestionMark.h"
#include "Coin.h"


#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 0
#define INIT_PLAYER_Y_TILES 13

#define CAMERA_VELOCITY 2


Scene::Scene()
{
	map = background = entities = NULL;
	player = NULL;
}

Scene::~Scene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
}

void Scene::prepareEntities() {
	glm::ivec2 size = entities -> getMapSize();
	int tileSize = entities -> getTileSize();
	for (int x = 0; x < size.x; ++x) {
		for (int y = 0; y < size.y; ++y) {
			Block *block = nullptr;
			int tileTipe = entities -> getTileTipe(y*size.x + x);
			if (tileTipe == 11) block = new Brick();
			else if (tileTipe == 3) block = new QuestionMark();
			//else if (tileTipe == 23) temp = new Coin();
			if(block) {
				block -> init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				block -> setPosition(glm::vec2(x * tileSize,y * tileSize));
				block -> setTileMap(map);
				blocks.push_back(block);
			}
		}
	}
}

void Scene::init()
{
	initShaders();
	//mirar porque no va si cambio el nombre
	map = TileMap::createTileMap("levels/01-map.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	background = TileMap::createTileMap("levels/01-background.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	entities = TileMap::createTileMap("levels/01-entities.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	prepareEntities();
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	//player ->setEntities(blocks);
	player -> setBlocks(blocks);
	posCamera = glm::ivec2(-SCREEN_WIDTH, -SCREEN_HEIGHT);
	updateCamera();
	//projection = glm::ortho(0.f, float(SCREEN_WIDTH), float(SCREEN_HEIGHT), 0.f);
	modelview = glm::mat4(1.0f);
	currentTime = 0.0f;
}

void Scene::updateCamera() {
	// Obtenemos la posición actual del jugador.
	glm::ivec2 playerPosition = player->getPosition();
	if(playerPosition.x >= (posCamera.x + (SCREEN_WIDTH / 3))) {
		// Calcula el centro de la ventana visible.
		posCamera.x = playerPosition.x - (SCREEN_WIDTH / 3);

		// Asegúrate de que la cámara no se salga de los límites del mapa.
		int mapWidth = map->getMapSize().x * map->getTileSize();
		posCamera.x = glm::clamp(posCamera.x, 0, mapWidth - SCREEN_WIDTH);
		player -> setMinCoords(posCamera);
		// Actualiza la matriz de vista para reflejar la posición de la cámara.
		int mapHeight = map->getMapSize().y * map->getTileSize();
		projection = glm::ortho(0.f + posCamera.x, float(SCREEN_WIDTH) + posCamera.x, float(mapHeight), 0.f);
	}
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	int numEntities = blocks.size();
	for (int i = 0; i < numEntities; ++i)
		if (blocks[i] -> isEntityActive()) blocks[i] -> update(deltaTime);
	updateCamera();
}

void Scene::render()
{
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	background -> render();
	map->render();
	//entities -> render();
	int numEntities = blocks.size();
	for (int i = 0; i < numEntities; ++i)
		if (blocks[i] -> isEntityActive()) blocks[i] -> render();
	player->render();
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}



