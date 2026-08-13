#include "includes/keys.h"
#include "includes/atulo.h"
#include "includes/miniaudio.h"
#include "includes/util.h"
#include <inttypes.h>
#include <locale.h>
#include <ncurses.h>
#include <unistd.h>

void user_keys(const char *filename, ma_engine *engine, ma_sound *sound,
               ma_uint32 sample_rate) {

  setlocale(LC_ALL, "");
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

    printw("\rPosition: %02" PRIu64 ":%02" PRIu64, (unsigned long)minutes,
           (unsigned long)seconds);
    refresh();
    napms(100);

    if ('q' == ch || 27 == ch) {
      quit_atulo();
      break;
    }
    if ('p' == ch || ' ' == ch) {
      pause_audio(filename, sound, &isPaused);
    }
    if (KEY_RIGHT == ch) {
      forward_skip(sound, sample_rate);
    }
    if (KEY_LEFT == ch) {
      backward_skip(sound, sample_rate);
    }
    if ('r' == ch) {
      replay(sound);
    }
    refresh();
  }
}
