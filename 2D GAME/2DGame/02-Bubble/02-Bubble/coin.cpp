#include "Coin.h"

#define SIZE_X 32
#define SIZE_Y 32

enum States
{
	NORMAL
};

void Coin::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
    Entity::init(tileMapPos, shaderProgram);
    isHit = false;
    
    spritesheet.loadFromFile("images/spriteMonedas.png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
    sprite->setNumberAnimations(1);

    sprite->setAnimationSpeed(NORMAL, 8);
	sprite->addKeyframe(NORMAL, glm::vec2(0.f, 0.f));
    sprite->addKeyframe(NORMAL, glm::vec2(0.25, 0.f));
    sprite->addKeyframe(NORMAL, glm::vec2(0.f, 0.5));
    sprite->addKeyframe(NORMAL, glm::vec2(0.25, 0.5));
    sprite->changeAnimation(NORMAL);
}

void Coin::update(int deltaTime) {
    sprite->update(deltaTime);
    if (isHit) isActive = false;
}

bool Coin::collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) 
{
    if (collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) {
        isHit = true;
    }
    return false;
}

bool Coin::collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size, int *posX) 
{
    if (collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) {
        isHit = true;
    }
    return false;
}

bool Coin::collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) 
{
    if (collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) {
        isHit = true;
    }
    return false;
}

bool Coin::collisionMoveUp(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) 
{
    if (collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) { 
        isHit = true;
    }
    return false;
}
