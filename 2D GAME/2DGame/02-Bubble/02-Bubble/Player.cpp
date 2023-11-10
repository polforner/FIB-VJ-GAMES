#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 300
#define FALL_STEP 16

#define ACCELERATION 0.005
#define DECELERATION 0.1

#define INI_VELOCITY 2.0
#define MAX_VELOCITY 5.0


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
	SMALL, BIG,
};

enum Dir {
	LEFT, RIGHT, DOWN, UP
};

void Player::configureSprites(ShaderProgram &shaderProgram) {
	//Configure SMALL
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

	//Configure BIG
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
	bigSprite->addKeyframe(GRAB_FLAG, glm::vec2(0.f, 0.875f));
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
				if (!isStar && state == SMALL) blocks[i] -> hit();
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
					Game::instance().addCoin();
				}
				else if (effect == 2) {
					if (state == SMALL) {
						state = BIG;
						isSwaping = true;
						if(!isStar) timer = 0;
						changeState = true;
					}
					else Game::instance().addPoints();
				}
				else if (effect == 3) {
					if (state == SMALL) {
						isStar = true;
						changeState = true;
						timer = 0;
					}
					else if (state == BIG) {
						isStar = true;
						changeState = true;
						timer = 0;
					}
					else Game::instance().addPoints();
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
				if (isStar || dir == DOWN) enemies[i] -> hit();
				else {
					if(!isSwaping) hit();
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
	if (state == BIG) {
		state = SMALL;
		isSwaping = true;
		timer = 0;
		changeState = true;
	}
	else if (state == SMALL) isEliminated = true;
}

void Player::selectSprite() {
	glm::ivec2 lastSize = size;
	int lastAnimation = sprite -> animation();
	//check states
	if (state == SMALL) {
		spritesheet.loadFromFile("images/spriteMario.png", TEXTURE_PIXEL_FORMAT_RGBA);
		size = glm::ivec2(56,64);
		sprite = smallSprite;
	}
	else if (state == BIG) {
		spritesheet.loadFromFile("images/spriteMario.png", TEXTURE_PIXEL_FORMAT_RGBA);
		size = glm::ivec2(63,128);
		sprite = bigSprite;
	}
	//check status
	if (isStar) {
		spritesheet.loadFromFile("images/spriteStarMario.png", TEXTURE_PIXEL_FORMAT_RGBA);
	}
	if (isSwaping) {
		if (timer % 250 < 125) {
				spritesheet.loadFromFile("images/spriteMario.png", TEXTURE_PIXEL_FORMAT_RGBA);
				size = glm::ivec2(56,64);
				sprite = smallSprite;
		} 
		else {
				spritesheet.loadFromFile("images/spriteMario.png", TEXTURE_PIXEL_FORMAT_RGBA);
				size = glm::ivec2(63,128);
				sprite = bigSprite;
		}
	}

	sprite->changeAnimation(lastAnimation);
	setPosition(posPlayer + (lastSize - size));
}

void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	inControl = true;
	isSwaping = false;
	isStar = false;
	bJumping = false;
	changeState = false;
	isRunning = false;
	flagGrabbed = false;
	win = false;
	configureSprites(shaderProgram);
	
	state = SMALL;
	spritesheet.loadFromFile("images/spriteMario.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = smallSprite;
	sprite -> changeAnimation(STAND_RIGHT);
	size = glm::ivec2(56,64);
	
	velocity = INI_VELOCITY;
	tileMapDispl = tileMapPos;
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	timer += deltaTime;
	
	if(!isSwaping && Game::instance().getKey('m')) {
		changeState = true;
		timer = 0;
		isSwaping = true;
		state = BIG;
	}
	if(Game::instance().getKey('g')) {
		changeState = true;
		timer = 0;
		isStar = true;
	}
	if (Game::instance().getRemainingTime() == 0) isEliminated = true;
	isRunning = Game::instance().getKey('x');
	if (isStar) isRunning = true;
if(inControl) {
		if(bJumping)
		{
			jumpAngle += JUMP_ANGLE_STEP;

			posPlayer.y = int(startY - JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
			if(jumpAngle > 90) {
				bJumping = !isBlockCollision(DOWN) && !map->collisionMoveDown(posPlayer, size, &posPlayer.y);
				if (isEnemyCollision(DOWN)) {
					bJumping = true;
					jumpAngle = 0;
					startY = posPlayer.y;
				}
			} else {
				isPickUpCollision(UP);
				if (isBlockCollision(UP) || map -> collisionMoveUp(posPlayer, size, &posPlayer.y)) {
					bJumping = false;
				}
			}
			if(jumpAngle >= 180)
			{
				bJumping = false;
				posPlayer.y = startY;
			}
		}
		else
		{
			posPlayer.y += FALL_STEP;
			
			if(isBlockCollision(DOWN) || map->collisionMoveDown(posPlayer, size, &posPlayer.y))
			{
				if(Game::instance().getSpecialKey(GLUT_KEY_UP))
				{
					bJumping = true;
					jumpAngle = 0;
					startY = posPlayer.y;
					Game::instance().playMusic("jump");
				}
			} else if (isEnemyCollision(DOWN)) {
					bJumping = true;
					jumpAngle = 0;
					startY = posPlayer.y;	
			}
			
			if (posPlayer.y + size.y >= ((map -> getMapSize()).y) * (map -> getTileSize())) isEliminated = true;
		}

		if(Game::instance().getSpecialKey(GLUT_KEY_LEFT)) {
			if(sprite->animation() != MOVE_LEFT) {
				sprite->changeAnimation(MOVE_LEFT);
				velocity = -INI_VELOCITY;
			}
			if (isRunning) velocity = glm::max(-MAX_VELOCITY, velocity - ACCELERATION * deltaTime);
			else velocity = glm::min(-INI_VELOCITY, velocity + DECELERATION * deltaTime);
			
			posPlayer.x += int(velocity);
			if (posPlayer.x < minCoords.x) posPlayer.x -= int(velocity);
			if(isBlockCollision(LEFT) || isEnemyCollision(LEFT) 
			|| map->collisionMoveLeft(posPlayer, size, &posPlayer.x)) {
				velocity = -INI_VELOCITY;
				sprite->changeAnimation(STAND_LEFT);
			}
		}
		else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT)) {
			if(sprite->animation() != MOVE_RIGHT){
				sprite->changeAnimation(MOVE_RIGHT);
				velocity = INI_VELOCITY;
			}
			if (isRunning) velocity = glm::min(MAX_VELOCITY, velocity + ACCELERATION * deltaTime);
			else velocity = glm::max(INI_VELOCITY, velocity - DECELERATION * deltaTime);
			
			posPlayer.x += int(velocity);
			if (posPlayer.x > (Game::instance().flagPosition()).x 
			&& posPlayer.y < (Game::instance().flagPosition()).y ) flagGrabbed = true;
			if((posPlayer.x > ((map -> getMapSize()).x * map -> getTileSize())) || isBlockCollision(RIGHT) 
			|| isEnemyCollision(RIGHT) || map->collisionMoveRight(posPlayer, size, &posPlayer.x))
			{
				velocity = INI_VELOCITY;
				sprite->changeAnimation(STAND_RIGHT);
			}
		}
		else
		{
			//velocity = glm::max(velocity - DESACCELERATION * deltaTime, INI_VELOCITY);
			if(sprite->animation() == MOVE_LEFT) sprite->changeAnimation(STAND_LEFT);
			else if(sprite->animation() == MOVE_RIGHT) sprite->changeAnimation(STAND_RIGHT);

			if (sprite -> animation() == LEFT) isEnemyCollision(LEFT);
			else isEnemyCollision(RIGHT);
		}
		isPickUpCollision(DOWN);
	}

	if (sprite -> animation() == ELIMINATE){
		jumpAngle += 2;
		if(jumpAngle >= 180) posPlayer.y += FALL_STEP;
		else posPlayer.y = int(startY - JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
		if (timer > 5000) Game::instance().imDead();
	}
	else if (sprite -> animation() == GRAB_FLAG){
		if (posPlayer.y < (Game::instance().flagPosition()).y) posPlayer.y += 1;
		else {
			sprite -> changeAnimation(MOVE_RIGHT);
			posPlayer.x += 64;
			posPlayer.y += 64;
			win = true;
			timer = 0;
		}
	} 
	else {
		if (isEliminated) {
			inControl = false;
			isSwaping = false;
			isStar = false;
			state = SMALL;
			changeState = true;
			sprite->changeAnimation(ELIMINATE); 
			jumpAngle = 0;
			startY = posPlayer.y;
			Game::instance().playMusic("die");
			isEliminated = false;
		}
		if (flagGrabbed) {
			inControl = false;
			timer = 0;
			posPlayer.x = (Game::instance().flagPosition()).x + 64;
			state = SMALL;
			changeState = true;
			if (posPlayer.y < (Game::instance().flagPosition()).y - 5 * 64) posPlayer.y = (Game::instance().flagPosition()).y - 5 * 64;
			sprite -> changeAnimation(GRAB_FLAG);
			Game::instance().playMusic("flag");
			flagGrabbed = false;
		}
		if (win) {
			if (timer < 2000) posPlayer.x += 1;
			else if (timer < 5000) sprite -> changeAnimation(STAND_RIGHT);
			else Game::instance().win();
		}
		if (isSwaping) {
			if (timer == 0) {
				if (state == BIG) Game::instance().playMusic("mushroom");
				else Game::instance().playMusic("takeDmg");
			}
			isSwaping = !(timer > 1000);
			changeState = true;
		}
		if (isStar) {
			isStar= !(timer > 10000);
			if(!isStar) {
				changeState = true;
				isRunning = false;
			}
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



