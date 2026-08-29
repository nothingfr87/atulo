#ifndef UI_H
#define UI_H
#include "miniaudio.h"

void init_ui();

void draw_ui(const char *filename, ma_engine *engine, ma_sound *sound,
             ma_uint32 sample_rate);

#endif
