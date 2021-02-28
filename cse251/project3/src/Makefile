CC := $(shell which cc)
CFLAGS += -g -Wall-Werror -O2

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)
APP := scheduler

$(APP): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	$(RM) $(APP) $(OBJS)
