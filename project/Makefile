CC = gcc
CFLAGS = -Wall -Wfatal-errors -Werror -g

DEPENDENCIES = $(wildcard src/*.c)
BINS = main

all: $(BINS)

main: main.o $(DEPENDENCIES:%.c=%.o) src/agent.h
	$(CC) $(CFLAGS) -o $@ $^

*/%.o: */%.c
	@$(CC) $(CFLAGS) -c $^

start: main
	./main

clean_objects:
	@rm -rf *.o
	@rm -rf src/*.o

clean: clean_objects
	@rm -rf $(BINS)

debug: main
	gdb main