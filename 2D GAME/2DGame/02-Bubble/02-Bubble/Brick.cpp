#include "Brick.h"

void Brick::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) {
    Entity::init(tileMapPos, shaderProgram);
    isHit = false;
    isDestroyed = false;
    spritesheet.loadFromFile("images/spriteMario.png", TEXTURE_PIXEL_FORMAT_RGBA);
    sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.125, 0.125), &spritesheet, &shaderProgram);
}

void Brick::update(int deltaTime) {
    sprite->update(deltaTime);
}