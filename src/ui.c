#include "includes/ui.h"
#include "includes/atulo.h"
#include "includes/miniaudio.h"
#include "includes/timeline.h"
#include "includes/util.h"
#include <inttypes.h>
#include <locale.h>
#include <ncurses.h>
#include <unistd.h>

void init_ui() {
  setlocale(LC_ALL, "");
  initscr();
  noecho();
  cbreak();
  start_color();
  use_default_colors();
  curs_set(0);
  timeout(100);
  keypad(stdscr, TRUE);

  init_pair(ACCENT_COLOR, COLOR_MAGENTA, -1);
  init_pair(MUTED_COLOR, 8, -1);
}

void draw_ui(const char *filename, ma_engine *engine, ma_sound *sound,
             ma_uint32 sample_rate) {

  int ch;
  ma_sound_start(sound);

  while (ma_sound_at_end(sound) == 0) {
    ch = getch();

    draw_timeline(sound, sample_rate);

    mvprintw(1, 2, "Atulo Player —  %s", filename);
    mvprintw(2, 2, "Status: %s", isPaused ? "[PAUSED] " : "[PLAYING]");
    attron(COLOR_PAIR(MUTED_COLOR));
    mvprintw(LINES - 5, 2,
             "Controls: [Space] Pause/Play | [<- / ->] Seek 5s | [r] Replay | "
             "[q] Quit");
    attroff(COLOR_PAIR(MUTED_COLOR));

    refresh();

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
