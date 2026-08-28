#include "includes/timeline.h"
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

  clear();

  int screen_row, screen_col;
  getmaxyx(stdscr, screen_row, screen_col);

  int barWidth = screen_col - 10;
  if (barWidth < 10)
    barWidth = 10;
  int filledWidth = (int)(progress * barWidth);

  mvprintw(LINES - 2, 2, "[");
  for (int i = 0; i < barWidth; i++) {
    if (i < filledWidth) {
      printw("=");
    } else if (i == filledWidth) {
      printw(">");
    } else {
      printw(" ");
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
