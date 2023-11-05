#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 288
#define FALL_STEP 16
#define ACCELERATION 0.01
#define DESACCELERATION 0.05
#define INI_VELOCITY 0.0
#define MAX_VELOCITY 8.0


#define SIZE_X 56
#define SIZE_Y 64


/* FALTA POR HACER: 

	- Que el spritesheet sea el mismo, pero 32 x 64, cuando coge una seta
	- Lo mismo al reves cuando recibe da�o 
	- Implemblocksar la logica de enemigos (animaciones, col, boxes...) 
	- Movimiblockso de Mario: aceleracion, la camara lo sigue, (A�adir sprite y) implemblocksar animacion freno, etc.
	- Crear clase para las blocksidades que faltan: Coin, Bandera y Koopa. 
	- Dise�ar el segundo nivel
	- Arreglar el movimiblockso de c�mara. 
	- Hacer que salte m�s ( salta 4 bloques en el juego original) 
	- Gestionar estados 
	- Rehacer sprites sin zooms  
	- Ampliar region que se ve
	- Acabar camara / animaciones ( cerrar cosas )


	COSAS VARIAS
	- Las animaciones de mario van bien todas
		�Falta implemblocksar que use las de saltar cuando salta
		�Falta implemblocksar las animaciones de Goomba, Koopa, Coin
	- Falta arreglar lo de la camara


*/
enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, GRAB_FLAG, ELIMINATE, JUMP_RIGHT, JUMP_LEFT
};
enum State {
	SMALL, BIG, STAR
};
enum Dir {
	LEFT, RIGHT, DOWN, UP
};

void Player::configureSmallSprite(ShaderProgram &shaderProgram) {
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
		
	sprite->changeAnimation(STAND_RIGHT);
}

bool Player::isBlockCollision(const int &dir) {
	int i = 0;
	bool someCollision = false;
	while (i < blocks.size()) {
		if (blocks[i] -> isEntityActive()) {
			bool collision = false;
			if (dir == LEFT) 
				collision = blocks[i] -> collisionMoveLeft(posPlayer, glm::ivec2(SIZE_X, SIZE_Y));
			else if (dir == RIGHT) 
				collision = blocks[i] -> collisionMoveRight(posPlayer, glm::ivec2(SIZE_X, SIZE_Y), &posPlayer.x);
			else if (dir == DOWN) 
				collision = blocks[i] -> collisionMoveDown(posPlayer, glm::ivec2(SIZE_X, SIZE_Y), &posPlayer.y);
			else if (dir == UP) 
				collision = blocks[i] -> collisionMoveUp(posPlayer, glm::ivec2(SIZE_X, SIZE_Y), &posPlayer.y);
			
			if (dir == UP && collision) {
				if (state == SMALL) blocks[i] -> hit();
				else blocks[i] -> destroy();
			}
			if (collision) someCollision = true;
		}
		++i;
	}
	return someCollision;
}

bool Player::isPickUpCollision(const int &dir) {
	int i = 0;
	while (i < pickUps.size()) {
		if (pickUps[i] -> isEntityActive()) {
			bool collision = false;
			if (dir == LEFT) 
				collision = pickUps[i] -> collisionMoveLeft(posPlayer, glm::ivec2(SIZE_X, SIZE_Y));
			else if (dir == RIGHT) 
				collision = pickUps[i] -> collisionMoveRight(posPlayer, glm::ivec2(SIZE_X, SIZE_Y), &posPlayer.x);
			else if (dir == DOWN) 
				collision = pickUps[i] -> collisionMoveDown(posPlayer, glm::ivec2(SIZE_X, SIZE_Y), &posPlayer.y);
			else if (dir == UP) 
				collision = pickUps[i] -> collisionMoveUp(posPlayer, glm::ivec2(SIZE_X, SIZE_Y), &posPlayer.y);
			
			if (collision) {
				int effect = pickUps[i] -> pick();
				//if (state == SMALL) state = BIG;
				//else state = SMALL;
			}
		}
		++i;
	}
	return false;
}

void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	inControl = true; 
	state = SMALL;
	bJumping = false;
	velocity = INI_VELOCITY;
	if (state == SMALL) configureSmallSprite(shaderProgram);
	tileMapDispl = tileMapPos;
	//sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT)/* and (inControl)*/)
	{
		if(sprite->animation() != MOVE_LEFT) {
			sprite->changeAnimation(MOVE_LEFT);
			velocity = INI_VELOCITY;
		}
		velocity = glm::min(velocity + ACCELERATION * deltaTime, MAX_VELOCITY);
		posPlayer.x -= int(velocity);

		isPickUpCollision(LEFT);
		bool collision = isBlockCollision(LEFT);
		if(posPlayer.x < minCoords.x || collision || map->collisionMoveLeft(posPlayer, glm::ivec2(SIZE_X, SIZE_Y)))
		{
			posPlayer.x += int(velocity);
			velocity = INI_VELOCITY;
			sprite->changeAnimation(STAND_LEFT);
		}

	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT) /* and inControl */)
	{
		if(sprite->animation() != MOVE_RIGHT){
			sprite->changeAnimation(MOVE_RIGHT);
			velocity = INI_VELOCITY;
		}

		velocity = glm::min(velocity + ACCELERATION * deltaTime, MAX_VELOCITY);
		posPlayer.x += int(velocity);

		isPickUpCollision(RIGHT);
		bool collision = isBlockCollision(RIGHT);
		if(collision || map->collisionMoveRight(posPlayer, glm::ivec2(SIZE_X, SIZE_Y), &posPlayer.x))
		{
			//posPlayer.x -= int(velocity);
			velocity = INI_VELOCITY;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else
	{
		velocity = glm::max(velocity - DESACCELERATION * deltaTime, INI_VELOCITY);
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
			if(jumpAngle > 90) {
				int i = 0;
				isPickUpCollision(DOWN);
				bool collision = isBlockCollision(DOWN);
				while (!collision && i < blocks.size()) {
					collision = blocks[i] -> collisionMoveDown(posPlayer, glm::ivec2(SIZE_X, SIZE_Y), &posPlayer.y);
					++i;
				}
				bJumping = !collision && !map->collisionMoveDown(posPlayer, glm::ivec2(SIZE_X, SIZE_Y), &posPlayer.y);
			} else {
				isPickUpCollision(UP);
				bool collision = isBlockCollision(UP);
				if (collision || map -> collisionMoveUp(posPlayer, glm::ivec2(SIZE_X, SIZE_Y), &posPlayer.y)) {
					bJumping = false;
				}
			}
		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		isPickUpCollision(DOWN);
		bool collision = isBlockCollision(DOWN);
		if(collision || map->collisionMoveDown(posPlayer, glm::ivec2(SIZE_X, SIZE_Y), &posPlayer.y))
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

void Player::setMinCoords(const glm::vec2 &coord) {
	minCoords = coord;
}

glm::ivec2 Player::getPosition() {
	return posPlayer;
}



