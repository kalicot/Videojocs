#include "Goomba.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4
#define SPEED 0.12


enum GoombaAnimations
{
	MOVE_RIGHT, MOVE_LEFT, DIE
};


void Goomba::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	engine = createIrrKlangDevice();
	bJumping = false;
	hp = 3;
	dead = false;
	direction = MOVE_LEFT;
	spriteSize = glm::ivec2(18, 18);
	spritesheet.loadFromFile("images/goombaTiles2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(spriteSize, glm::vec2(0.1667, 1.0), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(MOVE_LEFT, 8);
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.0f));
	sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.1667, 0.0f));

	sprite->setAnimationSpeed(MOVE_RIGHT, 8);
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, 0.0f));
	sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.1667, 0.0f));


	sprite->setAnimationSpeed(DIE, 15);
	sprite->addKeyframe(DIE, glm::vec2(0.3333f, 0.0f));
	sprite->addKeyframe(DIE, glm::vec2(0.5f, 0.0f));
	sprite->addKeyframe(DIE, glm::vec2(0.6667f, 0.0f));
	sprite->addKeyframe(DIE, glm::vec2(0.8333f, 0.0f));


	sprite->changeAnimation(MOVE_LEFT);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

// --
void Goomba::update(int deltaTime)
{

	sprite->update(deltaTime);
	if ((sprite->animation() == DIE) && sprite->lastKeyFrame())
		dead = true;
	if (hp > 0) {
		posPlayer.y += FALL_STEP;
		bJumping = !map->collisionMoveDown(posPlayer, spriteSize, &posPlayer.y);
		if (map->collisionMoveLeft(posPlayer, spriteSize))
		{
			direction = MOVE_RIGHT;
		}
		else if (map->collisionMoveRight(posPlayer, spriteSize))
		{
			direction = MOVE_LEFT;
		}

		if (direction == MOVE_LEFT)
		{
			if (sprite->animation() != MOVE_LEFT)
				sprite->changeAnimation(MOVE_LEFT);
			posPlayer.x -= 1;
		}
		else
		{
			if (sprite->animation() != MOVE_RIGHT)
				sprite->changeAnimation(MOVE_RIGHT);
			posPlayer.x += 1;
		}
	}
	else
	{
		if (sprite->animation() != DIE)
		{
			engine->play2D("music/goomba.mp3");
			sprite->changeAnimation(DIE);
		}
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));

}

void Goomba::render()
{
	if (hp > 0)
		sprite->render();
	else if (!dead)
		sprite->render();

}

void Goomba::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Goomba::setPosition(const glm::vec2& pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

int Goomba::getPositionX()
{
	return posPlayer.x;
}

int Goomba::getPositionY()
{
	return posPlayer.y;
}

glm::vec2 Goomba::getSpriteSize()
{
	return spriteSize;
}

bool Goomba::isDead()
{
	return (hp <= 0);
}

void Goomba::damage()
{
	hp--;
}

void Goomba::revive()
{
	hp = 3;
	dead = false;
}

glm::ivec2 Goomba::getPosition() {
	return posPlayer;
}

void Goomba::kill()
{
	hp = 0;
}