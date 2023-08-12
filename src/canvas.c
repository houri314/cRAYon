#include <canvas.h>
#include <raylib.h>
#include <stdlib.h>

Canvas* newCanvas() {
  Canvas* cv = malloc(sizeof(Canvas));
  cv->first = cv->current = NULL;
  cv->pixelCount = 0;

  return cv;
}

void drawCanvas(const Canvas* cv) {
  if (cv->pixelCount == 0)
    return;

  PixelData* tmp = cv->first;
  for (size_t i=0; i<cv->pixelCount; i++) {
    if (tmp == NULL)
      return;
    DrawCircleV(tmp->pos, tmp->size, tmp->col);
    tmp = tmp->next;
  }
}

/*
 * I'm really unsatisfied with the implementation of this function.
 * Everytime I tried it gives some weird errors so I have to resort to
 * writing this ugly thing.
 */
void canvasAddPixel(Canvas* cv, PixelData data) {
  if (!cv->current)
    cv->current = malloc(sizeof(PixelData));
  cv->current->pos = data.pos;
  cv->current->size = data.size;
  cv->current->col = data.col;

  if (cv->pixelCount == 0)
    cv->first = cv->current;

  cv->current->next = malloc(sizeof(PixelData));
  cv->current = cv->current->next;
  cv->pixelCount++;
}
