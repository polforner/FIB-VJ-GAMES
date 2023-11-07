#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 300
#define FALL_STEP 16
#define ACCELERATION 0.01
#define DESACCELERATION 0.05
#define INI_VELOCITY 0.0
#define MAX_VELOCITY 8.0


#define SIZE_X 56
#define SIZE_Y 128


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
	SMALL, BIG, SMALL_STAR, BIG_STAR
};
enum Dir {
	LEFT, RIGHT, DOWN, UP
};

void Player::configureSmallSprite(ShaderProgram &shaderProgram) {
	spritesheet.loadFromFile("images/spriteMario.png", TEXTURE_PIXEL_FORMAT_RGBA);
	smallSprite = Sprite::createSprite(glm::ivec2(64,64), glm::vec2(0.125, 0.125), &spritesheet, &shaderProgram);
	smallSprite->setNumberAnimations(8);
	
	smallSprite->setAnimationSpeed(STAND_LEFT, 8);
	smallSprite->addKeyframe(STAND_LEFT, glm::vec2(0.125f, 0.f));
		
	smallSprite->setAnimationSpeed(STAND_RIGHT, 8);
	smallSprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));
		
	smallSprite->setAnimationSpeed(MOVE_LEFT, 8);
	smallSprite->addKeyframe(MOVE_LEFT, glm::vec2(0.125f, 0.f));
	smallSprite->addKeyframe(MOVE_LEFT, glm::vec2(0.125f, 0.125f));
	smallSprite->addKeyframe(MOVE_LEFT, glm::vec2(0.125f, 0.25f));
	smallSprite->addKeyframe(MOVE_LEFT, glm::vec2(0.125f, 0.375f));
		
	smallSprite->setAnimationSpeed(MOVE_RIGHT, 8);
	smallSprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));
	smallSprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.125f));
	smallSprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.25f));
	smallSprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.375f));

	smallSprite->setAnimationSpeed(ELIMINATE, 8);
	smallSprite->addKeyframe(ELIMINATE, glm::vec2(0.f, 0.750f));

	smallSprite->setAnimationSpeed(JUMP_RIGHT, 8); 
	smallSprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.f, 0.5f)); 

	smallSprite->setAnimationSpeed(JUMP_LEFT, 8);
	smallSprite->addKeyframe(JUMP_LEFT, glm::vec2(0.125f, 0.5f)); 

	smallSprite->setAnimationSpeed(GRAB_FLAG, 8);
	smallSprite->addKeyframe(GRAB_FLAG, glm::vec2(0.f, 0.875f));
		
	smallSprite->changeAnimation(STAND_RIGHT);
}

void Player::configureBigSprite(ShaderProgram &shaderProgram) {
	spritesheet.loadFromFile("images/spriteMario.png", TEXTURE_PIXEL_FORMAT_RGBA);
	bigSprite = Sprite::createSprite(glm::ivec2(64,128), glm::vec2(0.125, 0.25), &spritesheet, &shaderProgram);
	bigSprite->setNumberAnimations(8);
	
	bigSprite->setAnimationSpeed(STAND_LEFT, 8);
	bigSprite->addKeyframe(STAND_LEFT, glm::vec2(0.625f, 0.f));
		
	bigSprite->setAnimationSpeed(STAND_RIGHT, 8);
	bigSprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25f, 0.f));
		
	bigSprite->setAnimationSpeed(MOVE_LEFT, 8);
	bigSprite->addKeyframe(MOVE_LEFT, glm::vec2(0.625f, 0.f));
	bigSprite->addKeyframe(MOVE_LEFT, glm::vec2(0.625f, 0.25f));
	bigSprite->addKeyframe(MOVE_LEFT, glm::vec2(0.625f, 0.5f));
	bigSprite->addKeyframe(MOVE_LEFT, glm::vec2(0.625f, 0.75f));
		
	bigSprite->setAnimationSpeed(MOVE_RIGHT, 8);
	bigSprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25f, 0.f));
	bigSprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25f, 0.25f));
	bigSprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25f, 0.5f));
	bigSprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25f, 0.75f));

	bigSprite->setAnimationSpeed(ELIMINATE, 8);
	bigSprite->addKeyframe(ELIMINATE, glm::vec2(0.f, 0.750f));

	bigSprite->setAnimationSpeed(JUMP_RIGHT, 8); 
	bigSprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.375f, 0.f)); 

	bigSprite->setAnimationSpeed(JUMP_LEFT, 8);
	bigSprite->addKeyframe(JUMP_LEFT, glm::vec2(0.5f, 0.f)); 

	bigSprite->setAnimationSpeed(GRAB_FLAG, 8);
	bigSprite->addKeyframe(GRAB_FLAG, glm::vec2(0.375f, 0.25f));
		
	bigSprite->changeAnimation(STAND_RIGHT);
}

