#ifndef ATULO_H
#define ATULO_H

#include "miniaudio.h"

extern ma_engine engine;
extern ma_result result;
extern ma_sound sound;
extern ma_decoder decoder;
extern ma_uint32 sample_rate;

extern int isPaused;

void init_atulo(int argc, char *argv[]);

void quit_atulo();

void free_atulo();

#endif
