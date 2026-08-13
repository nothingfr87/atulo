#include "includes/atulo.h"
#include "includes/miniaudio.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

ma_engine engine;
ma_result result;
ma_sound sound;
ma_decoder decoder;
ma_uint32 sample_rate;
int isPaused;

void init_atulo(int argc, char *argv[]) {
  if (argc <= 1) {
    fprintf(stderr, "Usage: %s <audio-file>\n", argv[0]);
    exit(1);
  }

  result = ma_engine_init(NULL, &engine);
  if (result != MA_SUCCESS) {
    perror("Failed to initialize engine\n");
    exit(1);
  }

  ma_uint32 channels;
  result = ma_decoder_get_data_format(&decoder, NULL, &channels, &sample_rate,
                                      NULL, 0);
  if (result != MA_SUCCESS) {
    fprintf(stderr, "Failed to get decoder format.\n");
    exit(1);
  }

  result = ma_sound_init_from_file(&engine, argv[1], MA_SOUND_FLAG_STREAM, NULL,
                                   NULL, &sound);
  if (result != MA_SUCCESS) {
    perror("Failed to initialize sound file\n");
    ma_engine_uninit(&engine);
    exit(1);
  }

  result = ma_sound_get_data_format(&sound, NULL, NULL, &sample_rate, NULL, 0);

  if (result != MA_SUCCESS || sample_rate == 0) {
    fprintf(stderr, "Failed to get audio sample rate.\n");
    ma_sound_uninit(&sound);
    ma_engine_uninit(&engine);
    exit(1);
  }
}

void quit_atulo() {
  ma_sound_stop(&sound);
  clear();
  printw("Stopping.\n");
  refresh();
}

void free_atulo() {
  ma_sound_stop(&sound);
  ma_sound_uninit(&sound);
  ma_engine_uninit(&engine);
}
