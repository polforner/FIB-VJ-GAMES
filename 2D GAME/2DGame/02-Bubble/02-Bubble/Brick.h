#ifndef _BRICK_INCLUDE
#define _BRICK_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include "Entity.h"

class Brick : public Entity{

public:

    void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram) override;
    void update(int deltaTime) override;
private:
    bool isHit, isDestroyed;
};
#endif
