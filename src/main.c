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
  SetTraceLogLevel(LOG_ALL);
  SetConfigFlags(FLAG_VSYNC_HINT);
  InitWindow(800, 600, "cRAYon");

  Canvas* canvas = newCanvas();
  PixelData brush = {
    .size = 10.0f,
    .col = BLACK
  };
  RenderTexture renderCanvas = LoadRenderTexture(800, 600);
  Image icon = LoadImageFromTexture(renderCanvas.texture);
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

      //User input: w: write
      if (IsKeyPressed(KEY_F3))
        exportCanvas(canvas);

    BeginTextureMode(renderCanvas);
      ClearBackground(RAYWHITE);
      drawCanvas(canvas);
    EndTextureMode();
    BeginDrawing();
      DrawTexturePro(
        renderCanvas.texture,
        (Rectangle){0, 600, 800, -600},
        (Rectangle){0, 0, 800, 600},
        (Vector2){0, 0},
        0,
        WHITE
      );
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
