#ifndef _PILLARMANAGER_H_
#define _PILLARMANAGER_H_

#include <vector>
#include "../swr/swr_sdl_context.h"
#include "CollisionState.h"
#include "CollisionUtils.h"
#include "pillar.h"


class PillarManager
{
public:
	PillarManager();
	~PillarManager();
	void Init(Bird* b);
	void LoadImages();
	void CreateMaskImages();
	void GeneratePillars();
	void ResetPillars();
	void SetBird(Bird* b);
	void Move(swr_sdl_context* ctx);
	void Display();
	void CheckCollisionOfBirdWithPillars(CollisionState* collisionState);
	void SetChromaKey(int red, int green, int blue, int alpha);
private:
	swr_color chromaKey;
	Bird *bird;
	int birdHeight;
	int birdWidth;
	int pillarTopImageWidth;
	int pillarTopImageHeight;
	int pillarBottomImageWidth;
	int pillarBottomImageHeight;
	unsigned char* pillarTopImage;
	unsigned char* pillarBottomImage;
	unsigned char* collisionImageMaskTopPillar;
	unsigned char* collisionImageMaskBottomPillar;
	std::vector<Pillar*> pillars;
	int leftMostPillarIndex;
	int rightMostPillarIndex;
};


