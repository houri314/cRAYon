#ifndef BRUSH_H
#define BRUSH_H
#include <raylib.h>
#include <stdint.h>
#include <stddef.h>

typedef struct {
  Vector2 pos;
  float size;
  Color col;
} BrushData;

#endif  //BRUSH_H
