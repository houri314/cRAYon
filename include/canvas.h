#ifndef CANVAS_H
#define CANVAS_H
#include <brush.h>
#include <raylib.h>
#include <stdint.h>
#include <stddef.h>

typedef struct {
  Image image;
  Texture2D texture;
} Canvas;

void drawCanvas(const Canvas*);
void canvasBrush(Canvas*, const BrushData*);
void updateCanvas(Canvas*);
void exportCanvas(const Canvas*);

#endif  //CANVAS_H
