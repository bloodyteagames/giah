#pragma once

#include "entities/entity.hpp"
#include "map.hpp"
#include <raylib.h>

class Player : public Entity {
public:
  void Update(Map &map);
  void Draw() override;

private:
  enum FRAMES { IDLE, RUN_RIGHT, RUN_LEFT };
  FRAMES m_frame = IDLE;
  bool m_canMove = true;
  float m_speed = 4.0;
};
