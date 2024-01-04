#include "editor.hpp"
#include "common.hpp"
#include "raylib.h"
#include <raygui.h>

void TilePicker::Update() {
  if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_S)) {
    map->SaveToFile("test");
  }
  if (IsKeyDown(KEY_LEFT_CONTROL) && IsKeyPressed(KEY_O)) {
    map->LoadFromFile("test");
  }
  if (IsKeyPressed(KEY_T)) {
    show = !show;
  }
}

void TilePicker::Draw() {
  if (!show) {
    GuiPanel(Rectangle({WIDTH - 48, 0, 48, HEIGHT}), "Tiles");
  }
}
