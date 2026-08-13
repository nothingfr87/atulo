CFLAGS  = $(shell pkg-config --cflags ncursesw)
LDFLAGS = $(shell pkg-config --libs ncursesw) -lpthread -lm -ldl
SRC = src/*.c
CC = gcc
BIN = atulo
install_dir = /usr/local/bin

.PHONY: all build install uninstall clean

all: clean build

build:
	$(CC) $(CFLAGS) $(SRC) -o $(BIN) $(LDFLAGS)

install: clean build
	sudo mkdir -p $(install_dir)
	sudo cp $(BIN) $(install_dir)/
	sudo chmod 755 $(install_dir)/$(BIN)

uninstall:
	sudo rm -f $(install_dir)/$(BIN)

clean:
	rm -f $(BIN)
