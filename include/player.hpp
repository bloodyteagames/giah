#pragma once

#include "map.hpp"
#include <raylib.h>

class Player {
public:
  Vector2 pos;
  Vector2 vel;

  void Update(Map &map);

  void Draw();

private:
  enum FRAMES { IDLE, RUN_RIGHT, RUN_LEFT };
  FRAMES m_frame = IDLE;
  bool m_canMove = true;
  float m_speed = 4.0;
};
