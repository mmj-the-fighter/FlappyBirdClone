#ifndef _PILLAR_H_
#define _PILLAR_H_

#include "../swr/swr_sdl_context.h"
#include "Bird.h"
#include "CollisionState.h"


#define MAX_PILLAR_VELOCITY 140.0f

class Pillar
{
public:
	Pillar();
	~Pillar();
	void Move(swr_sdl_context* ctx);	
	void MakePillar();
	void Display();	
	void DrawCollisionRectangles();
	bool IsPillarLeftOfScreen();
	bool IsBirdNear();
	void CheckCollisionWithBird(CollisionState *collisionState);

	void SetBird(Bird* b);
	void SetChromaKey(int red, int green, int blue, int alpha);
	void SetTopPillarImage(unsigned char* image, int width, int height);
	void SetBottomPillarImage(unsigned char* image, int width, int height);
	void SetCollisionImageMasks(unsigned char* topMask, unsigned char* bottomMask);

	unsigned char* pillarTopImage;
	unsigned char* pillarBottomImage;
	unsigned char* collisionImageMaskTopPillar;
	unsigned char* collisionImageMaskBottomPillar;
	
	int randomY;
	int birdHeight;
	float pillarTopX;
	float pillarTopY;
	float pillarBottomX;
	float pillarBottomY;
	float velX;
	int pillarTopImageWidth;
	int pillarTopImageHeight;
	int pillarBottomImageWidth;
	int pillarBottomImageHeight;
	int pillarPassageId;
	swr_color chromaKey;
	Bird *bird;
};



#endif