#include "includes/util.h"
#include "includes/miniaudio.h"
#include <ncurses.h>
#include <stdlib.h>

void pause_audio(const char *filename, ma_sound *sound, int *isPaused) {
  if (!*isPaused) {
    ma_sound_stop(sound);
    *isPaused = 1;
    clear();
    printw("Paused. Press 'p' or Space to resume.\n");
  } else {
    ma_sound_start(sound);
    *isPaused = 0;
    clear();
    printw("Playing -> [%s]\n", filename);
  }
}

void replay(ma_sound *sound) { ma_sound_seek_to_pcm_frame(sound, 0); }

void forward_skip(ma_sound *sound, ma_uint32 sample_rate) {
  ma_uint64 currentFrame;
  ma_sound_get_cursor_in_pcm_frames(sound, &currentFrame);
  ma_sound_get_data_format(sound, NULL, NULL, &sample_rate, NULL, 0);
  ma_uint64 skipTime = (ma_uint64)sample_rate * 5;
  ma_uint64 newFrame = currentFrame + skipTime;
  ma_sound_seek_to_pcm_frame(sound, newFrame);
}

void backward_skip(ma_sound *sound, ma_uint32 sample_rate) {
  ma_uint64 currentFrame;
  ma_uint64 skipFrames = (ma_uint64)sample_rate * 5;
  ma_uint64 newFrame;
  ma_sound_get_cursor_in_pcm_frames(sound, &currentFrame);
  if (currentFrame < skipFrames) {
    newFrame = 0;
  } else {
    newFrame = currentFrame - skipFrames;
  }
  ma_sound_seek_to_pcm_frame(sound, newFrame);
}
