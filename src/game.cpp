#include "assets.hpp"
#include "common.hpp"
#include "core.hpp"
#include "editor.hpp"
#include "gui.hpp"
#include "map.hpp"
#include "player.hpp"
#include <raylib.h>
#include <raymath.h>

static Map map;
static Player player;
static bool tileEditMode = false;

static TilePicker picker;

bool debug = false;

void INIT() {
  Assets::get().AddTexture("player", "res/images/player.png");
  Assets::get().AddTexture("tiles", "res/images/tiles.png");

  SetTraceLogLevel(LOG_ALL);

  player.pos = Vector2({32, 32});
}

void UPDATE() {
  if (IsKeyPressed(KEY_F1)) {
    debug = !debug;
  }

  player.Update(map);
}

void DRAW() {
  ClearBackground(BLACK);

  map.Draw();
  player.Draw();

  if (debug) {
    if (IsKeyPressed(KEY_T))
      tileEditMode = !tileEditMode;

    if (tileEditMode) {
      picker.Draw();
    } else {
      if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        map.SetTile(GetMouseX() / 8, GetMouseY() / 8, picker.currentTile,
                    picker.SOLIDS[picker.currentTile]);
      } else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        map.SetTile(GetMouseX() / 8, GetMouseY() / 8, 2, false);
      }
    }
    DrawRectangleLines(GetMouseX() / 8 * 8, GetMouseY() / 8 * 8, 8, 8, WHITE);
  }
}

void EXIT() {}
