#include "includes/atulo.h"
#include "includes/ui.h"
#include <unistd.h>

int main(int argc, char *argv[]) {
  init_atulo(argc, argv);
  init_ui();
  draw_ui(argv[optind], &engine, &sound, sample_rate);
  free_atulo();
  return 0;
}
