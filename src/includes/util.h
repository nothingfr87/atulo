#ifndef UTIL_H
#define UTIL_H

#include "miniaudio.h"

static inline const char *get_key_name(int key) {
  static char buf[2];

  switch (key) {
  case ' ':
    return "Space";

  case 0404:
    return "Left";

  case 0405:
    return "Right";

  case 0406:
    return "Up";

  case 0407:
    return "Down";

  case 27:
    return "Esc";

  case '\n':
    return "Enter";

  default:
    if (key >= 32 && key <= 126) {
      buf[0] = (char)key;
      buf[1] = '\0';
      return buf;
    }

    return "Unknown";
  }
}

void pause_audio(const char *filename, ma_sound *sound, int *isPaused);
void replay(ma_sound *sound);

void forward_skip(ma_sound *sound, ma_uint32 sample_rate);
void backward_skip(ma_sound *sound, ma_uint32 sample_rate);

#endif
