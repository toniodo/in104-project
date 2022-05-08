CC = gcc
CFLAGS = -Wall -Wfatal-errors -Werror -g

DEPENDENCIES = agent.c environment.c render.c
BINS = main

all: $(BINS)

main: $(DEPENDENCIES:%.c=%.o)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	@$(CC) $(CFLAGS) -c $^

start: main
	./main

clean_objects:
	@rm -rf *.o

clean: clean_objects
	@rm -rf $(BINS)