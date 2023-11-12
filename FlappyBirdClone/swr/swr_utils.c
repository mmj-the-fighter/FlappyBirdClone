#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "swr_utils.h"

int swr_get_max(int a, int b)
{
	return (a > b) ? a : b;
}

int swr_get_min(int a, int b)
{
	return (a < b) ? a : b;
}


int swr_random_in_range(int a, int b)
{
	if (a > b) {
		return 0;
	}
	return a + rand() % (b - a);
}

void swr_init_random()
{
	srand((unsigned)time(NULL));
}