void Player::configureSmallStarSprite(ShaderProgram &shaderProgram) {
	spritesheet.loadFromFile("images/spriteStarMario.png", TEXTURE_PIXEL_FORMAT_RGBA);
	smallStarSprite = Sprite::createSprite(glm::ivec2(64,64), glm::vec2(0.125, 0.125), &spritesheet, &shaderProgram);
	smallStarSprite->setNumberAnimations(8);
	
	smallStarSprite->setAnimationSpeed(STAND_LEFT, 8);
	smallStarSprite->addKeyframe(STAND_LEFT, glm::vec2(0.125f, 0.f));
		
	smallStarSprite->setAnimationSpeed(STAND_RIGHT, 8);
	smallStarSprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, 0.f));
		
	smallStarSprite->setAnimationSpeed(MOVE_LEFT, 8);
	smallStarSprite->addKeyframe(MOVE_LEFT, glm::vec2(0.125f, 0.f));
	smallStarSprite->addKeyframe(MOVE_LEFT, glm::vec2(0.125f, 0.125f));
	smallStarSprite->addKeyframe(MOVE_LEFT, glm::vec2(0.125f, 0.25f));
	smallStarSprite->addKeyframe(MOVE_LEFT, glm::vec2(0.125f, 0.375f));
		
	smallStarSprite->setAnimationSpeed(MOVE_RIGHT, 8);
	smallStarSprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.f));
	smallStarSprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.125f));
	smallStarSprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.25f));
	smallStarSprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.375f));

	smallStarSprite->setAnimationSpeed(ELIMINATE, 8);
	smallStarSprite->addKeyframe(ELIMINATE, glm::vec2(0.f, 0.750f));

	smallStarSprite->setAnimationSpeed(JUMP_RIGHT, 8); 
	smallStarSprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.f, 0.5f)); 

	smallStarSprite->setAnimationSpeed(JUMP_LEFT, 8);
	smallStarSprite->addKeyframe(JUMP_LEFT, glm::vec2(0.125f, 0.5f)); 

	smallStarSprite->setAnimationSpeed(GRAB_FLAG, 8);
	smallStarSprite->addKeyframe(GRAB_FLAG, glm::vec2(0.f, 0.875f));
		
	smallStarSprite->changeAnimation(STAND_RIGHT);
}

void Player::configureBigStarSprite(ShaderProgram &shaderProgram) {
	spritesheet.loadFromFile("images/spriteStarMario.png", TEXTURE_PIXEL_FORMAT_RGBA);
	bigStarSprite = Sprite::createSprite(glm::ivec2(64,128), glm::vec2(0.125, 0.25), &spritesheet, &shaderProgram);
	bigStarSprite->setNumberAnimations(8);
	
	bigStarSprite->setAnimationSpeed(STAND_LEFT, 8);
	bigStarSprite->addKeyframe(STAND_LEFT, glm::vec2(0.625f, 0.f));
		
	bigStarSprite->setAnimationSpeed(STAND_RIGHT, 8);
	bigStarSprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25f, 0.f));
		
	bigStarSprite->setAnimationSpeed(MOVE_LEFT, 8);
	bigStarSprite->addKeyframe(MOVE_LEFT, glm::vec2(0.625f, 0.f));
	bigStarSprite->addKeyframe(MOVE_LEFT, glm::vec2(0.625f, 0.25f));
	bigStarSprite->addKeyframe(MOVE_LEFT, glm::vec2(0.625f, 0.5f));
	bigStarSprite->addKeyframe(MOVE_LEFT, glm::vec2(0.625f, 0.75f));
		
	bigStarSprite->setAnimationSpeed(MOVE_RIGHT, 8);
	bigStarSprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25f, 0.f));
	bigStarSprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25f, 0.25f));
	bigStarSprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25f, 0.5f));
	bigStarSprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25f, 0.75f));

	bigStarSprite->setAnimationSpeed(ELIMINATE, 8);
	bigStarSprite->addKeyframe(ELIMINATE, glm::vec2(0.f, 0.750f));

	bigStarSprite->setAnimationSpeed(JUMP_RIGHT, 8); 
	bigStarSprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.375f, 0.f)); 

	bigStarSprite->setAnimationSpeed(JUMP_LEFT, 8);
	bigStarSprite->addKeyframe(JUMP_LEFT, glm::vec2(0.5f, 0.f)); 

	bigStarSprite->setAnimationSpeed(GRAB_FLAG, 8);
	bigStarSprite->addKeyframe(GRAB_FLAG, glm::vec2(0.375f, 0.25f));
		
	bigStarSprite->changeAnimation(STAND_RIGHT);
}	

