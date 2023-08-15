#include <canvas.h>
#include <raylib.h>
#include <stdlib.h>

void drawCanvas(const Canvas* cv) {
  DrawTexture(cv->texture, 0, 0, WHITE);
}

void updateCanvas(Canvas* cv) {
  UpdateTexture(cv->texture, cv->image.data);
}

Color canvasGetColor(const Canvas* cv, Vector2 v) {
  return GetImageColor(cv->image, v.x, v.y);
}

/*
 * First solution for a malloc-less canvas.
 * This has its own flaws, since the Image struct is just
 * a glorified void pointer to the data stored in RAM, it's
 * prone to array problems (out of bound), causing weird stuff drawing
 * near the vertical borders and segfaults drawing near the horizontal 
 * borders. I solved it by clamping the cursor between the borders with
 * THRESHOLD. This isn't the best practice but it kinda works now (for a
 * prototype at least).
 */
#define THRESHOLD 2.5
void canvasBrush(Canvas* cv, const BrushData* brush) {
  if (brush->pos.x + brush->size > cv->image.width - THRESHOLD) return;
  if (brush->pos.x - brush->size < THRESHOLD) return;
  if (brush->pos.y + brush->size > cv->image.height - THRESHOLD) return;
  if (brush->pos.y - brush->size < THRESHOLD) return;
  ImageDrawCircleV(&(cv->image), brush->pos, brush->size, brush->col);
}
