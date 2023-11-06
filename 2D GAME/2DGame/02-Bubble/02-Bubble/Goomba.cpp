#include "Goomba.h"

#define SIZE_X 64
#define SIZE_Y 64

enum States
{
	CRUSHED, MOVING_LEFT, MOVING_RIGHT
};

void Goomba::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
    Enemy::init(tileMapPos, shaderProgram);

    spritesheet.loadFromFile("images/sporiteGoomba.png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.5, 0.5), &spritesheet, &shaderProgram);
    sprite->setNumberAnimations(3);

    sprite->setAnimationSpeed(CRUSHED, 8);
	sprite->addKeyframe(CRUSHED, glm::vec2(0.f, 0.5f));

    sprite->setAnimationSpeed(MOVING_LEFT, 8);
	sprite->addKeyframe(MOVING_LEFT, glm::vec2(0.5f, 0.f));

    sprite->setAnimationSpeed(MOVING_RIGHT, 8);
	sprite->addKeyframe(MOVING_RIGHT, glm::vec2(0.f, 0.f));

    sprite->changeAnimation(MOVING_LEFT);
}

void Goomba::update(int deltaTime) {
    sprite->update(deltaTime);
}

bool Goomba::collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) 
{
    if (collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) {
		return true;
    }
    return false;
}

bool Goomba::collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size, int *posX) 
{
    if (collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) {
		return true;
    }
    return false;
}

bool Goomba::collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) 
{
    if (collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) {
		return true;
    }
    return false;
}

bool Goomba::collisionMoveUp(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) 
{
    if (collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) { 
		return true;
    }
    return false;
}
