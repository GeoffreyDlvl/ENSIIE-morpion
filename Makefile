CC = gcc -Wall -Wextra -ansi

main.o : main.c plateau.h historique.h interface.h
	$(CC) -c $< -o $@
