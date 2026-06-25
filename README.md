# Atulo

Atulo is a C program made to play audio files 

---

> [!NOTE]
> Atulo now supports mp3, wav, ogg, opus, and flac any other format atulo wouldn't be able to play them, currently I am working on creating a decoder using ffmpeg, until then you can use atulo freely 

---

## Requirements:

- GCC 
- miniaudio.h (embedded in the project) 
- Ncurses

#### Debian/Ubuntu Distros

```bash
sudo apt update
sudo apt install build-essentials  libncurses5-dev libncursesw5-dev
```

#### Fedora Distros

```bash
sudo dnf groupinstall "Development Tools"
sudo dnf install ncurses-devel
```

#### Arch Distros

```bash
sudo pacman -S base-devel ncurses

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
