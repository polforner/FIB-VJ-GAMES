#include "Goomba.h"

#define SIZE_X 60
#define SIZE_Y 64

#define GOOMBA_FALL_STEP 2
#define GOOMBA_VELOCITY 1
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
    sprite->addKeyframe(MOVING_LEFT, glm::vec2(0.f, 0.f));

    sprite->setAnimationSpeed(MOVING_RIGHT, 8);
	sprite->addKeyframe(MOVING_RIGHT, glm::vec2(0.f, 0.f));
    sprite->addKeyframe(MOVING_RIGHT, glm::vec2(0.5f, 0.f));

    sprite->changeAnimation(MOVING_LEFT);
}

void Goomba::update(int deltaTime) {
    sprite->update(deltaTime);
    if (isHit) {
        sprite -> changeAnimation(CRUSHED);
        deadTime = 0;
        isHit = false;
    }
    else if (sprite -> animation() == CRUSHED) {
        deadTime += deltaTime;
        if (deadTime > 100) isActive = false;
    }
    else {
        position.y += GOOMBA_FALL_STEP;
        int i = 0;
        bool collision = map->collisionMoveDown(position, glm::ivec2(SIZE_X,SIZE_Y), &position.y);
        while (!collision && i < blocks.size()) {
            if (blocks[i] -> isEntityActive()) collision = blocks[i] -> collisionMoveDown(position, glm::ivec2(SIZE_X,SIZE_Y), &position.y);
            ++i;
        }
        if (position.y + SIZE_Y >= ((map -> getMapSize()).y) * (map -> getTileSize())) isActive = false;

        if (sprite ->animation() == MOVING_LEFT) {
            position.x -= GOOMBA_VELOCITY;
            bool collision = map->collisionMoveLeft(position, glm::ivec2(SIZE_X,SIZE_Y), &position.x);
            while (!collision && i < blocks.size()) {
                if (blocks[i] -> isEntityActive()) collision = blocks[i] -> collisionMoveLeft(position, glm::ivec2(SIZE_X,SIZE_Y));
                ++i;
            }

            if (collision) {
                sprite -> changeAnimation(MOVING_RIGHT);
            }
        }
        else {
            position.x += GOOMBA_VELOCITY;
            bool collision = map->collisionMoveRight(position, glm::ivec2(SIZE_X,SIZE_Y), &position.x);
            while (!collision && i < blocks.size()) {
                if (blocks[i] -> isEntityActive()) collision = blocks[i] -> collisionMoveRight(position, glm::ivec2(SIZE_X,SIZE_Y),&position.x);
                ++i;
            }

            if (collision) {
                sprite -> changeAnimation(MOVING_LEFT);
            }  
        }
    }
    Entity::setPosition(position);
}

bool Goomba::collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) 
{
    if (!isHit && sprite -> animation() != CRUSHED && collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) {
		return true;
    }
    return false;
}

bool Goomba::collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size, int *posX) 
{
    if (!isHit && sprite -> animation() != CRUSHED && collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) {
		return true;
    }
    return false;
}

bool Goomba::collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) 
{
    if (!isHit && sprite -> animation() != CRUSHED && collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) {
		return true;
    }
    return false;
}

bool Goomba::collisionMoveUp(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) 
{
    if (!isHit && sprite -> animation() != CRUSHED && collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) { 
		return true;
    }
    return false;
}

void Goomba::hit() {
    if (sprite -> animation() != CRUSHED) {
        isHit = true;
    }
}
