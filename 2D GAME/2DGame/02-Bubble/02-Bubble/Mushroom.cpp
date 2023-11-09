#include "Mushroom.h"

#define SIZE_X 64
#define SIZE_Y 64

enum States
{
	WAITING, MOVING_LEFT, MOVING_RIGHT
};

void Mushroom::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
    PickUp::init(tileMapPos, shaderProgram);

    spritesheet.loadFromFile("images/spritesItems.png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.5, 0.5), &spritesheet, &shaderProgram);
    sprite->setNumberAnimations(3);

    sprite->setAnimationSpeed(WAITING, 8);
	sprite->addKeyframe(WAITING, glm::vec2(0.f, 0.f));

    sprite->setAnimationSpeed(MOVING_LEFT, 8);
	sprite->addKeyframe(MOVING_LEFT, glm::vec2(0.f, 0.5));

    sprite->setAnimationSpeed(MOVING_RIGHT, 8);
	sprite->addKeyframe(MOVING_RIGHT, glm::vec2(0.f, 0.f));

    sprite->changeAnimation(WAITING);
}

void Mushroom::update(int deltaTime) {
    sprite->update(deltaTime);

    if (isPicked) {
        if (sprite -> animation() == WAITING) {
            sprite->changeAnimation(MOVING_RIGHT);
            Entity::setPosition(glm::ivec2(position.x,position.y - 64));
        }
        else isActive = false;   
        isPicked = false;
    }
}

int Mushroom::pick() {
    isPicked = true;
    if (sprite -> animation() == WAITING) return 0;
    return 2;
}

bool Mushroom::collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) 
{
    if (collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) {
		return true;
    }
    return false;
}

bool Mushroom::collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size, int *posX) 
{
    if (collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) {
		return true;
    }
    return false;
}

bool Mushroom::collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) 
{
    if (collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) {
		return true;
    }
    return false;
}

bool Mushroom::collisionMoveUp(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) 
{
    if (collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) { 
		return true;
    }
    return false;
}

void Mushroom::setPosition(const glm::vec2 &pos) {
    position = glm::ivec2(pos.x, pos.y);
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
}
