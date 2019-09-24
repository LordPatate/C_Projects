#pragma once

struct vector {
  size_t size;
  size_t capacity;
  void** array;
};

struct vector *vect_create();
void vect_push(struct vector* vect, void* elem);
void* vect_pop(struct vector* vect);
void* vect_at(struct vector* vect, size_t i);
void vect_foreach(struct vector* vect, void (*func)(void*));
void vect_free(struct vector* vect);
