#include "keys.h"
#include "miniaudio.h"
#include <inttypes.h>
#include <ncurses.h>
#include <unistd.h>

void userKeys(const char *filename, ma_engine *engine, ma_sound *sound,
              ma_uint32 sample_rate) {

  initscr();
  noecho();
  cbreak();
  curs_set(0);
  timeout(100);
  keypad(stdscr, TRUE);
  int ch;

  ma_sound_start(sound);
  printw("\rPlaying -> [%s] ....\n", filename);

  while (ma_sound_at_end(sound) == 0) {
    ma_uint64 cursorFrames;
    ch = getch();

    ma_sound_get_cursor_in_pcm_frames(sound, &cursorFrames);

    ma_uint64 totalSeconds = cursorFrames / sample_rate;
    ma_uint64 minutes = totalSeconds / 60;
    ma_uint64 seconds = totalSeconds % 60;

    printw("\rPosition: %02" PRIu64 ":%02" PRIu64, minutes, seconds);
    refresh();
    napms(100);

    static int isPaused = 0;

    if ('q' == ch || 27 == ch) {
      ma_sound_stop(sound);
      clear();
      printw("OK, Stopping.\n");
      refresh();
      napms(100);
      break;
    }
    if ('p' == ch || ' ' == ch) {
      if (!isPaused) {
        ma_sound_stop(sound);
        isPaused = 1;
        clear();
        printw("Paused. Press 'p' or Space to resume.\n");
      } else {
        ma_sound_start(sound);
        isPaused = 0;
        clear();
        printw("\rPlaying -> [%s] ....\n", filename);
      }
    }
    if (KEY_RIGHT == ch) {
      ma_uint64 currentFrame;

      ma_sound_get_cursor_in_pcm_frames(sound, &currentFrame);
      ma_sound_get_data_format(sound, NULL, NULL, &sample_rate, NULL, 0);

      ma_uint64 skipTime = (ma_uint64)sample_rate * 5;
      ma_uint64 newFrame = currentFrame + skipTime;

      ma_sound_seek_to_pcm_frame(sound, newFrame);
    }
    if (KEY_LEFT == ch) {
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
    if ('r' == ch) {
      ma_sound_seek_to_pcm_frame(sound, 0);
    }
    // usleep(10000);
    refresh();
  }
}
