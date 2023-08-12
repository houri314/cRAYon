#ifndef PIXEL_H
#define PIXEL_H
#include <raylib.h>
#include <stdint.h>
#include <stddef.h>

typedef struct PixelData {
  struct PixelData* next;
  Vector2 pos;
  float size;
  Color col;
} PixelData;

#endif  //PIXEL_H
