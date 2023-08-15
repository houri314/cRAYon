#include <stdio.h>
#include <canvas.h>
#include <stdlib.h>

static size_t hashCanvas(const Canvas* cv) {
  size_t res = 0;
  //TODO: fill this later.
  return res;
}

void exportCanvas(const Canvas* cv) {
  ExportImage(cv->image, TextFormat("%ld.png", hashCanvas(cv)));
}
