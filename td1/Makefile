CC = gcc
CFLAGS = -Wall -Wfatal-errors -Werror -g

#SRCS = $(wildcard *.c)
DEPENDENCIES = functions.c mazeEnv.c
BINS = solveur dfs

all: $(BINS)


solveur: $(DEPENDENCIES:%.c=%.o) qlearning.o
	$(CC) $(CFLAGS) -o $@ $^

dfs: $(DEPENDENCIES:%.c=%.o) dfs.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	@$(CC) $(CFLAGS) -c $^

clean_objects:
	@rm -rf *.o

clean: clean_objects
	@rm -rf solveur dfs