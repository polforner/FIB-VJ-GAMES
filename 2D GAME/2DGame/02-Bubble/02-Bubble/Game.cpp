#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	scene.init1();
}

bool Game::update(int deltaTime)
{
	scene.update(deltaTime);

	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene.render();
}

void Game::keyPressed(int key)
{
	if (key == 27) // Escape code
		bPlay = false;
	if (key == 'l'){
		if((curScene != "instr") && (curScene != "creds")){
			scene.init1();
			curScene = "lv1";
		}
	}
	if (key == 'p') {
		if (curScene == "main") {
			scene.initInstr();
			curScene = "instr";
		}
		else if (curScene == "lv1") {
			scene.init2();
			curScene = "lv2";
		}
	}
	if (key == 'b') {
		if ((curScene == "instr") || (curScene == "creds")) {
			scene.initMain();
			curScene = "main";
		}
	}
	if (key == 3) {
		if ((curScene != "lv1") && (curScene != "lv2")) {
			scene.initCredits();
			curScene = "creds";
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