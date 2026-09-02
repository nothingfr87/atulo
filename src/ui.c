#include "includes/ui.h"
#include "../config.h"
#include "includes/atulo.h"
#include "includes/miniaudio.h"
#include "includes/timeline.h"
#include "includes/util.h"
#include <inttypes.h>
#include <limits.h>
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

  init_pair(ACCENT_COLOR, ACCENT_COLOR_CODE, -1);
  init_pair(MUTED_COLOR, MUTED_COLOR_CODE, -1);
}

void draw_ui(const char *filename, ma_engine *engine, ma_sound *sound,
             ma_uint32 sample_rate) {

  int ch;
  int running = 1;
  ma_sound_start(sound);

  while (running && ma_sound_at_end(sound) == 0) {
    ch = getch();

    int row, col;
    getmaxyx(stdscr, row, col);

    int box_w = BOX_W;
    int box_h = BOX_H;

    if (box_w > col - 4)
      box_w = col - 4;

    if (box_h > row - 4)
      box_h = row - 4;

    int box_y = (row - box_h) / 2;
    int box_x = (col - box_w) / 2;

    WINDOW *ui_box = newwin(box_h, box_w, box_y, box_x);

    box(ui_box, 0, 0);

    mvwprintw(ui_box, 1, 2, "Atulo Player —  %s", filename);
    mvwprintw(ui_box, 2, 2, "Status: %s", isPaused ? "[PAUSED]" : "[PLAYING]");
    draw_timeline(ui_box, sound, sample_rate, box_w, box_h);

    wattron(ui_box, COLOR_PAIR(MUTED_COLOR));
    mvwprintw(ui_box, box_h - 1, 2,
              "Controls: Play/Pause [%s] | Quit [%s] | Replay [%s] | Seek 5s "
              "[%s / %s] ",
              get_key_name(KEY_PAUSE), get_key_name(KEY_QUIT),
              get_key_name(KEY_REPLAY), get_key_name(SK_FR_KEY),
              get_key_name(SK_BR_KEY));
    wattroff(ui_box, COLOR_PAIR(MUTED_COLOR));

    wrefresh(ui_box);
    delwin(ui_box);

    refresh();

    switch (ch) {
    case KEY_QUIT:
      running = 0;
      quit_atulo();
      break;
    case KEY_PAUSE:
    case SEC_KEY_PAUSE:
      pause_audio(filename, sound, &isPaused);
    case SK_FR_KEY:
      forward_skip(sound, sample_rate);
      break;
    case SK_BR_KEY:
      backward_skip(sound, sample_rate);
      break;
    case KEY_REPLAY:
      replay(sound);
    }
  }
}
