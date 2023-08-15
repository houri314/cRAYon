#include <stdio.h>
#include <canvas.h>
#include <stdlib.h>

static size_t hashCanvas(const Canvas* cv) {
  size_t res = 0;
  for (size_t x=0; x<cv->image.width; x++) {
    for (size_t y=0; y<cv->image.height; y++) {
      Color tmp = canvasGetColor(cv, (Vector2){x, y});
      res += tmp.a * 13 + tmp.r * 23 + tmp.g >> 2 * tmp.b;
    }
  }
  return res;
}

void exportCanvas(const Canvas* cv) {
  ExportImage(cv->image, TextFormat("%lu.png", hashCanvas(cv)));
}
