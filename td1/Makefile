CC = gcc
CFLAGS = -Wall -Wfatal-errors -Werror

SRCS = $(wildcard *.c)
BINS = solveur
INCLUDES = $(SRCS:%.c=%)

all: $(BINS)

solveur: $(SRCS:%.c=%.o)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	@$(CC) -c $<

clean:
	@rm -rf solveur *.o