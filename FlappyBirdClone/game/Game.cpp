#include "..\swr\swr_utils.h"
#include "Game.h"

Game::Game()
	:gameOver(false)
{
	bird = new Bird();
	pillarManager = new PillarManager();
	scoreManager = new ScoreManager();
	swr_init_random();
}

Game::~Game()
{
	delete bird;
	delete pillarManager;
	delete scoreManager;
}

void Game::Init()
{
	gameOver = false;
	scoreManager->Init();
	lastHitPassageId = -1;
	bird->Init();
	pillarManager->Init(bird);	
}

void Game::Restart()
{
	gameOver = false;
	scoreManager->Reset();
	bird->Reset();
	lastHitPassageId = -1;
	pillarManager->ResetPillars();
}

void Game::OnLeftMouseButtonDown()
{
	bird->OnLeftMouseButtonDown();
}

void Game::OnRightMouseButtonDown()
{
	Restart();
}

void Game::Tick(swr_sdl_context *ctx)
{
	if (bird->IsOutOfScreen()) {
		gameOver = true;
	}

	if (!gameOver)
	{
		
		pillarManager->CheckCollisionOfBirdWithPillars(&collisionState);

		switch (collisionState.location)
		{
		case HITPASSAGE:
			if (lastHitPassageId != collisionState.pillarPassageId) {
				scoreManager->IncrementScore();
				lastHitPassageId = collisionState.pillarPassageId;
			}
		case HITNOTHING:
			bird->Move(ctx);
			pillarManager->Move(ctx);
			break;
		case HITPILLAR:
			gameOver = true;
			break;
		default:
			break;
		}
	}
}

void Game::Display()
{
	rasterizer_clear();
	pillarManager->Display();
	bird->Display();
	scoreManager->DisplayScore(gameOver);
}