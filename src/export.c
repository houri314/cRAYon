#include <stdio.h>
#include <canvas.h>
#include <stdlib.h>

static size_t hashCanvas(const Canvas* cv) {
  size_t res = 0;
  PixelData* tmp = cv->first;
  for (size_t i=0; i<cv->pixelCount; i++) {
    res += tmp->col.a * 13 + tmp->col.r * 23 + tmp->col.g << 2 * tmp->col.b;
    tmp = tmp->next;
  }
  return res;
}

void exportCanvas(const Canvas* cv) {
	if (cv->pixelCount < 1)
		return;
  ExportImage(*(cv->img), TextFormat("%lld.png", hashCanvas(cv)));
}
