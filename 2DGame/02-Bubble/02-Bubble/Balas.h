#ifndef _BALAS_INCLUDE
#define _BALAS_INCLUDE


#include "Sprite.h"
#include "TileMap.h"



class Balas
{

public:
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos, glm::vec2 vel);
	int getPositionX();
	int getPositionY();
	bool kills(const glm::vec2& posEnemie, const glm::ivec2& sizeTile);
	bool isAlive();

private:
	bool bJumping;
	glm::ivec2 tileMapDispl, spriteSize;
	glm::vec2 posPlayer, velocitat;
	int jumpAngle, startY;
	Texture spritesheet;
	Sprite* sprite;
	Sprite* sprite2;
	TileMap* map;
	bool alive, hit;

};

#endif
