#include "brainfuck.h"

void bye(int status, void* arg) {
  (void) status;
  struct globals* glob = arg;
  vect_free(glob->stack);
  free(glob);
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    errx(1, "Invalid arguments.\n%s", BRAINFUCK_USAGE);
  }

  struct globals* glob = glob_get();
  glob->instructions = argv[1];

  if (on_exit(bye, glob) != 0)
    err(1, "on_exit");

  while (*glob->instructions)
    exec(glob);

  return 0;
}
