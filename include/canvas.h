#ifndef CANVAS_H
#define CANVAS_H
#include <pixel.h>
#include <raylib.h>
#include <stdint.h>
#include <stddef.h>

typedef struct {
  PixelData* first;
  PixelData* current;
  Image* img;
  size_t pixelCount;
} Canvas;

Canvas* newCanvas();
void drawCanvas(const Canvas*);
void canvasAddPixel(Canvas*, PixelData);
void exportCanvas(const Canvas*);

#endif  //CANVAS_H
