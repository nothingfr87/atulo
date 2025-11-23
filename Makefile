build:
	cmake -B build
	cmake --build build

install: build
	mv build/player /usr/local/bin/player
	chmod 777 /usr/local/bin/player

uninstall:
	rm -f /usr/local/bin/player

clean:
	rm -rf build 
