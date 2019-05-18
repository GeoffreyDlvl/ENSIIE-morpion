HEADERS_DIR = headers
SOURCES_DIR = sources
BINARIES_DIR = bin
GTK_DIR = gtk-gui
VALGRIND_TEST_CONTEXT = tests/valgrind-test
COPY_BIN_TO_VALGRIND_CONTEXT = cp -v  morpion_* $(VALGRIND_TEST_CONTEXT)/morpion; cp -Rv assets $(VALGRIND_TEST_CONTEXT)
CC = gcc -Wall -Wextra -pedantic

CFLAGS=`pkg-config --cflags gtk+-3.0`
CLIBS=`pkg-config --libs gtk+-3.0`

all : init morpion

init:
	set -e

morpion : morpion_gtk morpion_console

morpion_console : $(BINARIES_DIR)/interface_console.o $(BINARIES_DIR)/history.o $(BINARIES_DIR)/board.o $(BINARIES_DIR)/utils.o $(BINARIES_DIR)/main.o
	$(CC) $^ -o $@
	$(COPY_BIN_TO_VALGRIND_CONTEXT)

morpion_gtk : $(BINARIES_DIR)/interface_gtk.o $(BINARIES_DIR)/history.o $(BINARIES_DIR)/board.o $(BINARIES_DIR)/utils.o $(BINARIES_DIR)/main.o $(BINARIES_DIR)/gui.o $(BINARIES_DIR)/canvas.o $(BINARIES_DIR)/gui.o $(BINARIES_DIR)/gui-top.o
	$(CC) $(CFLAGS) $^ $(CLIBS) -o $@ -lm
	$(COPY_BIN_TO_VALGRIND_CONTEXT)

$(BINARIES_DIR)/interface_console.o : $(SOURCES_DIR)/interface_console.c $(HEADERS_DIR)/interface.h $(HEADERS_DIR)/history.h $(HEADERS_DIR)/utils.h
	$(CC) -c $< -o $@

$(BINARIES_DIR)/gui-top.o : $(GTK_DIR)/gui-top.c $(GTK_DIR)/gui-top.h
	$(CC) $(CFLAGS) -c $< $(CLIBS) -o $@ -lm

$(BINARIES_DIR)/canvas.o : $(GTK_DIR)/canvas.c $(GTK_DIR)/gui.h $(GTK_DIR)/canvas.h
	$(CC) $(CFLAGS) -c $< $(CLIBS) -o $@ -lm

$(BINARIES_DIR)/gui.o : $(GTK_DIR)/gui.c $(GTK_DIR)/gui.h $(GTK_DIR)/canvas.h
	$(CC) $(CFLAGS) -c $< $(CLIBS) -o $@ -lm

$(BINARIES_DIR)/interface_gtk.o : $(SOURCES_DIR)/interface_gtk.c $(HEADERS_DIR)/interface.h $(HEADERS_DIR)/history.h $(HEADERS_DIR)/utils.h $(GTK_DIR)/gui.h $(GTK_DIR)/canvas.h
	$(CC) $(CFLAGS) -c $< $(CLIBS) -o $@ -lm

$(BINARIES_DIR)/history.o : $(SOURCES_DIR)/history.c $(HEADERS_DIR)/board.h $(HEADERS_DIR)/history.h $(HEADERS_DIR)/interface.h
	$(CC) -c $< -o $@

$(BINARIES_DIR)/board.o : $(SOURCES_DIR)/board.c $(HEADERS_DIR)/board.h $(HEADERS_DIR)/history.h $(HEADERS_DIR)/interface.h $(HEADERS_DIR)/utils.h
	$(CC) -c $< -o $@

$(BINARIES_DIR)/utils.o : $(SOURCES_DIR)/utils.c $(HEADERS_DIR)/utils.h 
	$(CC) -c $< -o $@

$(BINARIES_DIR)/main.o : $(SOURCES_DIR)/main.c $(HEADERS_DIR)/board.h $(HEADERS_DIR)/history.h $(HEADERS_DIR)/interface.h $(HEADERS_DIR)/utils.h
	$(CC) -c $< -o $@

clean:
	rm $(BINARIES_DIR)/*.o

$(shell mkdir -p $(BINARIES_DIR))
