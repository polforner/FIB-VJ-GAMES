#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 192
#define FALL_STEP 8
#define ACCELERATION 1
#define INI_VELOCITY 2
#define MAX_VELOCITY 5




/* FALTA POR HACER: 

	- Que el spritesheet sea el mismo, pero 32 x 64, cuando coge una seta
	- Lo mismo al reves cuando recibe da�o 
	- Implementar la logica de enemigos (animaciones, col, boxes...) 
	- Movimiento de Mario: aceleracion, la camara lo sigue, (A�adir sprite y) implementar animacion freno, etc.
	- Crear clase para las entidades que faltan: Coin, Bandera y Koopa. 
	- Dise�ar el segundo nivel
	- Arreglar el movimiento de c�mara. 
	- Hacer que salte m�s ( salta 4 bloques en el juego original) 
	- Gestionar estados 
	- Rehacer sprites sin zooms  
	- Ampliar region que se ve
	- Acabar camara / animaciones ( cerrar cosas )


	COSAS VARIAS
	- Las animaciones de mario van bien todas
		�Falta implementar que use las de saltar cuando salta
		�Falta implementar las animaciones de Goomba, Koopa, Coin
	- Falta arreglar lo de la camara


*/
enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, GRAB_FLAG, ELIMINATE, JUMP_RIGHT, JUMP_LEFT
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	inControl = true; 
	isSmall = true;
	isStar = false;
	bJumping = false;
	velocity = INI_VELOCITY;
	spritesheet.loadFromFile("images/spriteMario.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.125, 0.125), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(8);
	
		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.125f, 0.f));
		
		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.125f, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.125f, 0.125f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.125f, 0.25f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.125f, 0.375f));
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.125f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.25f));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.375f));

		sprite->setAnimationSpeed(ELIMINATE, 8);
		sprite->addKeyframe(ELIMINATE, glm::vec2(0.f, 0.750f));

		sprite->setAnimationSpeed(JUMP_RIGHT, 8); 
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.f, 0.5f)); 

		sprite->setAnimationSpeed(JUMP_LEFT, 8);
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.125f, 0.5f)); 

		sprite->setAnimationSpeed(GRAB_FLAG, 8);
		sprite->addKeyframe(GRAB_FLAG, glm::vec2(0.f, 0.875f));

		
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT)/* and (inControl)*/)
	{
		if(sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		velocity = glm::min(INI_VELOCITY + ACCELERATION * deltaTime, MAX_VELOCITY);
		posPlayer.x -= velocity;
		if(map->collisionMoveLeft(posPlayer, glm::ivec2(64, 64)))
		{
			posPlayer.x += velocity;
			velocity = INI_VELOCITY;
			sprite->changeAnimation(STAND_LEFT);
		}

	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT) /* and inControl */)
	{
		if(sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		velocity = glm::min(INI_VELOCITY + ACCELERATION * deltaTime, MAX_VELOCITY);
		posPlayer.x += velocity;
		if(map->collisionMoveRight(posPlayer, glm::ivec2(64, 64), &posPlayer.x))
		{
			//posPlayer.x -= velocity;
			velocity = INI_VELOCITY;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN)/* and (inControl)*/)
	{
		if (sprite->animation() != ELIMINATE)
			sprite->changeAnimation(JUMP_RIGHT);
		

	}
	else
	{
		if(sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if(sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}
	
	if(bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if(jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
		}
		else
		{
			posPlayer.y = int(startY - JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
			if(jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y);
			else {
				if (map -> collisionMoveUp(posPlayer, glm::ivec2(64, 64), &posPlayer.y)) {
					bJumping = false;
				}
			}
		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		if(map->collisionMoveDown(posPlayer, glm::ivec2(64, 64), &posPlayer.y))
		{
			if(Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
		}
	}

	if (isEliminated) {
		inControl = false; 
		sprite->changeAnimation(ELIMINATE); 

		//codigo para que baje hasta abajo de la pantalla

	}
	
	//int mapWidth = map->getMapSize().x * map->getTileSize();
    //int mapHeight = map->getMapSize().y * map->getTileSize();
	//posPlayer.x = glm::clamp(posPlayer.x, 0, mapWidth - SCREEN_WIDTH);
    //posPlayer.y = glm::clamp(posPlayer.y, 0, mapHeight - SCREEN_HEIGHT);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

glm::ivec2 Player::getPosition() {
	return posPlayer;
}



