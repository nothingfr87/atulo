#ifndef TIMELINE_H
#define TIMELINE_H

#include "miniaudio.h"
#include <ncurses.h>

void draw_timeline(WINDOW *win, ma_sound *sound, ma_uint32 sample_rate,
                   int box_w, int box_h);

#endif
