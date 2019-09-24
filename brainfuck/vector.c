#include "brainfuck.h"

struct vector *vect_create() {
  struct vector *vect = malloc(sizeof(struct vector));
  if (!vect)
    err(2, "vect_create");

  vect->size = 0;
  vect->capacity = 1;
  vect->array = malloc(sizeof(void*));

  return vect;
}

static void vect_expand(struct vector* vect) {
  vect->capacity <<= 1;
  void** p = realloc(vect->array, vect->capacity * sizeof(void*));
  if (!p)
    err(2, "vect_expand");
  vect->array = p;
}

void vect_push(struct vector* vect, void* elem) {
  if (vect->size == vect->capacity)
    vect_expand(vect);

  vect->array[vect->size++] = elem;
}

void* vect_pop(struct vector* vect) {
  if (vect->size == 0)
    errx(1, "vect_pop: empty vector");

  return vect->array[--vect->size];
}

void* vect_at(struct vector* vect, size_t i) {
  if (i > vect->size)
    errx(1, "vect_at: index out of range");

  return vect->array[i];
}

void vect_foreach(struct vector* vect, void (*func)(void*)) {
  for (size_t i = 0; i < vect->size; ++i)
    func(vect->array[i]);
}

void vect_free(struct vector* vect) {
  vect_foreach(vect, free);
  free(vect->array);
  free(vect);
}
