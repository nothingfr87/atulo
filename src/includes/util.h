#ifndef UTIL_H
#define UTIL_H

#include "miniaudio.h"

void pause_audio(const char *filename, ma_sound *sound, int *isPaused);
void replay(ma_sound *sound);

void forward_skip(ma_sound *sound, ma_uint32 sample_rate);
void backward_skip(ma_sound *sound, ma_uint32 sample_rate);

#endif
