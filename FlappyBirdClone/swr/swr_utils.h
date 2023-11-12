#ifndef _SWR_UTILS_H_
#define _SWR_UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif
	int swr_get_max(int a, int b);
	int swr_get_min(int a, int b);
	int swr_random_in_range(int a, int b);
	void swr_init_random();
#ifdef __cplusplus
}
#endif

#endif