#include "brainfuck.h"

static struct globals* glob_accessor(struct globals* value) {
  static struct globals* glob = NULL;

  if (!glob && value)
    glob = value;

  return glob;
}

static struct globals* glob_init() {
    struct globals* glob = malloc(sizeof(struct globals));
    if (!glob)
      err(1, "glob initialisation");

    for (int i = 0; i < 256; ++i)
      glob->buffer[i] = 0;
    glob->pointer = 0;
    glob->stack = vect_create();

    return glob_accessor(glob);
}

struct globals* glob_get() {
  struct globals* glob = glob_accessor(NULL);

  if (!glob)
    glob = glob_init();

  return glob;
}
