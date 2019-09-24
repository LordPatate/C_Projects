#include "brainfuck.h"

void unknown_symbol(struct globals* glob) {
  (void) glob;
  errx(2, "unknown symbol");
}

void left_bracket(struct globals* glob) {
  vect_push(glob->stack, glob->instructions);

  glob->instructions += 1;
}

void right_bracket(struct globals* glob) {
  char* left_bracket_pos = vect_pop(glob->stack);

  if (glob->buffer[glob->pointer] == 0)
    glob->instructions += 1;
  else
    glob->instructions = left_bracket_pos;
}

void step_right(struct globals* glob) {
  glob->pointer += 1;

  glob->instructions += 1;
}

void step_left(struct globals* glob) {
  glob->pointer -= 1;

  glob->instructions += 1;
}

void bump_up(struct globals* glob) {
  glob->buffer[glob->pointer] += 1;

  glob->instructions += 1;
}

void bump_down(struct globals* glob) {
  glob->buffer[glob->pointer] -= 1;

  glob->instructions += 1;
}

void input(struct globals* glob) {
  unsigned int x;

  scanf("%ud", &x);
  glob->buffer[glob->pointer] = x;

  glob->instructions += 1;
}

void output(struct globals* glob) {
  unsigned int x = glob->buffer[glob->pointer];

  printf("%u '%c'\n", x, (char)x);

  glob->instructions += 1;
}

static void init_table(void (*handlers[128])(struct globals*)) {
  for (int i = 0; i < 128; ++i)
    handlers[i] = unknown_symbol;

  handlers['['] = left_bracket;
  handlers[']'] = right_bracket;
  handlers['>'] = step_right;
  handlers['<'] = step_left;
  handlers['+'] = bump_up;
  handlers['-'] = bump_down;
  handlers[','] = input;
  handlers['.'] = output;
}

void exec(struct globals* glob) {
  int current = (int)glob->instructions[0];

  static void (*handlers[128])(struct globals*) = {0};
  if (handlers['['] == 0)
    init_table(handlers);

  handlers[current](glob);
}
