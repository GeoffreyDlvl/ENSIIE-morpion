HEADERS_DIR = headers
SOURCES_DIR = sources
BINARIES_DIR = bin

CC = gcc -Wall -Wextra -pedantic

all : morpion

morpion : $(BINARIES_DIR)/interface.o $(BINARIES_DIR)/history.o $(BINARIES_DIR)/board.o $(BINARIES_DIR)/utils.o $(BINARIES_DIR)/main.o
	$(CC) $^ -o $@


$(BINARIES_DIR)/interface.o : $(SOURCES_DIR)/interface.c $(HEADERS_DIR)/interface.h $(HEADERS_DIR)/history.h $(HEADERS_DIR)/utils.h
	$(CC) -c $< -o $@

$(BINARIES_DIR)/history.o : $(SOURCES_DIR)/history.c $(HEADERS_DIR)/board.h $(HEADERS_DIR)/history.h $(HEADERS_DIR)/interface.h
	$(CC) -c $< -o $@

$(BINARIES_DIR)/board.o : $(SOURCES_DIR)/board.c $(HEADERS_DIR)/board.h $(HEADERS_DIR)/history.h $(HEADERS_DIR)/interface.h $(HEADERS_DIR)/utils.h
	$(CC) -c $< -o $@

$(BINARIES_DIR)/utils.o : $(SOURCES_DIR)/utils.c $(HEADERS_DIR)/utils.h 
	$(CC) -c $< -o $@

$(BINARIES_DIR)/main.o : $(SOURCES_DIR)/main.c $(HEADERS_DIR)/board.h $(HEADERS_DIR)/history.h $(HEADERS_DIR)/interface.h $(HEADERS_DIR)/utils.h
	$(CC) -c $< -o $@

$(shell mkdir -p $(BINARIES_DIR))
