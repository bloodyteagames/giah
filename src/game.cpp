#include "assets.hpp"
#include "common.hpp"
#include "core.hpp"
#include "entities/bouncer.hpp"
#include "entities/entity.hpp"
#include "entities/player.hpp"
#include "map.hpp"
#include <memory>
#include <raylib.h>
#include <raymath.h>

// TODO: Handle player ->entity collisions

static Map map;
static Player player;
static std::vector<std::shared_ptr<Entity>> entities;

bool debug = false;

void ResetLevel() { entities.clear(); }

void CreatePlayer(int x, int y) {
  player = Player();
  player.pos = Vector2({(float)x, (float)y});
}

void CreateCoin(int x, int y) {
  (void)x;
  (void)y;
}

void CreateBouncer(int id, int x, int y, Vector2 vel) {
  entities.push_back(std::make_shared<Bouncer>(id, x, y, vel));
}

void INIT() {
  Assets::get().AddTexture("player", "res/images/player.png");
  Assets::get().AddTexture("tiles", "res/images/tiles.png");

  SetTraceLogLevel(LOG_ALL);

  player.pos = Vector2({32, 32});
}

void UPDATE() {
  if (IsKeyPressed(KEY_F1)) {
    debug = !debug;
  }

  if (IsKeyPressed(KEY_O))
    map.LoadFromFile("level_1");

  for (auto ent : entities) {
    ent->Update(map);
  }

  player.Update(map);
}

void DRAW() {
  ClearBackground(BLACK);

  map.Draw();
  player.Draw();

  for (auto ent : entities) {
    ent->Draw();
  }
}

void EXIT() {}
