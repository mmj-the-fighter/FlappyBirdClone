#include<cstdio>
#include <cmath>
#include "../swr/swr_rasterizer.h"
#include "../swr/swr_utils.h"

#include "CollisionUtils.h"
#include "Game.h"
#include "Pillar.h"



Pillar::Pillar():
pillarTopX(GAME_RESOLUTION_X), 
pillarBottomX(GAME_RESOLUTION_X),
velX(MAX_PILLAR_VELOCITY),
randomY(0)
{
}

Pillar::~Pillar(){

}

void Pillar::SetCollisionImageMasks(unsigned char* topMask, unsigned char* bottomMask)
{
	collisionImageMaskTopPillar = topMask;
	collisionImageMaskBottomPillar = bottomMask;
}

void Pillar::SetChromaKey(int red, int green, int blue, int alpha)
{
	chromaKey.r = red;
	chromaKey.g = green;
	chromaKey.b = blue;
	chromaKey.a = alpha;
}

void Pillar::SetBird(Bird *b){
	bird = b;
	birdHeight = b->height;
}

void Pillar::SetTopPillarImage(unsigned char* image, int width, int height)
{
	pillarTopImage = image;
	pillarTopImageWidth = width;
	pillarTopImageHeight = height;
}

void Pillar::SetBottomPillarImage(unsigned char* image, int width, int height)
{
	pillarBottomImage = image;
	pillarBottomImageWidth = width;
	pillarBottomImageHeight = height;
}

void Pillar::MakePillar()
{
	randomY = swr_random_in_range(0, GAME_RESOLUTION_Y);
	randomY = swr_get_min(600 - birdHeight * 4, randomY);
	pillarTopY = randomY - pillarTopImageHeight;
	pillarBottomY = randomY + birdHeight * 3;
	pillarTopX = GAME_RESOLUTION_X;
	pillarBottomX = GAME_RESOLUTION_X;
}

void Pillar::Move(swr_sdl_context* ctx)
{
	if (pillarTopX + pillarBottomImageWidth >= 0) {
		pillarTopX -= velX * ctx->lastFrameTime;
		pillarBottomX -= velX * ctx->lastFrameTime;
	}
}

bool Pillar::IsPillarLeftOfScreen()
{
	return (pillarTopX + pillarBottomImageWidth < 0);
}

bool Pillar::IsBirdNear()
{
	int dx = pillarTopX - bird->x;
	return abs(dx) <= (pillarTopImageWidth + bird->width);
}

void Pillar::Display()
{
	rasterizer_copy_pixels_chromakey(
		(int)pillarTopX, int(pillarTopY),
		pillarTopImageWidth, pillarTopImageHeight,
		&chromaKey, pillarTopImage
		);
	rasterizer_copy_pixels_chromakey(
		(int)pillarBottomX, int(pillarBottomY),
		pillarBottomImageWidth, pillarBottomImageHeight,
		&chromaKey, pillarBottomImage
		);
	//DrawCollisionRectangles();

}

void Pillar::DrawCollisionRectangles()
{
	int gap = birdHeight * 3;
	int left = pillarTopX;
	int top = 0;
	int bottom = pillarTopY + pillarTopImageHeight;
	int right = left + pillarTopImageWidth;
	if (bottom >= 600) bottom = 599;
	rasterizer_set_cur_color(0, 255, 0, 255);
	rasterizer_draw_rect(left, top, right, bottom);

	left = pillarBottomX;
	top = pillarBottomY;
	if (top < 599){
		bottom = pillarBottomY + pillarBottomImageHeight;
		if (bottom >= 600) bottom = 599;
		right = left + pillarBottomImageWidth;
		rasterizer_set_cur_color(255, 255, 0, 255);
		rasterizer_draw_rect(left, top, right, bottom);
	}

	left = pillarTopX;
	top = randomY + 1;
	bottom = top + gap - 1;
	right = left + pillarTopImageWidth;
	rasterizer_set_cur_color(255, 255, 255, 255);
	rasterizer_draw_rect(left, top, right, bottom);

}

void Pillar::CheckCollisionWithBird(CollisionState* collisionState)
{


	collisionState->pillarPassageId = -1;

	bool isCollidedWithTopPillar = false;
	bool isCollidedWithBottomPillar = false;
	bool isCollidedWithPassage = false;

	isCollidedWithTopPillar = CheckCollisionPixelLevel(
		bird->x,
		bird->y,
		bird->x + bird->width,
		bird->y + bird->height,
		pillarTopX,
		pillarTopY,
		pillarTopX + pillarTopImageWidth,
		pillarTopY + pillarTopImageHeight,
		bird->collisionImageMask, bird->width, bird->height,
		collisionImageMaskTopPillar, pillarTopImageWidth, pillarTopImageHeight
	);

	if (isCollidedWithTopPillar){
		collisionState->location = HITPILLAR;
		return;
	}

	isCollidedWithBottomPillar = CheckCollisionPixelLevel(
		bird->x,
		bird->y,
		bird->x + bird->width,
		bird->y + bird->height,
		pillarBottomX,
		pillarBottomY,
		pillarBottomX + pillarBottomImageWidth,
		pillarBottomY + pillarBottomImageHeight,
		bird->collisionImageMask, bird->width, bird->height,
		collisionImageMaskBottomPillar, pillarBottomImageWidth, pillarBottomImageHeight
		);

	if (isCollidedWithBottomPillar){
		collisionState->location = HITPILLAR;
		return;
	}

	int gap = birdHeight * 3;

	isCollidedWithPassage = CheckCollision(
		bird->x,
		bird->y,
		bird->x + bird->width,
		bird->y + bird->height,
		pillarTopX,
		randomY + 1,
		pillarTopX + pillarTopImageWidth,
		randomY + 1 + gap - 1
		);

	if (isCollidedWithPassage){
		collisionState->location = HITPASSAGE;
		collisionState->pillarPassageId = pillarPassageId;
		return;
	}

	collisionState->location = HITNOTHING;
	return;
}
