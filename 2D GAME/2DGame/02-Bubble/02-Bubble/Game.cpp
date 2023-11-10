#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "SceneMain.h"
#include "SceneInstr.h"
#include "Lvl1Scene.h"
#include "Lvl2Scene.h"
#include "SceneCreds.h"
#include "irrKlang.h"
using namespace irrklang;
#pragma comment(lib, "irrKlang.lib")

enum Scenes {
	MAIN, INSTR, LVL1, LVL2, CREDS, COUNT
};

const vector<char*> backgroundMusics = {"","","audio/lv1music.wav","audio/lv2music.wav",""};
void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	scenes = vector<Scene*> (COUNT);
   	curScene = MAIN;
	scenes[curScene] = new SceneMain();
	scenes[curScene] -> init();
	curScene = LVL1;
	scenes[curScene] = new Lvl1Scene();
	scenes[curScene] -> init();
 	curScene = LVL2;
  	scenes[curScene] = new Lvl2Scene();
	scenes[curScene] -> init();
   	curScene = CREDS; 
    scenes[curScene] = new SceneCreds();
	scenes[curScene] -> init();
 	curScene = INSTR; 
  	scenes[curScene] = new SceneInstr(); 
	scenes[curScene] -> init();

 	curScene = MAIN;
 	changeScene = true;
	mainMusic = createIrrKlangDevice();
	efectos = createIrrKlangDevice();
	coins = 0;
	points = 0;
	lives = 3;
	remainingTime = 120;
}

bool Game::update(int deltaTime)
{
	remainingTime -= deltaTime / 1000.f;
	scenes[curScene] -> update(deltaTime);

	return bPlay;
}

void Game::render()
{
	if (changeScene) {
		mainMusic -> stopAllSounds();
		scenes[curScene] -> init(); 
		changeScene = false;
		mainMusic -> play2D(backgroundMusics[curScene], true);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scenes[curScene] -> render();
}

void Game::keyPressed(int key) {
	if (key == 27) // Escape code
		bPlay = false;
	if (key == 'p') {
		if (curScene == MAIN) {
			curScene = INSTR;
			changeScene = true;
		}
		else if (curScene == LVL1) {
			curScene = LVL2;
			remainingTime = 120;	
			changeScene = true;
		}
	}
	if (key == 'b') {
		if ((curScene == INSTR) || (curScene == CREDS)) {
			curScene = MAIN;
			changeScene = true;
		}
	}
	if (key == 'o') {
		if ((curScene == LVL1) || (curScene == LVL2)) {
			remainingTime -= 10;
		}
	}
	if (key == '1') {
		if (curScene == MAIN) {
			curScene = LVL1;
			remainingTime = 120;
			changeScene = true;
		}
		else if (curScene == LVL1) {
			curScene = LVL1;
			remainingTime = 120;	
			changeScene = true;
		}
	}
	if (key == '2') {
		if (curScene == MAIN) {
			curScene = INSTR;
			changeScene = true;
		}
		else if (curScene == LVL1 || curScene == LVL2) {
			curScene = LVL2;
			remainingTime = 120;	
			changeScene = true;
		}
	}
	if (key == '3') {
		if (curScene == MAIN) {
			curScene = CREDS;
			changeScene = true;
		}
	}
	if (key == 3) {
		if ((curScene != LVL1) && (curScene != LVL2)) {
			curScene = CREDS;
			changeScene = true;
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

int Game::getRemainingTime() {
	if (remainingTime <= 0) return 0;
	return remainingTime;
}

int Game::getActualLvl() {
	if (curScene == LVL1) return 1;
	else if (curScene == LVL2) return 2;
	return -1;
}

glm::ivec2 Game::flagPosition() {
	if (curScene == LVL1) return glm::ivec2(232 * 64, 12 * 64);
	else if (curScene == LVL2) return glm::ivec2(162 * 64, 12 * 64);
}

void Game::playMusic(string queCosa) {
	efectos -> stopAllSounds();
	
	if (queCosa == "goombaDie") efectos->play2D("audio/smb_stomp.wav", false);
	else if (queCosa == "brickHit")efectos->play2D("audio/smb_bump.wav", false);
	else if (queCosa == "brickDestroy")efectos->play2D("audio/smb_breakblock.wav", false);
	else if (queCosa == "mushroom")efectos->play2D("audio/smb_powerup.wav", false);
	else if (queCosa == "die"){
		mainMusic -> stopAllSounds();
		efectos->play2D("audio/smb_mariodie.wav", false);
	}
	else if (queCosa == "flag"){
		mainMusic -> stopAllSounds(); 
		efectos->play2D("audio/smb_stage_clear.wav", false);
	}//que suene al final de la animación
	else if (queCosa == "jump")efectos->play2D("audio/smb_jump-small.wav", false); 
	else if (queCosa == "takeDmg")efectos->play2D("audio/smb_shrink.wav", false); 
	else if (queCosa == "starMario") {
		mainMusic -> stopAllSounds();
		efectos-> play2D("audio/smb_starMario.wav", false);
	}
	else if (queCosa == "main") {
		mainMusic -> stopAllSounds();
		if (curScene == LVL1) mainMusic -> play2D("audio/lv1music.wav", false);
		else mainMusic -> play2D("audio/lv2music.wav", false);
	}
}

void Game::imDead() {
	lives -= 1;
	remainingTime = 120;
	if (lives < 0) {
		curScene = CREDS;
		lives = 3;
	}
	changeScene = true;
}

void Game::win() {
	if (curScene == LVL1) curScene = LVL2;
	else if (curScene == LVL2) curScene = CREDS;
	remainingTime = 120;
	changeScene = true;
}
