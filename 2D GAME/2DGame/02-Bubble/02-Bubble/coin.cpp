#include "Coin.h"

#define SIZE_X 32
#define SIZE_Y 32

#define COIN_JUMP_ANGLE_STEP 8
#define COIN_JUMP_HEIGHT 256


enum States
{
	NORMAL, PICKED
};

void Coin::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
    PickUp::init(tileMapPos, shaderProgram);

    spritesheet.loadFromFile("images/spriteMonedas.png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
    sprite->setNumberAnimations(2);

    sprite->setAnimationSpeed(PICKED, 8);
	sprite->addKeyframe(PICKED, glm::vec2(0.f, 0.f));
    sprite->addKeyframe(PICKED, glm::vec2(0.25, 0.f));
    sprite->addKeyframe(PICKED, glm::vec2(0.f, 0.5));
    sprite->addKeyframe(PICKED, glm::vec2(0.25, 0.5));

    sprite->setAnimationSpeed(NORMAL, 8);
	sprite->addKeyframe(NORMAL, glm::vec2(0.f, 0.f));

    sprite->changeAnimation(NORMAL);
}

void Coin::update(int deltaTime) {
    sprite->update(deltaTime);

    if (sprite -> animation() == PICKED) {
        jumpAngle += COIN_JUMP_ANGLE_STEP;
		if(jumpAngle >= 180) {
            isActive = 0;
        }
		else {
            int y = int(originalY - COIN_JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
            Entity::setPosition(glm::ivec2(position.x,y));
        }
    }

    if (isPicked) {
        sprite->changeAnimation(PICKED);
        jumpAngle = 0;
        originalY = position.y;
        isPicked = false;
    }
}

int Coin::pick() {
    if (sprite -> animation() == PICKED) return 0;
    isPicked = true;
    return 1;
}

bool Coin::collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) 
{
    if (collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) {
		return true;
    }
    return false;
}

bool Coin::collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size, int *posX) 
{
    if (collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) {
		return true;
    }
    return false;
}

bool Coin::collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) 
{
    if (collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) {
		return true;
    }
    return false;
}

bool Coin::collisionMoveUp(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) 
{
    if (collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) { 
		return true;
    }
    return false;
}

void Coin::setPosition(const glm::vec2 &pos) {
    position = glm::ivec2(pos.x + 16, pos.y + 32);
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
}