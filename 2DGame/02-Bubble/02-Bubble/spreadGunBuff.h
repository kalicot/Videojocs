#ifndef _SPREAD_GUN_BUFF_INCLUDE
#define _SPREAD_GUN_BUFF_INCLUDE

#include "Sprite.h"
#include "TileMap.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class spreadGunBuff

{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	int getPositionX();
	int getPositionY();
	bool isActive();
	void activate();
	void damage();
	glm::vec2 getSpriteSize();


private:
	bool bJumping;
	int start;
	glm::ivec2 tileMapDispl, posPlayer, spriteSize;
	int jumpAngle, startY;
	Texture spritesheet;
	Texture spritesheet2;
	Sprite* sprite;
	TileMap* map;
	int hp;
	int direction;
	bool dead;
	bool active;

};

#endif