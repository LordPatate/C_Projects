#pragma once

struct globals {
  char* instructions;
  unsigned int buffer[256];
  unsigned char pointer;
  struct vector* stack;
};

struct globals* glob_get();
