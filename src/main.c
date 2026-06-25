#include "keys.h"
#include "miniaudio.h"
#include <inttypes.h>
#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    fprintf(stderr, "Usage: %s <audio-file>\n", argv[0]);
    return 1;
  }

  ma_engine engine;
  ma_result result;
  ma_sound sound;
  ma_decoder decoder;

  result = ma_engine_init(NULL, &engine);
  if (result != MA_SUCCESS) {
    perror("Failed to initialize engine\n");
    return 1;
  }

  ma_uint32 sample_rate = ma_engine_get_sample_rate(&engine);

  if (sample_rate == 0) {
    endwin();
    fprintf(stderr, "Could not get audio sample rate.\n");
    ma_engine_uninit(&engine);
    return 1;
  }

  result = ma_sound_init_from_file(&engine, argv[1], MA_SOUND_FLAG_STREAM, NULL,
                                   NULL, &sound);
  if (result != MA_SUCCESS) {
    perror("Failed to initialize sound file\n");
    ma_engine_uninit(&engine);
    return 1;
  }

  userKeys(argv[1], &engine, &sound, sample_rate);

  ma_sound_stop(&sound);
  ma_sound_uninit(&sound);
  ma_engine_uninit(&engine);

  return 0;
}
