CFLAGS = $(shell pkg-config --cflags --libs ncursesw) -lpthread -lm -ldl
FILES = src/main.c src/keys.c src/miniaudio.c
BIN = atulo
install_dir = /usr/local/bin/

all: clean build

install: clean build
	chmod 777 $(BIN)
	mv $(BIN) $(install_dir)

build:
	cc $(FILES) -o $(BIN) $(CFLAGS)

clean:
	rm -rf $(BIN) 2>/dev/null
