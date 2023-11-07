#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "Lvl1Scene.h"

enum Scenes {
	MAIN, INSTR, LVL1, LVL2, CREDS, COUNT
};
void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	scenes = vector<Scene*> (COUNT);
	curScene = LVL1;
	scenes[curScene] = new Lvl1Scene();
	scenes[curScene] -> init();
	
	
}

bool Game::update(int deltaTime)
{
	scenes[curScene] -> update(deltaTime);

	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scenes[curScene] -> render();
}

void Game::keyPressed(int key)
{
	if (key == 27) // Escape code
		bPlay = false;
	if (key == 'l'){
		if((curScene != INSTR) && (curScene != CREDS)){
			curScene = LVL1;
			scenes[curScene] ->init();
		}
	}
	if (key == 'p') {
		if (curScene == MAIN) {

			curScene = INSTR;
		}
		else if (curScene == LVL1) {

			curScene = LVL2;
		}
	}
	if (key == 'b') {
		if ((curScene == INSTR) || (curScene == CREDS)) {

			curScene = MAIN;
		}
	}
	if (key == 3) {
		if ((curScene != LVL1) && (curScene != LVL2)) {

			curScene = CREDS;
		}
	}
	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::specialKeyPressed(int key)
{
	specialKeys[key] = true;
}

void Game::specialKeyReleased(int key)
{
	specialKeys[key] = false;
}

void Game::mouseMove(int x, int y)
{
}

void Game::mousePress(int button)
{
}

void Game::mouseRelease(int button)
{
}

bool Game::getKey(int key) const
{
	return keys[key];
}

bool Game::getSpecialKey(int key) const
{
	return specialKeys[key];
}