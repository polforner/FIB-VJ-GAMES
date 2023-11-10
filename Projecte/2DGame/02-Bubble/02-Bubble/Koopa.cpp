#include "Koopa.h"
#include "Game.h"
#define SIZE_X 60
#define SIZE_Y 64

#define KOOPA_FALL_STEP 2
#define KOOPA_VELOCITY 1
#define KOOPA_ROLLING_VELOCITY 5
enum States
{
	WAITING, ROLLING_LEFT, ROLLING_RIGHT, MOVING_LEFT, MOVING_RIGHT
};

void Koopa::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
    Enemy::init(tileMapPos, shaderProgram);

    spritesheet.loadFromFile("images/spriteKoopa2.png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.25, 0.25), &spritesheet, &shaderProgram);
    sprite->setNumberAnimations(5);

    sprite->setAnimationSpeed(WAITING, 8);
	sprite->addKeyframe(WAITING, glm::vec2(0.f, 0.5f));

    sprite->setAnimationSpeed(ROLLING_LEFT, 8);
	sprite->addKeyframe(ROLLING_LEFT, glm::vec2(0.f, 0.5f));

    sprite->setAnimationSpeed(ROLLING_RIGHT, 8);
	sprite->addKeyframe(ROLLING_RIGHT, glm::vec2(0.f, 0.5f));

    sprite->setAnimationSpeed(MOVING_LEFT, 8);
	sprite->addKeyframe(MOVING_LEFT, glm::vec2(0.25f, 0.f));
    sprite->addKeyframe(MOVING_LEFT, glm::vec2(0.25f, 0.25f));

    sprite->setAnimationSpeed(MOVING_RIGHT, 8);
	sprite->addKeyframe(MOVING_RIGHT, glm::vec2(0.f, 0.f));
    sprite->addKeyframe(MOVING_RIGHT, glm::vec2(0.f, 0.25f));

    sprite->changeAnimation(MOVING_LEFT);

    deadTime = 0;
}

void Koopa::update(int deltaTime) {
    sprite->update(deltaTime);
    if (isHit) {
        if (sprite -> animation() == WAITING || sprite -> animation() == ROLLING_LEFT || sprite -> animation() == ROLLING_RIGHT) isActive = false;
        else sprite -> changeAnimation(WAITING);
        Game::instance().playMusic("goombaDie");
        deadTime = 0;
        isHit = false;
    }
    else {
        if (sprite -> animation() == WAITING ) {
            deadTime += deltaTime;
            if (deadTime > 10000) sprite -> changeAnimation(MOVING_RIGHT);
        }
        position.y += KOOPA_FALL_STEP;
        int i = 0;
        bool collision = map->collisionMoveDown(position, glm::ivec2(SIZE_X,SIZE_Y), &position.y);
        while (!collision && i < blocks.size()) {
            if (blocks[i] -> isEntityActive()) collision = blocks[i] -> collisionMoveDown(position, glm::ivec2(SIZE_X,SIZE_Y), &position.y);
            ++i;
        }
        if (position.y + SIZE_Y >= ((map -> getMapSize()).y) * (map -> getTileSize())) isActive = false;

        if (sprite -> animation() == MOVING_LEFT || sprite ->animation() == ROLLING_LEFT) {
            if (sprite -> animation() == MOVING_LEFT) position.x -= KOOPA_VELOCITY;
            else position.x -= KOOPA_ROLLING_VELOCITY;
            bool collision = map->collisionMoveLeft(position, glm::ivec2(SIZE_X,SIZE_Y),&position.x);
            while (!collision && i < blocks.size()) {
                if (blocks[i] -> isEntityActive()) collision = blocks[i] -> collisionMoveLeft(position, glm::ivec2(SIZE_X,SIZE_Y));
                ++i;
            }

            if (collision) {
                if (sprite ->animation() == MOVING_LEFT) sprite -> changeAnimation(MOVING_RIGHT);
                else sprite -> changeAnimation(ROLLING_RIGHT);
            }
        }
        else if (sprite ->animation() == MOVING_RIGHT || sprite ->animation() == ROLLING_RIGHT) {
            if (sprite -> animation() == MOVING_RIGHT) position.x += KOOPA_VELOCITY;
            else position.x += KOOPA_ROLLING_VELOCITY;
            bool collision = map->collisionMoveRight(position, glm::ivec2(SIZE_X,SIZE_Y), &position.x);
            while (!collision && i < blocks.size()) {
                if (blocks[i] -> isEntityActive()) collision = blocks[i] -> collisionMoveRight(position, glm::ivec2(SIZE_X,SIZE_Y),&position.x);
                ++i;
            }

            if (collision) {
                if (sprite ->animation() == MOVING_RIGHT) sprite -> changeAnimation(MOVING_LEFT);
                else sprite -> changeAnimation(ROLLING_LEFT);
            }  
        }
    }
    Entity::setPosition(position);
}

bool Koopa::collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) 
{
    if (!isHit && collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) {
        if (sprite -> animation() == WAITING) {
            sprite -> changeAnimation(ROLLING_LEFT);
            return false;
        }
		return true;
    }
    return false;
}

bool Koopa::collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size, int *posX) 
{
    if (!isHit && collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) {
        if (sprite -> animation() == WAITING) {
            sprite -> changeAnimation(ROLLING_RIGHT);
            return false;
        }
		return true;
    }
    return false;
}

bool Koopa::collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) 
{
    if (!isHit && collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) {
        if (sprite -> animation() == WAITING) return false;
		return true;
    }
    return false;
}

bool Koopa::collisionMoveUp(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) 
{
    if (!isHit && collision(position, glm::ivec2(SIZE_X,SIZE_Y), pos, size)) { 
		return true;
    }
    return false;
}

void Koopa::hit() {
    isHit = true;
}
