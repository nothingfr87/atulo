#include <AL/al.h>
#include <AL/alc.h>
#include <sndfile.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  // FLags
  int opt;
  if (optind >= argc) {
    fprintf(stderr, "Usage: %s [-h] [-v] <audio.wav>\n", argv[0]);
    return EXIT_FAILURE;
  }
  while ((opt = getopt(argc, argv, "vh")) != -1) {
    switch (opt) {
    case 'v':
      printf("Version 1.0.4 Alpha\n");
      return EXIT_SUCCESS;
    case 'h':
      printf("Usage: \n");
      printf("[-v] Shows current version\n");
      printf("[-h] Displays help menu and exits\n");
      return EXIT_SUCCESS;
    default:
      fprintf(stderr, "Invalid Option\n Usage: %s [-h] [-v]\n", argv[0]);
      return EXIT_FAILURE;
    }
  }

  // Initiliazing Audio Device & Context
  ALCdevice *device = alcOpenDevice(NULL);
  if (!device) {
    fprintf(stderr,
            "Failed to open your default audio device, please try again\n");
    return 1;
  }

  ALCcontext *context = alcCreateContext(device, NULL);
  if (!context) {
    fprintf(
        stderr,
        "Failed to create a context for your audio device, please try again\n");
    alcCloseDevice(device);
    return 1;
  }

  alcMakeContextCurrent(context);

  // Loading Audio File
  const char *filename = argv[optind];
  SF_INFO sfinfo;
  SNDFILE *sndfile = sf_open(filename, SFM_READ, &sfinfo);
  if (!sndfile) {
    fprintf(stderr, "Failed: Could not open file, maybe file doesn't exist\n");
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);
    return 1;
  }

  ALsizei num = (ALsizei)(sfinfo.frames * sfinfo.channels);
  ALsizei sizeData = num * sizeof(short);
  short *bufferData = malloc(sizeData);

  ALenum format;

  if (sfinfo.channels == 1) {
    format = AL_FORMAT_MONO16;
  } else if (sfinfo.channels == 2) {
    format = AL_FORMAT_STEREO16;
  } else {
    fprintf(stderr, "Unsupported channel count: %d\n", sfinfo.channels);
    sf_close(sndfile);
    return EXIT_FAILURE;
  }

  sf_read_short(sndfile, bufferData, num);
  sf_close(sndfile);

  // Generating Buffers
  alGetError();
  ALuint buffer;
  alGenBuffers(1, &buffer);
  alGetError();

  // Reading Buffer Data
  alBufferData(buffer, format, bufferData, sizeData, sfinfo.samplerate);
  free(bufferData);

  // Generating Sources and Playing Audioe
  ALuint source;
  alGenSources(1, &source);
  alSourcei(source, AL_BUFFER, buffer);

  alSourcePlay(source);

  ALint source_state;
  alGetSourcei(source, AL_SOURCE_STATE, &source_state);
  while (source_state == AL_PLAYING) {
    alGetSourcei(source, AL_SOURCE_STATE, &source_state);
    sleep(1);
  }

  alDeleteSources(1, &source);
  alDeleteBuffers(1, &buffer);

  alcMakeContextCurrent(NULL);
  alcDestroyContext(context);
  alcCloseDevice(device);

  printf("Done Playing the Audio File\n");

  return EXIT_SUCCESS;
}
