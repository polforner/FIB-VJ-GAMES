#include "Brick.h"

#define SIZE_X 64
#define SIZE_Y 64

enum States
{
	NORMAL, BREAKING, BREAKED
};

void Brick::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
    Entity::init(tileMapPos, shaderProgram);
    isHit = false;
    isDestroyed = false;
    
    spritesheet.loadFromFile("images/spriteBlockLv1.png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.5, 0.5), &spritesheet, &shaderProgram);
    sprite->setNumberAnimations(3);

    sprite->setAnimationSpeed(NORMAL, 8);
	sprite->addKeyframe(NORMAL, glm::vec2(0.f, 0.f));

    sprite->setAnimationSpeed(BREAKING, 8);
	sprite->addKeyframe(BREAKING, glm::vec2(0.5, 0.f));

    sprite->setAnimationSpeed(BREAKED, 8);
	sprite->addKeyframe(BREAKED, glm::vec2(0.f, 0.5));
    sprite->changeAnimation(NORMAL);
}

void Brick::update(int deltaTime) {
    sprite->update(deltaTime);
    if (isHit) sprite->changeAnimation(BREAKED);
}

bool Brick::collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) 
{
    if (collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) {
        return true;
    }
    return false;
}

bool Brick::collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size, int *posX) 
{
    if (collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) {
        *posX = position.x - SIZE_X;
        return true;
    }
    return false;
}

bool Brick::collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) 
{
    if (collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) {
        *posY = position.y - SIZE_Y;
        return true;
    }
    return false;
}

bool Brick::collisionMoveUp(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) 
{
    if (collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) { 
        *posY = position.y + SIZE_Y;
        isHit = true;
        return true;
    }
    return false;
}