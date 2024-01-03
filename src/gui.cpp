#include "gui.hpp"
#include "raylib.h"

static int active = 0;
static int hot = 0;

void BeginGui() { hot = 0; }

void EndGui() {
  if (IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
    active = 0;
  } else {
    if (active == 0) {
      active = -1;
    }
  }
}

bool Button(int id, Rectangle rect, ButtonStyle style) {
  // Check if being hovered
  if (CheckCollisionPointRec(GetMousePosition(), rect)) {
    hot = id;
    if (active == 0 && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
      active = id;
    }
  }

  Color color = style.base;
  if (active == id) {
    color = style.click;
  } else if (hot == id) {
    color = style.hover;
  }

  DrawRectangleRec(rect, color);

  if (active == id && hot == id && IsMouseButtonUp(MOUSE_BUTTON_LEFT)) {
    return true;
  }
  return false;
}
