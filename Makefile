CC = gcc -Wall -Wextra -ansi

sources/main.o : sources/main.c headers/plateau.h headers/historique.h headers/interface.h
	$(CC) -c $< -o $@
