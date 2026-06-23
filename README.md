# Audio Player

Audio Player is a C program made to play audio files with OpenAL Library

---

> [!NOTE]
> After testing `atulo` a bit, it turns out that loading all of the audio data into one buffer to the memory creates a huge memory usage for every second the audio file increases, so if the audio file is 20 minutes it would take approximately 200MB-300MB

> [!WARNING]
> Due to my weak experience, I am going to stop developing on Atulo for sometime till I find a solution for the memory usage problem
> Contributions are still open!

---

## Requirements:

- GCC 
- OpenAL
- Libsndfile
- Ncurses

#### Debian/Ubuntu Distros

```bash
sudo apt update
sudo apt install libopenal-dev libsndfile1-dev build-essentials  libncurses5-dev libncursesw5-dev
```

#### Fedora Distros

```bash
sudo dnf groupinstall "Development Tools"
sudo dnf install openal-soft-devel libsndfile-devel ncurses-devel
```

#### Arch Distros

```bash
sudo pacman -S base-devel openal libsndfile ncurses

```

--- 

## Supported OS:
- Linux
- MacOS (Not Tested)

---

## How to build:

### Build

Run `make clean build` to only build the file in the current directory you will have a binary for the program

```bash
$ make clean build
```

### Install

Run `sudo make clean install` to build and move the binary to the `/usr/local/bin/` directory to make it run everywhere

```bash
$ sudo make clean install
```

### Uninstall

Run `sudo make uninstall` to uninstall the program

```bash
sudo make uninstall
```

---

## Features:

- Works from terminal directly
- lightweight
- Supports all formats
- Keybindings:
    - p/Space: Pause
    - q/Escape: Exit
    - r: replay from start
    - Right Arrow: Skip 5 seconds
    - Left Arrow: Go back 5 seconds

More Coming...

---

## Issues

if you find any issues you can report at [Issues](https://github.com/nothingfr87/Atulo/issues)

---

## Contributing

Contributions are welcome whether they are adding new features or improving code just make your edit and make a pull request

Please make sure your pull request is well documented

--- 

## License

This Project is licensed under the [GPLv3 License](LICENSE)
