#include "QuestionMark.h"

#define SIZE_X 64
#define SIZE_Y 64

enum States
{
	NORMAL, BREAKED
};

void QuestionMark::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
    Block::init(tileMapPos, shaderProgram);
    isHit = false;
    isDestroyed = false;
    
    spritesheet.loadFromFile("images/spriteLoot.png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.5, 0.5), &spritesheet, &shaderProgram);
    sprite->setNumberAnimations(2);

    sprite->setAnimationSpeed(NORMAL, 8);
	sprite->addKeyframe(NORMAL, glm::vec2(0.f, 0.f));
    sprite->addKeyframe(NORMAL, glm::vec2(0.5, 0.f));
    sprite->addKeyframe(NORMAL, glm::vec2(0.f, 0.5));

    sprite->setAnimationSpeed(BREAKED, 8);
	sprite->addKeyframe(BREAKED, glm::vec2(0.5, 0.5));

    sprite->changeAnimation(NORMAL);
}

void QuestionMark::update(int deltaTime) {
    sprite->update(deltaTime);
    if (isHit || isDestroyed) sprite->changeAnimation(BREAKED);
}

void QuestionMark::hit(){
    isHit = true;
}

void QuestionMark::destroy() {
    isDestroyed = true;
}

bool QuestionMark::collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) 
{
    if (collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) {
        return true;
    }
    return false;
}

bool QuestionMark::collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size, int *posX)
{
    if (collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) {
        *posX = position.x - SIZE_X;
        return true;
    }
    return false;
}

bool QuestionMark::collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) 
{
    if (collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) {
        *posY = position.y - size.y;
        return true;
    }
    return false;
}

bool QuestionMark::collisionMoveUp(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY)
{
    if (collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) { 
        *posY = position.y + SIZE_Y;
        return true;
    }
    return false;
}
