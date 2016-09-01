#define testcase_declare

#define testcase_init()

#define testcase_exit()

#define testcase_iter(pcount)					\
	do {							\
		int __k;					\
		for (__k = 0; __k < ITERCOUNT; __k++)		\
			(*(pcount))++;				\
		for (__k = 0; __k < (ITERCOUNT - 1); __k++)	\
			(*(pcount))--;				\
	} while (0)
