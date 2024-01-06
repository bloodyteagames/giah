#include "common.hpp"
#include "core.hpp"
#include <algorithm>
#include <raylib.h>

int main(void) {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  InitWindow(640, 480, "GIAH!");
  SetWindowMinSize(WIDTH, HEIGHT);

  // ToggleBorderlessWindowed();

  RenderTexture2D target = LoadRenderTexture(240, 136);
  SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);

  INIT();
  SetWindowState(FLAG_WINDOW_MAXIMIZED);

  SetTargetFPS(60);
  while (!WindowShouldClose()) {
    // Mouse scaling
    float scale = std::min((float)GetScreenWidth() / WIDTH,
                           (float)GetScreenHeight() / HEIGHT);
    SetMouseOffset(-(GetScreenWidth() - (WIDTH * scale)) * 0.5f,
                   -(GetScreenHeight() - (HEIGHT * scale)) * 0.5f);
    SetMouseScale(1 / scale, 1 / scale);

    if (IsKeyDown(KEY_LEFT_ALT) && IsKeyPressed(KEY_ENTER)) {
      ToggleBorderlessWindowed();
    }

    UPDATE();

    BeginTextureMode(target);
    DRAW();
    EndTextureMode();

    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexturePro(
        target.texture,
        Rectangle({0.0f, 0.0f, (float)target.texture.width,
                   (float)-target.texture.height}),
        Rectangle({(GetScreenWidth() - ((float)WIDTH * scale)) * 0.5f,
                   (GetScreenHeight() - ((float)HEIGHT * scale)) * 0.5f,
                   (float)WIDTH * scale, (float)HEIGHT * scale}),
        Vector2({0, 0}), 0.0f, WHITE);
    EndDrawing();
  }

  EXIT();
  CloseWindow();
  return 0;
}
