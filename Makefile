MKDIR_P = mkdir -p

BIN_DIR = $(MKDIR_P) bin

CC = gcc -Wall -Wextra -pedantic

all : morpion

morpion : bin/interface.o bin/history.o bin/board.o bin/main.o
	$(CC) $^ -o $@

$(BIN_DIR)/interface.o : sources/interface.c headers/interface.h headers/history.h
	$(CC) -c $< -o $@

bin/history.o : sources/history.c headers/board.h headers/history.h headers/interface.h
	$(CC) -c $< -o $@

bin/board.o : sources/board.c headers/board.h headers/history.h headers/interface.h
	$(CC) -c $< -o $@

$(BIN_DIR)/main.o : sources/main.c headers/board.h headers/history.h headers/interface.h
	$(CC) -c $< -o $@
