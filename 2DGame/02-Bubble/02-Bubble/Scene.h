#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Goomba.h"
#include "HammerBros.h"
#include "TexturedQuad.h"
#include "Sphere.h"
#include "Explosion.h"
#include "Koopa.h"
#include "Lakitu.h"
#include "block_interrogante.h"
// Scene contains all the entities of our game.
// It is responsible for updating and render them.


#include <irrKlang.h>
using namespace irrklang;
#pragma comment(lib, "irrKlang.lib")

class Scene
{

public:
	Scene();
	~Scene();

	void init();
	int update(int deltaTime);
	void render();

private:
	void initShaders();
	void updateCamera(int deltaTime);
	void loadLevel(int lvl);
	void loadEnemies(int lvl);
	void setPlayerIniPos();
	bool goalState1();
	bool goalState2();
	bool goalState3();

private:
	TileMap *map;
	Player *player;
	block_interrogante* interrogante;
	Goomba *goomba[20];
	Koopa* koopa;
	Lakitu* lakitu;
	ShaderProgram texProgram;
	bool first;
	float currentTime;
	glm::mat4 projection;
	float cameraX;
	int level;
	// Text textLifes;
	int cameraState;
	// level 2 
	TexturedQuad* bgS2, *fireBar;
	Texture imageBgS2, imageFireBar;
	Sphere* sphere;
	float cineTimer;
	Explosion *explosion;

	HammerBros* hammerBros[5];

	ISoundEngine* engine;

};


#endif // _SCENE_INCLUDE

