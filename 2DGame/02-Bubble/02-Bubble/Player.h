#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "Balas.h"

#include <irrKlang.h>
using namespace irrklang;
#pragma comment(lib, "irrKlang.lib")

#define NUM_BALES 90


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram);
	void update(int deltaTime);
	void render();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	int getPositionX();
	int getPositionY();
	glm::ivec2 getPosition();
	bool dies(const glm::vec2& posEnemie, const glm::ivec2& sizeTile);
	bool kills(const glm::vec2& posEnemie, const glm::ivec2& sizeTile);
	void setFrontal(bool b);
	void setRunUpAnimation();
	int getRound();
	glm::vec2 getSpriteSize();
	void activeTripleshoot();

private:
	void shoot(const glm::vec2& pos, int angle);

private:
	bool bJumping;
	glm::ivec2 tileMapDispl, posPlayer, spriteSize, spriteSize2, spriteSize3;
	int jumpAngle, startY;
	Texture spritesheet;
	Texture spritesheet2;
	Texture spritesheet3;
	Sprite *sprite;
	Sprite *sprite2;
	Sprite* sprite3;
	TileMap *map;
	bool dead;
	int chooseSprite;
	int actualBullet;
	Balas *bales[90];
	bool right;
	int canShoot;
	bool tripleshoot;
	bool frontal;
	bool runUp;
	int round;
	
	ISoundEngine* engine;
};


#endif // _PLAYER_INCLUDE


