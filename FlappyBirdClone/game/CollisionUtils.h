#ifndef _COLLISION_UTILS_H_
#define _COLLSION_UTILS_H_

#include "../swr/swr_pixel.h"

bool CheckCollision(
	int left1, int top1, int right1, int bottom1,
	int left2, int top2, int right2, int bottom2
	);

bool CheckCollisionPixelLevel(
	int a1x, int a1y, int a2x, int a2y,
	int b1x, int b1y, int b2x, int b2y,
	unsigned char *maskA, int aWidth, int aHeight,
	unsigned char *maskB, int bWidth, int bHeight
	);

unsigned char* CreateCollisionMaskImage(
	unsigned char* image, int width, int height,
	swr_color* chromaKey
	);

#endif