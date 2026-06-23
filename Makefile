GCC_ARGUMENTS = -Wall -O2 $(shell pkg-config --cflags --libs openal sndfile ncursesw) -o 
CC = gcc
BIN = atulo

install_dir = "/usr/local/bin/"

all: clean build

build:
	gcc src/main.c $(GCC_ARGUMENTS) $(BIN) 

install: build
	mv $(BIN) $(install_dir) 
	chmod 777 $(install_dir)$(BIN)

uninstall:
	rm -f $(install_dir)$(BIN)

clean:
	rm -f $(BIN) 
