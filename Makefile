CC = gcc -Wall -Wextra -ansi

sources/main.o : sources/main.c headers/board.h headers/history.h headers/interface.h
	$(CC) -c $< -o $@
