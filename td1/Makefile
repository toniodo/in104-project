CC = gcc
CFLAGS = -Wall -Wfatal-errors -Werror -g

#SRCS = $(wildcard *.c)
DEPENDENCIES = functions.c mazeEnv.c policies.c
BINS = solveur dfs solveur2

all: $(BINS)


solveur: $(DEPENDENCIES:%.c=%.o) qlearning.o
	$(CC) $(CFLAGS) -o $@ $^

dfs: $(DEPENDENCIES:%.c=%.o) dfs.o
	$(CC) $(CFLAGS) -o $@ $^

solveur2: $(DEPENDENCIES:%.c=%.o) 2qlearning.c
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	@$(CC) $(CFLAGS) -c $^

clean_objects:
	@rm -rf *.o

clean: clean_objects
	@rm -rf solveur dfs solveur2