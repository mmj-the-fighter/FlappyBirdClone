#include <cmath>
#include <cstdlib>
#include <cstdio>
#include "../swr/swr_utils.h"
#include "CollisionUtils.h"


bool CheckCollision(
	int left1, int top1, int right1, int bottom1,
	int left2, int top2, int right2, int bottom2
	)
{
	int  x1, x2;
	if (bottom2 < top1 || top2 > bottom1){
		return false;
	}
	else
	{
		x1 = (left2  > left1) ? left2 : left1;
		x2 = (right2 < right1) ? right2 : right1;
		if (x1 > x2)
			return false;
		return true;
	}
}

bool CheckCollisionPixelLevel(
	int a1x, int a1y, int a2x, int a2y,
	int b1x, int b1y, int b2x, int b2y,
	unsigned char *maskA, int aWidth, int aHeight,
	unsigned char *maskB, int bWidth, int bHeight
	)
{

	if (!CheckCollision(a1x, a1y, a2x, a2y, b1x, b1y, b2x, b2y)){
		return false;
	}
	/*intersect */
	int p1x = a1x;
	int p1y = a1y;
	int p2x = a2x;
	int p2y = a2y;

	int p3x = b1x;
	int p3y = b1y;
	int p4x = b2x;
	int p4y = b2y;

	int p5x = swr_get_max(p1x, p3x);
	int p5y = swr_get_max(p1y, p3y);

	int p6x = swr_get_min(p2x, p4x);
	int p6y = swr_get_min(p2y, p4y);
	/*clip */
	int asx = p5x - p1x;
	int asy = p5y - p1y;
	int atw = abs(p5x - p6x);
	int ath = abs(p5y - p6y);

	int bsx = p5x - p3x;
	int bsy = p5y - p3y;
	int btw = abs(p5x - p6x);
	int bth = abs(p5y - p6y);

	int dy, dx;
	int aoffset, boffset;
	unsigned char* aloc;
	unsigned char* bloc;

	for (dy = 0; dy < ath; ++dy)
	{
		for (dx = 0; dx < atw; ++dx)
		{
			aoffset = (aWidth * (asy + dy)) + (asx + dx);
			boffset = (bWidth * (bsy + dy)) + (bsx + dx);
			aloc = maskA + aoffset;
			bloc = maskB + boffset;
			if (*aloc != 0 && *bloc != 0){
				return true;
			}
		}
	}
	return false;

}

unsigned char* CreateCollisionMaskImage(
	unsigned char* image, int width, int height,
	swr_color* chromaKey)
{
	int numPixels = width * height;
	unsigned char* mask = (unsigned char*)malloc(numPixels * sizeof(unsigned char));
	unsigned char* loc = image;
	int i;
	unsigned char red = 0, blue = 0, green = 0, alpha = 0;
	unsigned char redChroma = chromaKey->r, 
		blueChroma = chromaKey->b, 
		greenChroma = chromaKey->g, 
		alphaChroma = chromaKey->a;

	for (i = 0; i < numPixels; ++i) {
		blue = *loc;
		green = *(loc + 1);
		red = *(loc + 2);
		alpha = *(loc + 3);
		if (red == redChroma  && 
			green == greenChroma && 
			blue == blueChroma && 
			alpha == alphaChroma)
		{
			*(mask + i) = 0;
		}
		else{
			*(mask + i) = 1;
		}
		loc += 4;
	}
	return mask;
}
