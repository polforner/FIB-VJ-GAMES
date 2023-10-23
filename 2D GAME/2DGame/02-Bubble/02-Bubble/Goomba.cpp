#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Goomba.h"
#include "Game.h"


#define FALL_STEP 4

/*
enum GoombaAnims
{
	MOVE_LEFT, MOVE_RIGHT, ELIMINATED
};


void Goomba::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	facingRight = false;
	bJumping = false;
	spritesheet.loadFromFile("images/spriteGoomba.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	
	sprite->setAnimationSpeed(MOVE_RIGHT, 8);

	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posENEMY.x), float(tileMapDispl.y + posENEMY.y)));

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

	if (bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if (jumpAngle == 180)
		{
			bJumping = false;
			posENEMY.y = startY;
		}
		else
		{
			posENEMY.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if (jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posENEMY, glm::ivec2(32, 32), &posENEMY.y);
		}
	}
	else
	{
		posENEMY.y += FALL_STEP;
		if (map->collisionMoveDown(posENEMY, glm::ivec2(32, 32), &posENEMY.y))
		{
			if (Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				bJumping = true;
				jumpAngle = 0;
				startY = posENEMY.y;
			}
		}
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
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posENEMY.x), float(tileMapDispl.y + posENEMY.y)));
}

*/


