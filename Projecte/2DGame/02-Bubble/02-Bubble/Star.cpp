#include "Star.h"

#define SIZE_X 64
#define SIZE_Y 64

#define STAR_JUMP_ANGLE_STEP 2
#define STAR_JUMP_HEIGHT 128
enum States
{
	WAITING, JUMPING
};

void Star::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
    PickUp::init(tileMapPos, shaderProgram);

    spritesheet.loadFromFile("images/spritesItems.png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.5, 0.5), &spritesheet, &shaderProgram);
    sprite->setNumberAnimations(2);

    sprite->setAnimationSpeed(WAITING, 8);
	sprite->addKeyframe(WAITING, glm::vec2(0.5f, 0.f));

    sprite->setAnimationSpeed(JUMPING, 8);
	sprite->addKeyframe(JUMPING, glm::vec2(0.5f, 0.f));

    sprite->changeAnimation(WAITING);
    jumpAngle = 0;
    startY = 0;
}

void Star::update(int deltaTime) {
    sprite->update(deltaTime);

    if (sprite -> animation() == JUMPING) {
        jumpAngle += STAR_JUMP_ANGLE_STEP;
        if(jumpAngle >= 360) {
            jumpAngle = 0;
            position.y = startY;
        }
        else if(jumpAngle < 180) position.y = int(startY - STAR_JUMP_HEIGHT * sin(3.14159f * jumpAngle / 180.f));
        Entity::setPosition(glm::ivec2(position.x,position.y));
    }
    if (isPicked) {
        if (sprite -> animation() == WAITING) {
            sprite->changeAnimation(JUMPING);
            Entity::setPosition(glm::ivec2(position.x,position.y - 64));
            startY = position.y;
            jumpAngle = 0;
        }
        else isActive = false;   
        isPicked = false;
    }


}

int Star::pick() {
    isPicked = true;
    if (sprite -> animation() == WAITING) return 0;
    return 3;
}

bool Star::collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) 
{
    if (collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) {
		return true;
    }
    return false;
}

bool Star::collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size, int *posX) 
{
    if (collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) {
		return true;
    }
    return false;
}

bool Star::collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) 
{
    if (collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) {
		return true;
    }
    return false;
}

bool Star::collisionMoveUp(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) 
{
    if (collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) { 
		return true;
    }
    return false;
}

void Star::setPosition(const glm::vec2 &pos) {
    position = glm::ivec2(pos.x, pos.y);
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + position.x), float(tileMapDispl.y + position.y)));
}
