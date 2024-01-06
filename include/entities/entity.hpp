#pragma once

#include "map.hpp"
#include <raylib.h>

class Entity {
public:
  int id;
  Vector2 pos, vel;

  virtual void Update(Map &map) = 0;
  virtual void Draw() = 0;
  ~Entity() {}
};
