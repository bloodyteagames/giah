#include "assets.hpp" #include "common.hpp"
#include "core.hpp"
#include "map.hpp"
#include "player.hpp"
#include <raylib.h>

static Map map;
static Player player;

bool debug = false;

class DebugUI {
public:
  Map *map;

private:
  bool m_showTilePicker = false;
  bool m_tileMode = false;

public:
  void Update() {
    if (IsKeyPressed(KEY_T)) {
      m_tileMode = !m_tileMode;
    }

    if (m_tileMode) {
      if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        map->SetTile(GetMouseX() / 8, GetMouseY() / 8, 0, true);
      } else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        map->SetTile(GetMouseX() / 8, GetMouseY() / 8, 2, false);
      }

      if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S)) {
        map->SaveToFile("res/data/test.json");
      }

      if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_O)) {
        map->LoadFromFile("res/data/test.json");
      }
    }
  }

  void Draw() {
    if (m_showTilePicker) {
      DrawRectangle(2, 2, 68, 12, Color({15, 15, 15, 200}));
      DrawRectangleLines(2, 2, 68, 12, WHITE);
    } else if (m_tileMode) {
      DrawTextureRec(
          Assets::get().GetTexture("tiles"), Rectangle({0, 0, 8, 8}),
          Vector2({((GetMouseX() / 8) * 8), ((GetMouseY() / 8) * 8)}), WHITE);
    }
  }
} debugUI;

void INIT() {
  Assets::get().AddTexture("player", "res/images/player.png");
  Assets::get().AddTexture("tiles", "res/images/tiles.png");

  debugUI.map = &map;
  player.pos = Vector2({32, 32});

  // map.LoadFromFile("res/data/test.json");
}

void UPDATE() {
  if (IsKeyPressed(KEY_F1)) {
    debug = !debug;
  }

  if (debug) {
    debugUI.Update();
  }

  player.Update(map);
}

void DRAW() {
  ClearBackground(BLACK);

  map.Draw();
  player.Draw();

  if (debug) {
    debugUI.Draw();
  }
}

void EXIT() {}
