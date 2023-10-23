
enum koopaAnims
{
	MOVE_LEFT, MOVE_RIGHT, SHELL
};

/*

void Koopa::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int dir) // Goomba
{
direction = dir;
spritesheet.loadFromFile("images/spriteKoopa.png", TEXTURE_PIXEL_FORMAT_RGBA);
sprite = Sprite::createSprite(glm::ivec2(32, 64), glm::vec2(0.25, 0.5), &spritesheet, &shaderProgram);
sprite->setNumberAnimations(3);

sprite->setAnimationSpeed(MOVE_LEFT, 8);
sprite->addKeyframe(MOVING, glm::vec2(0.f, 0.0f));
sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.5f));

sprite->setAnimationSpeed(MOVE_RIGHT, 8);
sprite->addKeyframe(MOVING, glm::vec2(0.5f, 0.0f));
sprite->addKeyframe(STAND_LEFT, glm::vec2(0.5f, 0.5f));

sprite->setAnimationSpeed(SHELL, 8);
sprite->addKeyframe(ELIMINATED, glm::vec2(0.25f, 0.f));

sprite->changeAnimation(0);
tileMapDispl = tileMapPos;
sprite->setPosition(glm::vec2(float(tileMapDispl.x + posEnemy.x + ENEMY_SPEED * dist), float(tileMapDispl.y + posEnemy.y)));

}