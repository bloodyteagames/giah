#include "entities/player.hpp"
#include "assets.hpp"
#include "map.hpp"
#include "raylib.h"

void Player::Update(Map &map) {
  if (m_canMove) {
    if (IsKeyDown(KEY_D)) {
      vel.x = m_speed;
      m_canMove = false;
      m_frame = RUN_RIGHT;
    } else if (IsKeyDown(KEY_A)) {
      vel.x = -m_speed;
      m_canMove = false;
      m_frame = RUN_LEFT;
    } else if (IsKeyDown(KEY_S)) {
      vel.y = m_speed;
      m_canMove = false;
    } else if (IsKeyDown(KEY_W)) {
      vel.y = -m_speed;
      m_canMove = false;
    }
  }

  // Horizontal collisions
  if (map.GetSolid((pos.x + vel.x) / 8, pos.y / 8) ||
      map.GetSolid((pos.x + 7 + vel.x) / 8, pos.y / 8)) {
    vel.x = 0;
    m_frame = IDLE;
    m_canMove = true;
  }
  pos.x += vel.x;

  // Vertical collisions
  if (map.GetSolid(pos.x / 8, (pos.y + vel.y) / 8) ||
      map.GetSolid(pos.x / 8, (pos.y + 7 + vel.y) / 8)) {
    vel.y = 0;
    m_frame = IDLE;
    m_canMove = true;
  }
  pos.y += vel.y;
}

void Player::Draw() {
  DrawTextureRec(Assets::get().GetTexture("player"),
                 Rectangle({(float)m_frame * 8, 0, 8, 8}), pos, WHITE);
}
