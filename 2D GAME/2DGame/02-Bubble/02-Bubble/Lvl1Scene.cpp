#include <iostream>
#include <cmath>
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>
#include "Lvl1Scene.h"
#include "Game.h"
#include "Brick.h"
#include "QuestionMark.h"
#include "Coin.h"
#include "Mushroom.h"
#include "Star.h"
#include "Goomba.h"
#include "Koopa.h"

#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 1
#define INIT_PLAYER_Y_TILES 12

#define CAMERA_VELOCITY 2


Lvl1Scene::Lvl1Scene()
{
	map = background = entities = NULL;
	player = NULL;
}

Lvl1Scene::~Lvl1Scene()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
}

void Lvl1Scene::prepareEntities() {
	blocks = vector<Block*>();
	pickUps = vector<PickUp*>();
	enemies = vector<Enemy*>();	
	glm::ivec2 size = entities->getMapSize();
	int tileSize = entities->getTileSize();
	for (int x = 0; x < size.x; ++x) {
		for (int y = 0; y < size.y; ++y) {
			Block *block = nullptr;
			PickUp *pickUp = nullptr;
			Enemy *enemy = nullptr;
			int tileTipe = entities -> getTileTipe(y*size.x + x);
			if (tileTipe == 11) block = new Brick();
			else if (tileTipe == 3) { 
				block = new QuestionMark();
				if (y <= 8) pickUp = new Star();
				else pickUp = new Mushroom();
				
			}
			else if (tileTipe == 23) pickUp = new Coin();
			else if (tileTipe == 24) enemy = new Goomba();
			else if (tileTipe == 30) enemy = new Koopa();
			
			if(block) {
				block -> init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				block -> setPosition(glm::vec2(x * tileSize,y * tileSize));
				block -> setTileMap(map);
				blocks.push_back(block);
			}
			if (pickUp) {
				pickUp -> init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				pickUp -> setPosition(glm::vec2(x * tileSize,y * tileSize));
				pickUp -> setTileMap(map);
				pickUps.push_back(pickUp);	
			}
			if (enemy) {
				enemy -> init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
				enemy -> setPosition(glm::vec2(x * tileSize,y * tileSize));
				enemy -> setTileMap(map);
				enemy -> setCollisions(map, blocks);
				enemies.push_back(enemy);	
			}
		}
	}
}

void Lvl1Scene::initShaders()
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

void Lvl1Scene::updateCamera() {
	// Obtenemos la posición actual del jugador.
	glm::ivec2 playerPosition = player->getPosition();
	if (playerPosition.x >= (posCamera.x + (SCREEN_WIDTH / 3))) {
		// Calcula el centro de la ventana visible.
		posCamera.x = playerPosition.x - (SCREEN_WIDTH / 3);

		// Asegúrate de que la cámara no se salga de los límites del mapa.
		int mapWidth = map->getMapSize().x * map->getTileSize();
		posCamera.x = glm::clamp(posCamera.x, 0, mapWidth - SCREEN_WIDTH);
		player-> setMinCoords(posCamera);
		// Actualiza la matriz de vista para reflejar la posición de la cámara.
		int mapHeight = map->getMapSize().y * map->getTileSize();
		projection = glm::ortho(0.f + posCamera.x, float(SCREEN_WIDTH) + posCamera.x, float(mapHeight), 0.f);
	}
}

void Lvl1Scene::init()
{
	//clear todo
	//deleteAllEntities(); 
	initShaders();
	map = TileMap::createTileMap("levels/01-map.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	background = TileMap::createTileMap("levels/01-background.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	entities = TileMap::createTileMap("levels/01-entities.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	prepareEntities();
	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	player -> setBlocks(blocks);
	player -> setPickUps(pickUps);
	player -> setEnemies(enemies);
	posCamera = glm::ivec2(-SCREEN_WIDTH, -SCREEN_HEIGHT);
	updateCamera();
	modelview = glm::mat4(1.0f);
	painter = new Text();
	painter -> init("fonts/SuperMario256.ttf");
}

void Lvl1Scene::update(int deltaTime)
{
	player->update(deltaTime);
	int numBlocks = blocks.size();
	for (int i = 0; i < numBlocks; ++i)
		if (blocks[i] -> isEntityActive()) blocks[i] -> update(deltaTime);

	int numPickUps = pickUps.size();
	for (int i = 0; i < numPickUps; ++i)
		if (pickUps[i] -> isEntityActive()) pickUps[i] -> update(deltaTime);

	int numEnemies = enemies.size();
	for (int i = 0; i < numEnemies; ++i)
		if (enemies[i] -> isEntityActive()) enemies[i] -> update(deltaTime);
	
	updateCamera();
}

void Lvl1Scene::render()
{
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	background->render();
	map->render();

	//Render entities
	int numBlocks = blocks.size();
	for (int i = 0; i < numBlocks; ++i)
		if (blocks[i] -> isEntityActive()) blocks[i] -> render();

	int numEnemies = enemies.size();
	for (int i = 0; i < numEnemies; ++i)
		if (enemies[i] -> isEntityActive()) enemies[i] -> render();

	int numPickUps = pickUps.size();
	for (int i = 0; i < numPickUps; ++i)
		if (pickUps[i] -> isEntityActive()) pickUps[i] -> render();

	player->render();

	//Render values
	string text;
	//Score text
	text = "SCORE";
	painter -> render(text, glm::vec2(0.1 * SCREEN_WIDTH, 0.05 * SCREEN_HEIGHT), 32, glm::vec4(1, 1, 1, 1));
	text = to_string(Game::instance().getPoints());
	painter -> render(text, glm::vec2(0.1 * SCREEN_WIDTH, 0.10 * SCREEN_HEIGHT), 32, glm::vec4(1, 1, 1, 1));

	//Coins text
	text = "COINS";
	painter -> render(text, glm::vec2(0.3 * SCREEN_WIDTH, 0.05 * SCREEN_HEIGHT), 32, glm::vec4(1, 0.843, 0, 1));
	text = to_string(Game::instance().getCoins());
	painter -> render(text, glm::vec2(0.3 * SCREEN_WIDTH, 0.10 * SCREEN_HEIGHT), 32, glm::vec4(1, 0.843, 0, 1));

	//Worlds info text
	text = "WORLD";
	painter -> render(text, glm::vec2(0.5 * SCREEN_WIDTH, 0.05 * SCREEN_HEIGHT), 32, glm::vec4(1, 1, 1, 1));
	text = "1 - 1";
	painter -> render(text, glm::vec2(0.5 * SCREEN_WIDTH, 0.10 * SCREEN_HEIGHT), 32, glm::vec4(1, 1, 1, 1));

	//Time text
	text = "TIME";
	painter -> render(text, glm::vec2(0.7 * SCREEN_WIDTH, 0.05 * SCREEN_HEIGHT), 32, glm::vec4(1, 0.843, 0, 1));
	text = to_string(Game::instance().getRemainingTime());
	painter -> render(text, glm::vec2(0.7 * SCREEN_WIDTH, 0.10 * SCREEN_HEIGHT), 32, glm::vec4(1, 0.843, 0, 1));

}

