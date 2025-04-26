#pragma once

#ifndef _BIRD_H_
#define _BIRD_H_

#include "../spinach/core/spn_canvas.h"
#include "../spinach/core/spn_image.h"

#define MAX_JUMP_DELAY 0.15f
#define MAX_JUMP_ACCELERATION 17.5f
#define GRAVITY 10.0f

class Bird
{
public:
	Bird();
	~Bird();
	void Move(spn::Canvas* canvas);
	void Display(spn::Canvas* canvas);
	void Init(int worldWt, int worldHt);
	void Reset();
	void OnJumpStarted();
	void OnJumpEnded();
	void OnLeftMouseButtonDown();
	bool IsOutOfScreen();
private:
	bool jumping;
	float jumpTime;
	float jumpAccelY;
	float velY;
	float gravityY;
	void DrawCollider(spn::Canvas* canvas, int x, int y);
public:
	int ww, wh;
	int x;
	int y;
	int width;
	int height;
	spn::Image image;
	int chromaR;
	int chromaG;
	int chromaB;
};

#endif

