#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Goomba.h"
#include "Game.h"


#define FALL_STEP 4
#define ENEMY_SPEED 5


enum GoombaAnims
{
	MOVING, ELIMINATED
};
/*

void Goomba::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int dir) // Goomba
{
	direction = dir;
	spritesheet.loadFromFile("images/spriteGoomba.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.5, 0.5), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(MOVING, 8);
	sprite->addKeyframe(MOVING, glm::vec2(0.f, 0.f));
	sprite->addKeyframe(STAND_LEFT, glm::vec2(0.5f, 0.f));
	
	sprite->setAnimationSpeed(ELIMINATED, 8);
	sprite->addKeyframe(ELIMINATED, glm::vec2(0.f, 0.5f));

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x + ENEMY_SPEED * dist), float(tileMapDispl.y + posEnemy.y)));

}

void Goomba::update(int deltaTime)
{
	sprite->update(deltaTime);
	else
	{
		if (sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}

	if(chocaVsPared){
		displ *= -1; 
	}

	if(isEliminated){//hay una funcion en enemy que es eliminate() la cual pasa de eliminated false a true
		sprite->changeAnimation(ELIMINATED); 
		displ = 0; 
		//wait 1.25 seconds
		//dejaDeRenderizarlo()

	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posENEMY.x), float(tileMapDispl.y + posENEMY.y)));
}

void Goomba::render()
{
	sprite->render();
}

void Goomba::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Goomba::setPosition(const glm::vec2 &pos)
{
	posENEMY = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posENEMY.x + ENEMY_SPEED * dist), float(tileMapDispl.y + posENEMY.y)));
}

*/


