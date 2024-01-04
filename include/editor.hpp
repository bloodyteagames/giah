#pragma once
#include "map.hpp"
#include <raylib.h>

class TilePicker {
public:
  const bool SOLIDS[3] = {true, true, false};
  int currentTile = 0;
  Map *map;
  bool show = false;

public:
  void Update();
  void Draw();
};
