

#include "../swr/swr_image.h"

#include "PillarManager.h"
#include "Game.h"

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
	for (int i = 0; i < 4; i++) {
		Pillar * pillar = new Pillar;
		pillar->pillarPassageId = i;
		pillar->SetTopPillarImage(pillarTopImage, pillarTopImageWidth, pillarTopImageHeight);
		pillar->SetBottomPillarImage(pillarBottomImage, pillarBottomImageWidth, pillarBottomImageHeight);
		pillar->SetChromaKey(0,255,0,255);
		pillar->SetCollisionImageMasks(collisionImageMaskTopPillar, collisionImageMaskBottomPillar);
		pillar->SetBird(bird);
		pillar->MakePillar();
		pillar->velX = MAX_PILLAR_VELOCITY;
		pillar->pillarTopX = pillar->pillarBottomX = GAME_RESOLUTION_X + i * (8 * birdHeight);
		pillars.push_back(pillar);
	}
}


void PillarManager::ResetPillars()
{
	int i = 0;
	for (auto& pillar : pillars) {
		pillar->MakePillar();
		pillar->pillarTopX = pillar->pillarBottomX = GAME_RESOLUTION_X + i * (8 * birdHeight);
		++i;
	}
}

void PillarManager::Move(swr_sdl_context* ctx)
{
	int i = 0;

	auto iterator = pillars.begin();
	Pillar* pillar = *iterator;
	bool isFirstPillarInsertedToBack = false;
	if (pillar->IsPillarLeftOfScreen()) {
		Pillar* pillarBack = pillars.back();
		pillar->MakePillar();
		pillar->pillarTopX = pillar->pillarBottomX = pillarBack->pillarTopX + 8 * birdHeight;
		pillars.pop_front();
		pillars.push_back(pillar);
		isFirstPillarInsertedToBack = true;
	}
	else{
		isFirstPillarInsertedToBack = false;
		pillar->Move(ctx);
	}

	auto iterator2 = pillars.begin();
	if (!isFirstPillarInsertedToBack) {
		++iterator2;
	}
	while (iterator2 != pillars.end()) {
		Pillar* pillar = *iterator2;
		pillar->Move(ctx);
		++iterator2;
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
	for (auto& pillar : pillars) {
		if (pillar->IsBirdNear()) {
			pillar->CheckCollisionWithBird(collisionState);
			break;
		}
	}
}
