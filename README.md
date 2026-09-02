# Atulo

Atulo is a C program made to play audio files 

---

> [!NOTE]
> Atulo now supports mp3, wav, ogg, opus, aiff and flac any other format atulo wouldn't be able to play them, currently I am working on creating a decoder using ffmpeg, until then you can use atulo freely 

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
- Keyboard Focused 

---

## Usage:

| Key | Function |
| --- | -------- |
| <kbd>p</kbd> <kbd>Space</kbd> | Pause |
| <kbd>q</kbd> | Quit |
| <kbd>r</kbd> | Replay |
| <kbd>-></kbd> | Seek 5s |
| <kbd><-</kbd> | Seek 5s Backward |

---

## Configuration:

Atulo can be configured through `config.h` then rebuilding the source code

```h
#ifndef CONFIG_H
#define CONFIG_H

// Keys
#define KEY_QUIT 'q'
#define KEY_REPLAY 'r'
#define KEY_PAUSE 'p'
#define SEC_KEY_PAUSE ' ' // Space
#define SK_FR_KEY 0405 // Right Arrow
#define SK_BR_KEY 0404 // Left Arrow

// Box Width & Height
#define BOX_W 80
#define BOX_H 10

// Colors (MUST FOLLOW NCURSES COLOR CODES)
#define ACCENT_COLOR_CODE 5
#define MUTED_COLOR_CODE 8

#endif
```

You can change the width and height of the box that contains the elements

You can change the Keybindings (NON-LETTER KEYS MUST USE THE CORRESPONDING NCURSES KEY CODES)

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
