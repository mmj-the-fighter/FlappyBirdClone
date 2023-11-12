#ifndef _GAME_H_
#define _GAME_H_

#include "../swr/swr_sdl_context.h"
#include "Bird.h"
#include "PillarManager.h"
#include "ScoreManager.h"

#define GAME_RESOLUTION_X 800
#define GAME_RESOLUTION_Y 600

class Game
{
public:
	Game();
	~Game();
	void Init();
	void Restart();
	void Tick(swr_sdl_context *ctx);
	void Display();
	void OnLeftMouseButtonDown();
	void OnRightMouseButtonDown();
	inline bool IsGameOver(){ return gameOver; }
public:
	bool gameOver;
	Bird* bird;
	PillarManager* pillarManager;
	ScoreManager* scoreManager;
	int lastHitPassageId;
	CollisionState collisionState;
};

#endif
