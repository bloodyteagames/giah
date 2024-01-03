#include "editor.hpp"
#include "assets.hpp"
#include "common.hpp"
#include "gui.hpp"
#include "raylib.h"

static ButtonStyle style = {.base = Color({250, 250, 250, 200}),
                            .hover = Color({150, 150, 150, 200}),
                            .click = Color({50, 50, 50, 200})};

void TilePicker::Draw() {
  DrawRectangle(8, 8, WIDTH - 16, HEIGHT - 16, Color({15, 15, 15, 200}));
  DrawRectangleLines(8, 8, WIDTH - 16, HEIGHT - 16, WHITE);

  BeginGui();
  for (int i = 0; i < 3; i++) {
    if (Button(1 + i, Rectangle({(float)9 + i * 12, 9, 10, 10}), style)) {
      currentTile = i;
    }
    DrawTextureRec(Assets::get().GetTexture("tiles"),
                   Rectangle({(float)i * 8, 0, 8, 8}),
                   Vector2({(float)10 + i * 12, 10}), WHITE);
  }
  EndGui();
}