bool Player::isBlockCollision(const int &dir) {
	int i = 0;
	bool someCollision = false;
	glm::ivec2 constPosition = posPlayer;
	int numBlocks = blocks.size();
	while (i < numBlocks) {
		if (blocks[i] -> isEntityActive()) {
			bool collision = false;
			if (dir == LEFT) 
				collision = blocks[i] -> collisionMoveLeft(constPosition, size);
			else if (dir == RIGHT) 
				collision = blocks[i] -> collisionMoveRight(constPosition, size, &posPlayer.x);
			else if (dir == DOWN) 
				collision = blocks[i] -> collisionMoveDown(constPosition, size, &posPlayer.y);
			else if (dir == UP) 
				collision = blocks[i] -> collisionMoveUp(constPosition, size, &posPlayer.y);
			
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
	int numPickUps = pickUps.size();
	while (i < numPickUps) {
		if (pickUps[i] -> isEntityActive()) {
			bool collision = false;
			if (dir == LEFT) 
				collision = pickUps[i] -> collisionMoveLeft(posPlayer, size);
			else if (dir == RIGHT) 
				collision = pickUps[i] -> collisionMoveRight(posPlayer, size, &posPlayer.x);
			else if (dir == DOWN) 
				collision = pickUps[i] -> collisionMoveDown(posPlayer, size, &posPlayer.y);
			else if (dir == UP) 
				collision = pickUps[i] -> collisionMoveUp(posPlayer, size, &posPlayer.y);
			
			if (collision) {
				int effect = pickUps[i] -> pick();
				if (effect == 1) {
					++coins;
					score += 100;
				}
				else if (effect == 2) {
					if (state == SMALL) {
						state = BIG;
						changeState = true;
					}
					else score += 1000;
				}
				else if (effect == 3) {
					if (state == SMALL) {
						state = SMALL_STAR;
						changeState = true;
					}
					else if (state == BIG) {
						state = BIG_STAR;
						changeState = true;
					}
					else score += 1000;
				}
			}
		}
		++i;
	}
	return false;
}

bool Player::isEnemyCollision(const int &dir) {
	int i = 0;
	bool someCollision = false;
	glm::ivec2 constPosition = posPlayer;
	int numEnemies = enemies.size();
	while (i < numEnemies) {
		if (enemies[i] -> isEntityActive()) {
			bool collision = false;
			if (dir == LEFT) 
				collision = enemies[i] -> collisionMoveLeft(constPosition, size);
			else if (dir == RIGHT) 
				collision = enemies[i] -> collisionMoveRight(constPosition, size, &posPlayer.x);
			else if (dir == DOWN) 
				collision = enemies[i] -> collisionMoveDown(constPosition, size, &posPlayer.y);
			else if (dir == UP) 
				collision = enemies[i] -> collisionMoveUp(constPosition, size, &posPlayer.y);
			
			if (collision) {
				if (dir == DOWN) enemies[i] -> hit();
				else {
					hit();
					collision = false;
				}
			}
			if (collision) someCollision = true;
		}
		++i;
	}
	return someCollision;	
}

void Player::hit() {
	isEliminated = true;
}

void Player::configureSprites(ShaderProgram &shaderProgram) {
	configureSmallSprite(shaderProgram);
	configureBigSprite(shaderProgram);
	configureSmallStarSprite(shaderProgram);
	configureBigStarSprite(shaderProgram);
}

void Player::selectSprite() {
	glm::ivec2 lastSize = size;
	int lastAnimation = sprite -> animation();
	if (state == SMALL) {
		spritesheet.loadFromFile("images/spriteMario.png", TEXTURE_PIXEL_FORMAT_RGBA);
		size = glm::ivec2(64,64);
		sprite = smallSprite;
	}
	else if (state == BIG) {
		spritesheet.loadFromFile("images/spriteMario.png", TEXTURE_PIXEL_FORMAT_RGBA);
		size = glm::ivec2(64,128);
		sprite = bigSprite;
	}
	else if (state == SMALL_STAR) {
		spritesheet.loadFromFile("images/spriteStarMario.png", TEXTURE_PIXEL_FORMAT_RGBA);
		size = glm::ivec2(64,64);
		sprite = smallStarSprite;
	}
	else if (state == BIG_STAR) {
		spritesheet.loadFromFile("images/spriteStarMario.png", TEXTURE_PIXEL_FORMAT_RGBA);
		size = glm::ivec2(64,128);
		sprite = bigStarSprite;
	}
	sprite->changeAnimation(lastAnimation);
	setPosition(posPlayer + (lastSize - size));
}

void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	inControl = true; 
	state = SMALL;
	changeState = false;
	bJumping = false;
	velocity = INI_VELOCITY;
	configureSprites(shaderProgram);
	sprite = smallSprite;
	selectSprite();
	tileMapDispl = tileMapPos;
}

void Player::update(int deltaTime)
{
	if(Game::instance().getKey('m')) {
		changeState = true;
		state = BIG;
	}
	sprite->update(deltaTime);
	if (sprite -> animation() == ELIMINATE){
		jumpAngle += 2;
		if(jumpAngle >= 180) posPlayer.y += FALL_STEP;
		else posPlayer.y = int(startY - JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
	}
	else {
		if(Game::instance().getSpecialKey(GLUT_KEY_LEFT)/* and (inControl)*/) {
			if(sprite->animation() != MOVE_LEFT) {
				sprite->changeAnimation(MOVE_LEFT);
				velocity = INI_VELOCITY;
			}
			velocity = glm::min(velocity + ACCELERATION * deltaTime, MAX_VELOCITY);
			posPlayer.x -= int(velocity);

			isPickUpCollision(LEFT);
			bool collision = isBlockCollision(LEFT);
			if(posPlayer.x < minCoords.x || collision || map->collisionMoveLeft(posPlayer, size))
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
			if(collision || map->collisionMoveRight(posPlayer, size, &posPlayer.x))
			{
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
					isPickUpCollision(DOWN);
					bool collision = isBlockCollision(DOWN);
					bJumping = !collision && !map->collisionMoveDown(posPlayer, size, &posPlayer.y);
					collision = isEnemyCollision(DOWN);
					if (collision) {
						bJumping = true;
						jumpAngle = 0;
						startY = posPlayer.y;
					}
				} else {
					isPickUpCollision(UP);
					bool collision = isBlockCollision(UP);
					if (collision || map -> collisionMoveUp(posPlayer, size, &posPlayer.y)) {
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
			
			if(collision || map->collisionMoveDown(posPlayer, size, &posPlayer.y))
			{
				if(Game::instance().getSpecialKey(GLUT_KEY_UP))
				{
					bJumping = true;
					jumpAngle = 0;
					startY = posPlayer.y;
				}
			} else if (collision = isEnemyCollision(DOWN)) {
					bJumping = true;
					jumpAngle = 0;
					startY = posPlayer.y;			
			}
		}
		isEnemyCollision(RIGHT);
		if (isEliminated) {
			inControl = false; 
			sprite->changeAnimation(ELIMINATE); 
			jumpAngle = 0;
			startY = posPlayer.y;
			isEliminated = false;
		}
		if (changeState) {
			selectSprite();
			changeState = false;
		}
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



