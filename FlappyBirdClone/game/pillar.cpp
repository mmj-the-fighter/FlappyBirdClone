#include <algorithm>
#include "Game.h"
#include "pillar.h"
#include "rng.hpp"


Pillar::Pillar(int worldWt, int worldHt):
pillarTopX(worldWt), 
pillarBottomX(worldWt),
velX(MAX_PILLAR_VELOCITY),
randomY(0)
{
	ww = worldWt;
	wh = worldHt;
}

void Pillar::SetChromaKey(int red, int green, int blue)
{
	chromaR = red;
	chromaG = green;
	chromaB = blue;
}

void Pillar::SetBird(Bird *b){
	bird = b;
	birdHeight = b->height;
}

void Pillar::SetPillarImages(spn::Image* topImage, spn::Image* bottomImage) {
	pillarTopImage = topImage;
	pillarTopImageWidth = topImage->GetCanvas()->GetWidth();
	pillarTopImageHeight = topImage->GetCanvas()->GetHeight();

	pillarBottomImage = bottomImage;
	pillarBottomImageWidth = bottomImage->GetCanvas()->GetWidth();
	pillarBottomImageHeight = bottomImage->GetCanvas()->GetHeight();
}


void Pillar::MakePillar()
{
	randomY = Rng::Instance().GenerateInRange(0, wh);
	randomY = std::min(600 - birdHeight * 4, randomY);
	pillarTopY = randomY - pillarTopImageHeight;
	pillarBottomY = randomY + birdHeight * 3;
	pillarTopX = ww;
	pillarBottomX = ww;
}

void Pillar::Move(spn::Canvas *canvas)
{
	if (pillarTopX + pillarBottomImageWidth >= 0) {
		pillarTopX -= velX * canvas->GetLastFrameTime();
		pillarBottomX -= velX * canvas->GetLastFrameTime();
	}
}

bool Pillar::IsPillarOutOfScreen()
{
	return (pillarTopX + pillarBottomImageWidth < 0);
}

bool Pillar::IsBirdNear()
{
	int dx = pillarTopX - bird->x;
	return abs(dx) <= (pillarTopImageWidth + bird->width);
}

void Pillar::Display(spn::Canvas* canvas)
{
	canvas->DrawImageChromaKeyed(pillarTopImage, pillarTopX, pillarTopY, chromaR, chromaG, chromaB);
	canvas->DrawImageChromaKeyed(pillarBottomImage, pillarBottomX, pillarBottomY, chromaR, chromaG, chromaB);
}
