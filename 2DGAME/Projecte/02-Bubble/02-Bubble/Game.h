#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include "Scene.h"
#include <vector>
#include <irrKlang.h>
#include "Text.h"
#include <List>
using namespace irrklang;


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 512


// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{

private:
	Game() {}

public:
	static Game &instance()
	{
		static Game G;

		return G;
	}

	void init();
	bool update(int deltaTime);
	void render();

	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void specialKeyPressed(int key);
	void specialKeyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);

	bool getKey(int key) const;
	bool getSpecialKey(int key) const;
	void playMusic(string queCosa);
	void imDead();
	void win();
	glm::ivec2 flagPosition();

	int getActualLvl();
	int getCoins() {return coins + currentCoins;};
	int getPoints() {return points + currentPoints;};
	int getLives() {return lives;};
	int getRemainingTime();

	void addCoin() { ++currentCoins; };
	void addPoints(int p);
	

private:
	bool bPlay;                       // Continue to play game?
	vector<Scene*> scenes;
	//Scene scene;                      // Scene to render
	bool keys[256], specialKeys[256]; // Store key states so that 
									  // we can have access at any time
	int curScene;
	bool changeScene;
	ISoundEngine* mainMusic;
	ISoundEngine* efectos;
	Text *text;
	//List<pair<int,int>> scores;
	//stats
	int coins, currentCoins;
	int points, currentPoints;
	int lives;
	double remainingTime;
};


#endif // _GAME_INCLUDE
