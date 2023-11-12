#include "../swr/swr_image.h"
#include "../swr/swr_rasterizer.h"

#include "Bird.h"
#include "Game.h"
#include "CollisionUtils.h"


Bird::Bird()
	: image(NULL), collisionImageMask(NULL)
{
	
}

Bird::~Bird()
{
	destroy_image(image);
	if (collisionImageMask != NULL) {
		free(collisionImageMask);
	}
}

void Bird::OnJumpStarted()
{
	jumping = true;
	jumpTime = MAX_JUMP_DELAY;
	velY = 0;
	jumpAccelY = MAX_JUMP_ACCELERATION;
}

void Bird::OnJumpEnded()
{
	jumping = false;
	//velY = 0;
	jumpAccelY = 0;
}

void Bird::OnLeftMouseButtonDown()
{
	if (!jumping) {
		OnJumpStarted();
	}
}


void Bird::Move(swr_sdl_context *ctx)
{
	if (jumping) {
		if (jumpTime <= 0.0f) {
			OnJumpEnded();
		} else {
			jumpTime -= ctx->lastFrameTime;
			velY -= (jumpAccelY)* ctx->lastFrameTime;
		}
	} else {
		velY += (gravityY)* ctx->lastFrameTime;
	}
	y += velY;
}

bool Bird::IsOutOfScreen()
{
	int top = (int)y;
	int bottom = top + height;
	return (top >= GAME_RESOLUTION_Y) || (bottom < 0);
}

void Bird::Display()
{
	rasterizer_copy_pixels_chromakey(
		(int)x, (int)y,width, height,
		&chromaKey, image
	);
	//DrawCollisionRectangle();
}


void Bird::DrawCollisionRectangle()
{
	int left = (int)x;
	int top = (int)y;
	int bottom = top + height;
	int right = left + width;
	rasterizer_draw_rect(left, top, right, bottom);
}

void Bird::Init()
{
	x = GAME_RESOLUTION_X / 3;
	y = GAME_RESOLUTION_Y / 2;
	velY = 0;
	gravityY = GRAVITY;
	jumpAccelY = 0;
	jumping = false;
	SetChromaKey(0, 255, 0, 255);
	LoadImage("images/bird.ppm");
	CreateMask();
}

void Bird::Reset()
{
	x = GAME_RESOLUTION_X / 3;
	y = GAME_RESOLUTION_Y / 2;
	velY = 0;
	gravityY = GRAVITY;
	jumpAccelY = 0;
	jumping = false;
}

void Bird::SetChromaKey(int red, int green, int blue, int alpha)
{
	chromaKey.r = red;
	chromaKey.g = green;
	chromaKey.b = blue;
	chromaKey.a = alpha;
}

void Bird::LoadImage(const char* path)
{
	image = read_ppm_raw(path, LE, &width, &height);
}

void Bird::CreateMask(){
	collisionImageMask = CreateCollisionMaskImage(image, width, height, &chromaKey);
}

