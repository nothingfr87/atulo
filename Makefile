GCC_PARAMS = -Wall -O2 -I/usr/include/SDL2 -D_REENTRANT -lSDL2 -o

build:
	gcc src/main.c $(GCC_PARAMS) player

install: build
	mv player /usr/local/bin/player
	chmod 777 /usr/local/bin/player

uninstall:
	rm -f /usr/local/bin/player

clean:
	rm -f player
