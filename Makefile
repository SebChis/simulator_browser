# CHISELITA Sebastian - 314CA 
CC = gcc
CFLAGS = -Wall -Wextra -lm

SRC = main.c stacks.c prints.c frees.c pages.c tabs.c move_tabs.c
EXE = tema1

build:
	$(CC) -o $(EXE) $(SRC) $(CFLAGS)

run:
	./$(EXE)

.PHONY: clean
clean:
	rm -f $(EXE) *~
