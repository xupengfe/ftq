#include <sys/mman.h>

#define CACHE_SIZE		(1UL * 1024 * 1024)
#define CACHE_LENGTH		(cache_size / sizeof(unsigned long))
#define CACHE_STRIDE		(64 / sizeof(unsigned long))

#define testcase_declare			\
	unsigned long *cache_data;		\
	int cache_size = CACHE_SIZE

#define testcase_init()							\
	do {								\
		if (test_argument)					\
			cache_size = atoi(test_argument);		\
		cache_data = mmap(NULL, cache_size, PROT_READ | PROT_WRITE, \
				  MAP_PRIVATE | MAP_ANONYMOUS | MAP_POPULATE, \
				  -1, 0);				\
	} while (0)

#define testcase_exit()				\
	munmap(cache_data, cache_size)

#define testcase_iter(pcount)						\
	do {								\
		int i;							\
		for (i = 0; i < CACHE_LENGTH; i += CACHE_STRIDE)	\
			cache_data[i] = *(pcount);			\
		(*(pcount))++;						\
	} while (0)
