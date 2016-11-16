#include <sys/mman.h>

#define CACHE_SIZE		(5UL * 1024 * 1024 / 2)
#define CACHE_LENGTH		(CACHE_SIZE / sizeof(unsigned long))
#define CACHE_STRIDE		(64 / sizeof(unsigned long))

#define testcase_declare			\
	unsigned long *cache_data

#define testcase_init()							\
	cache_data = mmap(NULL, CACHE_SIZE, PROT_READ | PROT_WRITE,	\
			  MAP_PRIVATE | MAP_ANONYMOUS | MAP_POPULATE,	\
			  -1, 0)

#define testcase_exit()				\
	munmap(cache_data, CACHE_SIZE)

#define testcase_iter(pcount)						\
	do {								\
		int i;							\
		for (i = 0; i < CACHE_LENGTH; i += CACHE_STRIDE)	\
			cache_data[i] = *(pcount);			\
		(*(pcount))++;						\
	} while (0)
