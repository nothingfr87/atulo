#include "includes/atulo.h"
#include "includes/keys.h"

int main(int argc, char *argv[]) {
  init_atulo(argc, argv);
  user_keys(argv[1], &engine, &sound, sample_rate);
  free_atulo();
  return 0;
}
