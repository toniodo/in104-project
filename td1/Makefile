CC = gcc
CFLAGS = -Wall -Wfatal-errors -Werror -g

#SRCS = $(wildcard *.c)
DEPENDENCIES = functions.c mazeEnv.c policies.c
BINS = solveur dfs solveur2 sarsa

all: $(BINS)


solveur: $(DEPENDENCIES:%.c=%.o) qlearning.o
	$(CC) $(CFLAGS) -o $@ $^

dfs: $(DEPENDENCIES:%.c=%.o) dfs.o
	$(CC) $(CFLAGS) -o $@ $^

solveur2: $(DEPENDENCIES:%.c=%.o) 2qlearning.o
	$(CC) $(CFLAGS) -o $@ $^

sarsa: $(DEPENDENCIES:%.c=%.o) sarsa.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	@$(CC) $(CFLAGS) -c $^

start: solveur
	./solveur

clean_objects:
	@rm -rf *.o

clean: clean_objects
	@rm -rf $(BINS)
