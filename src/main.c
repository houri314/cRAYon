#include <stdio.h>
#include <raylib.h>
#include <stdlib.h>
#include <string.h>

#include <canvas.h>
#include <pixel.h>

void updateTitle(const PixelData* brush) {
  SetWindowTitle(
      TextFormat("cRAYon - brush size: %g, color: #%08x", brush->size, ColorToInt(brush->col))
      );
}

int main(int argc, char** argv) {
  //Create a window for choosing canvas size.
  SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
  InitWindow(800, 600, "cRAYon - resize window and press O to open new canvas");

  Vector2 windowSize;
  while (!IsKeyPressed(KEY_O)) {
    windowSize = (Vector2){
      .x = GetRenderWidth(),
      .y = GetRenderHeight()
    };
    BeginDrawing();
      ClearBackground(WHITE);
    EndDrawing();
      //Exit if exit event received (if I put this as while() condition
      //the canvas window will open on exit).
      if (WindowShouldClose()) return 0;
  }
  CloseWindow();

  //Create the actual window for painting.
  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(windowSize.x, windowSize.y, "cRAYon");
  Canvas* canvas = newCanvas();
  PixelData brush = {
    .size = 10.0f,
    .col = BLACK
  };
  RenderTexture renderCanvas = LoadRenderTexture(windowSize.x, windowSize.y);
  Image icon = LoadImageFromTexture(renderCanvas.texture);
  float windowOpacity = 1.0f;
  while (!WindowShouldClose()) {
      brush.pos = GetMousePosition();

      //Update window title with brush size.
      updateTitle(&brush);

      //Sets canvas as window icon on pen up.
      if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) || IsKeyReleased(KEY_Z)) {
        if (IsImageReady(icon))
          UnloadImage(icon);
        canvas->img = &icon;
        icon = LoadImageFromTexture(renderCanvas.texture);
        ImageFlipVertical(&icon);
        SetWindowIcon(icon);
      }

      //User input: left mouse/Z: pen down.
      if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) || IsKeyDown(KEY_Z))
        canvasAddPixel(canvas, brush);

      //User input: F3: write
      if (IsKeyPressed(KEY_F3))
        exportCanvas(canvas);

      //User input: A: increase brush size, with shift: decrease brush size
      if (IsKeyPressed(KEY_A)) {
        if (IsKeyDown(KEY_LEFT_SHIFT)) {
          if (brush.size > 1) brush.size -= 0.5;
        }
        else brush.size += 0.5;
      }

      //User input: T: increase window opacity, with shift: decrease window opacity
      if (IsKeyPressed(KEY_T)) {
        if (IsKeyDown(KEY_LEFT_SHIFT)) {
          if (windowOpacity > 0) windowOpacity -= 0.2;
        }
        else {
          if (windowOpacity < 1) windowOpacity += 0.2;
        }
        SetWindowOpacity(windowOpacity);
      }

      //User input: Tab: switch brush color
      if (IsKeyPressed(KEY_TAB)) {
        brush.col.r = ~brush.col.r;
        brush.col.g = ~brush.col.g;
        brush.col.b = ~brush.col.b;
      }

    BeginTextureMode(renderCanvas);
      ClearBackground(WHITE);
      drawCanvas(canvas);
    EndTextureMode();
    BeginDrawing();
      DrawTexturePro(
        renderCanvas.texture,
        (Rectangle){0, windowSize.y, windowSize.x, -windowSize.y},
        (Rectangle){0, 0, windowSize.x, windowSize.y},
        (Vector2){0, 0},
        0,
        WHITE
      );
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
