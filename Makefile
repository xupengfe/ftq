CC = cc
ACC = x86_64-ucb-akaros-gcc
CFLAGS = -Wall -O2
ACFLAGS = -Wall -O2 -Dros
LIBS =
LDFLAGS = $(USER_OPT)

linux_core = --include linux.h ftq.c ftqcore.c linux.c

tests := $(patsubst tests/%.h,ftq_%,$(wildcard tests/*.h))

all: tests

tests: $(tests)

$(tests): ftq_%: tests/%.h linux.h ftq.c ftqcore.c linux.c
	$(CC) -o $@ $(CFLAGS) --include linux.h --include $< ftq.c ftqcore.c linux.c -lpthread -lrt

linux:
	cc $(CFLAGS) --include linux.h -Wall ftq.c ftqcore.c linux.c -o ftq.linux -lpthread -lrt
	cc $(CFLAGS) --include linux.h -Wall ftq.c ftqcore.c linux.c -o ftq.static.linux -lpthread -lrt -static

akaros:
	$(ACC) $(ACFLAGS) --include linux.h -Wall ftq.c ftqcore.c akaros.c -o ftq.akaros -lpthread

clean:
	rm -f *.o t_ftq ftq ftq.linux ftq.static.linux ftq.akaros *~
