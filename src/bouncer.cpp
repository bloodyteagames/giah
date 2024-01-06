#include "entities/bouncer.hpp"
#include "common.hpp"
#include "raylib.h"

Bouncer::Bouncer(int _id, int x, int y, Vector2 velocity) {
  id = _id;
  pos = Vector2({(float)x, (float)y});
  vel = velocity;
}

void Bouncer::Update(Map &map) {
  // Horizontal collisions
  if (map.GetSolid((pos.x + vel.x) / 8, pos.y / 8) ||
      map.GetSolid((pos.x + 7 + vel.x) / 8, pos.y / 8)) {
    vel.x = -vel.x;
  }
  pos.x += vel.x;

  // Vertical collisions
  if (map.GetSolid(pos.x / 8, (pos.y + vel.y) / 8) ||
      map.GetSolid(pos.x / 8, (pos.y + 7 + vel.y) / 8)) {
    vel.y = -vel.y;
  }
  pos.y += vel.y;
}

void Bouncer::Draw() { DrawRectangle(pos.x, pos.y, 8, 8, RED); }
