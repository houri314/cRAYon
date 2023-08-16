#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <canvas.h>
#include <brush.h>

void updateTitle(const BrushData* brush) {
  SetWindowTitle(
      TextFormat("cRAYon - brush size: %g, color: #%08x", brush->size, ColorToInt(brush->col))
      );
}

int main(int argc, char** argv) {
  //Create a window for choosing canvas size.
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
  InitWindow(800, 600, "cRAYon - resize window and press O to open new canvas");

  Vector2 windowSize;
  bool fileLoaded = 0;
  FilePathList file;
  while (!IsKeyPressed(KEY_O) && !fileLoaded) {
      windowSize = (Vector2){
        .x = GetRenderWidth(),
        .y = GetRenderHeight()
      };
      if (IsFileDropped()) {
        file = LoadDroppedFiles();
        fileLoaded = 1;
      }
    BeginDrawing();
      ClearBackground(WHITE);
      DrawText("Or you can drag and drop an image file here to open it", 0, 0, 20, BLACK);
    EndDrawing();
      //Exit if exit event received (if I put this as while() condition
      //the canvas window will open on exit).
      if (WindowShouldClose()) return 0;
  }
  CloseWindow();

  //Create the actual window for painting.
  BrushData brush = {
    .size = 10.0f,
    .col = BLACK
  };

  float windowOpacity = 1.0f;
  SetConfigFlags(FLAG_VSYNC_HINT);

  Canvas canvas;
  if (fileLoaded) {
    canvas.image = LoadImage(file.paths[0]);
    UnloadDroppedFiles(file);
    //Resize window to fit loaded image if necessary.
    if (windowSize.x != canvas.image.width || windowSize.y != canvas.image.height)
      windowSize = (Vector2){canvas.image.width, canvas.image.height};
  }
  else
    canvas.image = GenImageColor(windowSize.x, windowSize.y, WHITE);

  InitWindow(windowSize.x, windowSize.y, "cRAYon");

  SetWindowIcon(canvas.image);
  canvas.texture = LoadTextureFromImage(canvas.image);
  while (!WindowShouldClose()) {
      brush.pos = GetMousePosition();
      int8_t mod = -2*(IsKeyDown(KEY_LEFT_SHIFT))+1;

      //Update window title with brush size.
      updateTitle(&brush);

      //Sets canvas as window icon on pen up.
      if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) || IsKeyReleased(KEY_Z)) {
        SetWindowIcon(canvas.image);
      }

      //User input: left mouse/Z: pen down.
      if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsKeyDown(KEY_Z))
        canvasBrush(&canvas, &brush);

      //User input: F3: write
      if (IsKeyPressed(KEY_F3))
        exportCanvas(&canvas);

      //User input: A: increase brush size, with shift: decrease brush size
      if (IsKeyPressed(KEY_A))
        brush.size += 0.5*mod;

      //User input: T: increase window opacity, with shift: decrease window opacity
      if (IsKeyPressed(KEY_T)) {
        windowOpacity += 0.2*mod;
        if (windowOpacity < 0) windowOpacity = 0;
        else if (windowOpacity > 1) windowOpacity = 1;
        SetWindowOpacity(windowOpacity);
      }

      //User input: QWE: change brush color.
      //With Ctrl held: more precise changing.
      if (IsKeyDown(KEY_LEFT_CONTROL)) {
        if (IsKeyPressed(KEY_Q)) brush.col.r += 5*mod;
        if (IsKeyPressed(KEY_W)) brush.col.g += 5*mod;
        if (IsKeyPressed(KEY_E)) brush.col.b += 5*mod;
      }
      else {
        if (IsKeyDown(KEY_Q)) brush.col.r += 1*mod;
        if (IsKeyDown(KEY_W)) brush.col.g += 1*mod;
        if (IsKeyDown(KEY_E)) brush.col.b += 1*mod;
      }

      //User input: Y: yank color under cursor.
      if (IsKeyPressed(KEY_Y))
        brush.col = canvasGetColor(&canvas, brush.pos);

      updateCanvas(&canvas);

    BeginDrawing();
      drawCanvas(&canvas);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
