#ifndef _BIRD_H_
#define _BIRD_H_

#include "../swr/swr_sdl_context.h"

#define MAX_JUMP_DELAY 0.15f
#define MAX_JUMP_ACCELERATION 17.5f
#define GRAVITY 10.0f

class Bird
{
public:
	Bird();
	~Bird();
	void Move(swr_sdl_context *ctx);
	void Display();
	void DrawCollisionRectangle();
	void Init();
	void Reset();
	void OnJumpStarted();
	void OnJumpEnded();
	void OnLeftMouseButtonDown();
	bool IsOutOfScreen();
private:
	void LoadImage(const char* fileName);
	void CreateMask();
	void SetChromaKey(int red, int green, int blue, int alpha);
	bool jumping;
	float jumpTime;
	float jumpAccelY;
	float velY;
	float gravityY;
public:
	int x;
	int y;
	int width;
	int height;
	unsigned char* image;
	unsigned char* collisionImageMask;
	swr_color chromaKey;
};

#endif
