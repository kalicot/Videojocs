#include "Balas.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4
#define SPEED 0.12


enum PlayerAnims
{
	SHOOT, FLY, HIT
};

//S: straight
//U: up
//D: down
//R: right
//L: left
enum angle
{
	S_R = 0, U_R = 45, U_L = 135, S_L = 180, D_L = 225, D_R = 315
};


void Balas::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram)
{
	bJumping = false;
	alive = false;
	spritesheet.loadFromFile("images/Bullets.png", TEXTURE_PIXEL_FORMAT_RGBA);

	spriteSize = glm::ivec2(8, 8);

	sprite = Sprite::createSprite(spriteSize, glm::vec2(0.2, 1.0), &spritesheet, &shaderProgram);

	sprite->setNumberAnimations(3);

	sprite->setAnimationSpeed(SHOOT, 35);
	sprite->addKeyframe(SHOOT, glm::vec2(0.f, 0.0f));
	sprite->addKeyframe(SHOOT, glm::vec2(0.2f, 0.0f));
	sprite->addKeyframe(SHOOT, glm::vec2(0.4f, 0.0f));
	sprite->addKeyframe(SHOOT, glm::vec2(0.6f, 0.0f));

	sprite->setAnimationSpeed(FLY, 3);
	sprite->addKeyframe(FLY, glm::vec2(0.6f, 0.0f));

	sprite->setAnimationSpeed(HIT, 3);
	sprite->addKeyframe(HIT, glm::vec2(0.8f, 0.0f));


	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));


}

// --
void Balas::update(int deltaTime)
{
	sprite->update(deltaTime);
	posPlayer.x += velocitat.x;
	posPlayer.y += velocitat.y;
	if (sprite->animation()  == SHOOT)
	{
		if (sprite->lastKeyFrame())
			sprite->changeAnimation(FLY);
	}

	if (alive)
	{
		posPlayer.x += velocitat.x;
		posPlayer.y += velocitat.y;
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));


}

void Balas::render()
{
	sprite->render();
}

void Balas::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Balas::setPosition(const glm::vec2& pos, glm::ivec2 vel)
{
	posPlayer = pos;
	alive = true;
	velocitat = vel;
	sprite->changeAnimation(SHOOT);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

int Balas::getPositionX()
{
	return posPlayer.x;
}

int Balas::getPositionY()
{
	return posPlayer.y;
}

bool Balas::dies(const glm::vec2& posEnemie, const glm::ivec2& sizeTile)
{
	//hago el tama�o de colision mas peque�o para que no se note tanto que tenemos pixeles vacios delante del sprite del player
	int xEnemie1, xEnemie2, yEnemie1, yEnemie2;
	xEnemie1 = posEnemie.x + 4;
	xEnemie2 = xEnemie1 + sizeTile.x - 2;
	yEnemie1 = posEnemie.y + 2;
	yEnemie2 = yEnemie1 + sizeTile.y - 2;
	//mirar primer si la posicio x1 del player es troba entre les del enemic, x2 player entre x del enemic
	//o com l'sprite del player es mes gran mirar si x1 < x1 enemie i x2 > x2 enemie
	if (((posPlayer.x >= xEnemie1) && (posPlayer.x <= xEnemie2)) || (((posPlayer.x + spriteSize.x) >= xEnemie1) && ((posPlayer.x + spriteSize.x) <= xEnemie2)) || ((posPlayer.x <= xEnemie1) && ((posPlayer.x + spriteSize.x) >= xEnemie2)))
	{
		if (((posPlayer.y >= yEnemie1) && (posPlayer.y <= yEnemie2)) || (((posPlayer.y + spriteSize.y) >= yEnemie1) && ((posPlayer.y + spriteSize.y) <= yEnemie2)) || ((posPlayer.y <= yEnemie1) && ((posPlayer.y + spriteSize.y) >= yEnemie2)))
		{
			alive = false;
			return true;
		}
	}
	alive = true;
	return false;

}

bool Balas::isAlive()	//et diu si la bala esta viva
{
	return alive;
}

