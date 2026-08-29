#include "includes/timeline.h"
#include "includes/atulo.h"
#include "includes/miniaudio.h"
#include <ncurses.h>

void draw_timeline(ma_sound *sound, ma_uint32 sample_rate) {
  ma_uint64 totalFrames = 0;
  ma_sound_get_length_in_pcm_frames(sound, &totalFrames);

  if (totalFrames == 0) {
    totalFrames = 1;
  }

  ma_uint64 cursorFrames = 0;
  ma_sound_get_cursor_in_pcm_frames(sound, &cursorFrames);

  double currentSeconds = (double)cursorFrames / sample_rate;
  double totalSeconds = (double)totalFrames / sample_rate;
  double progress = (double)cursorFrames / totalFrames;

  if (progress > 1.0)
    progress = 1.0;

  int screen_row, screen_col;
  getmaxyx(stdscr, screen_row, screen_col);

  int bar_width = screen_col - 10;
  if (bar_width < 10)
    bar_width = 10;
  int filled_width = (int)(progress * bar_width);

  mvprintw(LINES - 2, 2, "[");
  for (int i = 0; i < bar_width; i++) {
    if (i < filled_width) {
      attron(COLOR_PAIR(ACCENT_COLOR));
      printw("=");
      attroff(COLOR_PAIR(ACCENT_COLOR));
    } else if (i == filled_width) {
      printw(">");
    } else {
      attron(COLOR_PAIR(MUTED_COLOR));
      printw("=");
      attroff(COLOR_PAIR(MUTED_COLOR));
    }
  }
  printw("]");

  int curMin = (int)currentSeconds / 60;
  int curSec = (int)currentSeconds % 60;
  int totMin = (int)totalSeconds / 60;
  int totSec = (int)totalSeconds % 60;

  mvprintw(LINES - 3, 2, "%02d:%02d / %02d:%02d  (%.1f%%)", curMin, curSec,
           totMin, totSec, progress * 100);

  refresh();
}
