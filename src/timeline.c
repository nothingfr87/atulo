#include "includes/timeline.h"
#include "includes/atulo.h"
#include "includes/miniaudio.h"
#include <ncurses.h>

void draw_timeline(WINDOW *win, ma_sound *sound, ma_uint32 sample_rate,
                   int box_w, int box_h) {

  ma_uint64 totalFrames = 0;
  ma_sound_get_length_in_pcm_frames(sound, &totalFrames);

  if (totalFrames == 0)
    totalFrames = 1;

  ma_uint64 cursorFrames = 0;
  ma_sound_get_cursor_in_pcm_frames(sound, &cursorFrames);

  double currentSeconds = (double)cursorFrames / sample_rate;
  double totalSeconds = (double)totalFrames / sample_rate;
  double progress = (double)cursorFrames / totalFrames;

  if (progress > 1.0)
    progress = 1.0;

  int bar_width = box_w - 6;

  if (bar_width < 10)
    bar_width = 10;

  int filled_width = (int)(progress * bar_width);

  int curMin = (int)currentSeconds / 60;
  int curSec = (int)currentSeconds % 60;
  int totMin = (int)totalSeconds / 60;
  int totSec = (int)totalSeconds % 60;

  mvwprintw(win, box_h / 2, 2, "%02d:%02d / %02d:%02d  (%.1f%%)", curMin,
            curSec, totMin, totSec, progress * 100);

  mvwprintw(win, (box_h / 2) + 1, 2, "[");

  for (int i = 0; i < bar_width; i++) {
    if (i < filled_width) {
      wattron(win, COLOR_PAIR(ACCENT_COLOR));
      waddch(win, '=');
      wattroff(win, COLOR_PAIR(ACCENT_COLOR));
    } else if (i == filled_width) {
      waddch(win, '>');
    } else {
      wattron(win, COLOR_PAIR(MUTED_COLOR));
      waddch(win, '=');
      wattroff(win, COLOR_PAIR(MUTED_COLOR));
    }
  }
  waddch(win, ']');
}
