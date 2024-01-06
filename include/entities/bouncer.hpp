#pragma once

#include "entity.hpp"
#include <raylib.h>

class Bouncer : public Entity {
public:
  Bouncer(int _id, int x, int y, Vector2 velocity);
  void Update(Map &map) override;
  void Draw() override;
};
