#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"
#include "Lvl1Scene.h"
#include "Lvl2Scene.h"
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
 	curScene = LVL2;
  	scenes[curScene] = new Lvl2Scene();
	curScene = LVL1;
	scenes[curScene] = new Lvl1Scene();

	/*
 	curScene = INSTR; 
  	scenes[curScene] = new SceneInstr(); 
   	curScene = CREDS; 
    	scenes[curScene] = new SceneCreds(); 

   	curScene = MAIN;
	scenes[curScene] = new SceneMain();
	scenes[curScene] -> init();
 	*/
 	changeScene = true;
	mainMusic = createIrrKlangDevice();
	efectos = createIrrKlangDevice();
	
	//mainMusic->play2D("/audio/getout.ogg", true);
	
	
}

bool Game::update(int deltaTime)
{
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

void Game::keyPressed(int key)
{
	if (key == 27) // Escape code
		bPlay = false;
	if (key == 'l'){
		if((curScene != INSTR) && (curScene != CREDS)){
			curScene = LVL1;
			changeScene = true;
		}
	}
	if (key == 'p') {
		if (curScene == MAIN) {
			curScene = INSTR;
			changeScene = true;
		}
		else if (curScene == LVL1) {

			curScene = LVL2;
			changeScene = true;
		}
	}
	if (key == 'b') {
		if ((curScene == INSTR) || (curScene == CREDS)) {

			curScene = MAIN;
			//scenes[curScene] -> init(); 
		}
	}
	if (key == 3) {
		if ((curScene != LVL1) && (curScene != LVL2)) {

			curScene = CREDS;
			//scenes[curScene] -> init(); 
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
	else if (queCosa == "flag")efectos->play2D("audio/smb_stage_clear.wav", false); //que suene al final de la animación
	else if (queCosa == "jump")efectos->play2D("audio/smb_jump-small.wav", false); 
}

