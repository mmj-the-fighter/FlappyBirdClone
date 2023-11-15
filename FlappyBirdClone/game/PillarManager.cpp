

#include "../swr/swr_image.h"

#include "PillarManager.h"
#include "Game.h"
#define MAX_PILLAR_COUNT 4
#define MAX_INTER_PILLAR_DISTANCE_MULTIPLIER 8

PillarManager::PillarManager()
{
};

PillarManager::~PillarManager(){
	for (auto& pillar : pillars) {
		delete pillar;
	}
	destroy_image(pillarTopImage);
	destroy_image(pillarBottomImage);

	if (collisionImageMaskTopPillar != NULL) {
		free(collisionImageMaskTopPillar);
	}
	if (collisionImageMaskBottomPillar != NULL) {
		free(collisionImageMaskBottomPillar);
	}
}

void PillarManager::Init(Bird* b)
{
	SetBird(b);
	SetChromaKey(0, 255, 0, 255);
	LoadImages();
	CreateMaskImages();
	GeneratePillars();
}

void PillarManager::SetBird(Bird* b)
{
	bird = b;
	birdHeight = b->height;
	birdWidth = b->width;
}

void PillarManager::SetChromaKey(int red, int green, int blue, int alpha)
{
	chromaKey.r = red;
	chromaKey.g = green;
	chromaKey.b = blue;
	chromaKey.a = alpha;
}


void PillarManager::LoadImages(){
	pillarTopImage = read_ppm_raw("images/pillar_top.ppm", LE, &pillarTopImageWidth, &pillarTopImageHeight);
	pillarBottomImage = read_ppm_raw("images/pillar_bottom.ppm", LE, &pillarBottomImageWidth, &pillarBottomImageHeight);
}

void PillarManager::CreateMaskImages()
{
	collisionImageMaskTopPillar = CreateCollisionMaskImage(pillarTopImage,
		pillarTopImageWidth,
		pillarTopImageHeight,
		&chromaKey
		);

	collisionImageMaskBottomPillar = CreateCollisionMaskImage(pillarBottomImage,
		pillarBottomImageWidth,
		pillarBottomImageHeight,
		&chromaKey
		);
}


void PillarManager::GeneratePillars()
{
	for (int i = 0; i < MAX_PILLAR_COUNT; i++) {
		Pillar * pillar = new Pillar;
		pillar->pillarPassageId = i;
		pillar->SetTopPillarImage(pillarTopImage, pillarTopImageWidth, pillarTopImageHeight);
		pillar->SetBottomPillarImage(pillarBottomImage, pillarBottomImageWidth, pillarBottomImageHeight);
		pillar->SetChromaKey(chromaKey.r, chromaKey.g ,chromaKey.b, chromaKey.a);
		pillar->SetCollisionImageMasks(collisionImageMaskTopPillar, collisionImageMaskBottomPillar);
		pillar->SetBird(bird);
		pillar->MakePillar();
		pillar->velX = MAX_PILLAR_VELOCITY;
		pillar->pillarTopX = 
			pillar->pillarBottomX = 
			GAME_RESOLUTION_X + 
			i * (MAX_INTER_PILLAR_DISTANCE_MULTIPLIER * birdWidth);
		pillars.push_back(pillar);
	}
	leftMostPillarIndex = 0;
	rightMostPillarIndex = MAX_PILLAR_COUNT - 1;
}


void PillarManager::ResetPillars()
{
	int i = 0;
	for (auto& pillar : pillars) {
		pillar->MakePillar();
		pillar->pillarTopX = 
			pillar->pillarBottomX = 
			GAME_RESOLUTION_X + 
			i * (MAX_INTER_PILLAR_DISTANCE_MULTIPLIER * birdWidth);
		++i;
	}
	leftMostPillarIndex = 0;
	rightMostPillarIndex = MAX_PILLAR_COUNT - 1;
}

void PillarManager::Move(swr_sdl_context* ctx)
{
	Pillar *leftMostPillar = pillars[leftMostPillarIndex];
	if (leftMostPillar->IsPillarLeftOfScreen()){
		leftMostPillar->MakePillar();
		leftMostPillar->pillarTopX = 
		leftMostPillar->pillarBottomX = 
		pillars[rightMostPillarIndex]->pillarTopX + 
		MAX_INTER_PILLAR_DISTANCE_MULTIPLIER * birdWidth;
		rightMostPillarIndex = leftMostPillarIndex;
		leftMostPillarIndex = (leftMostPillarIndex + 1) % MAX_PILLAR_COUNT;
	}
	
	for (auto& pillar : pillars) {
		pillar->Move(ctx);
	}
}

void PillarManager::Display()
{
	for (auto& pillar : pillars) {
		if (!pillar->IsPillarLeftOfScreen()) {
			pillar->Display();
		}
	}
}

void PillarManager::CheckCollisionOfBirdWithPillars(CollisionState* collisionState)
{
	collisionState->location = HITNOTHING;
	collisionState->pillarPassageId = -1;
	//int count = MAX_PILLAR_COUNT;
	int count = 2;
	int index = leftMostPillarIndex;
	while (collisionState->location == HITNOTHING && --count >= 0) {
		Pillar* pillar = pillars[index];
		if (pillar->IsBirdNear()) {
			pillar->CheckCollisionWithBird(collisionState);
		}
		index = (index + 1) % MAX_PILLAR_COUNT;
	}
}
