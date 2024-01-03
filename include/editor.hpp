#pragma once
#include <raylib.h>

class TilePicker {
public:
  const bool SOLIDS[3] = {true, true, false};
  int currentTile = 0;

  void Draw();
};
