CC = gcc -Wall -Wextra -pedantic

all : sources/main.out

sources/main.out : sources/interface.o sources/history.o sources/board.o sources/main.o
	$(CC) $^ -o $@

sources/interface.o : sources/interface.c headers/interface.h headers/history.h
	$(CC) -c $< -o $@

sources/history.o : sources/history.c headers/board.h headers/history.h headers/interface.h
	$(CC) -c $< -o $@

sources/board.o : sources/board.c headers/board.h headers/history.h headers/interface.h
	$(CC) -c $< -o $@

sources/main.o : sources/main.c headers/board.h headers/history.h headers/interface.h
	$(CC) -c $< -o $@
