#include "assets.hpp"
#include "common.hpp"
#include "core.hpp"
#include "editor.hpp"
#include "map.hpp"
#include "player.hpp"
#include <raylib.h>
#include <raymath.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>
#undef RAYGUI_IMPLEMENTATION

static Map map;
static Player player;

bool debug = false;

TilePicker picker;
int showPicker = 0;

void INIT() {
  Assets::get().AddTexture("player", "res/images/player.png");
  Assets::get().AddTexture("tiles", "res/images/tiles.png");
  SetTraceLogLevel(LOG_ALL);
  GuiLoadStyle("res/styles/style_dark.rgs");

  picker.map = &map;
  player.pos = Vector2({32, 32});
}

void UPDATE() {
  if (IsKeyPressed(KEY_F1)) {
    debug = !debug;
  }

  if (debug) {
    picker.Update();
  }

  if (picker.show)
    player.Update(map);
}

void DRAW() {
  ClearBackground(BLACK);

  map.Draw();
  player.Draw();

  if (debug) {
    DrawRectangleLines(GetMouseX() / 8 * 8, GetMouseY() / 8 * 8, 8, 8, WHITE);
    picker.Draw();
  }
}

void EXIT() {}
