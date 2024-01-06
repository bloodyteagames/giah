#include "assets.hpp"
#include "common.hpp"
#include "core.hpp"
#include "map.hpp"
#include "player.hpp"
#include <raylib.h>
#include <raymath.h>

static Map map;
static Player player;
static std::vector<Rectangle> coins(32);
static std::vector<Rectangle> bouncers(32);

bool debug = false;

void ResetLevel() {
  coins.clear();
  bouncers.clear();
}
void CreatePlayer(int x, int y) {
  player.pos = Vector2({(float)x, (float)y});
  player.vel = Vector2Zero();
}
void CreateCoin(int x, int y) {
  coins.push_back(Rectangle({(float)x + 2, (float)y + 2, 4, 4}));
}
void CreateBouncer(int x, int y, Vector2 vel) {
  (void)vel;
  bouncers.push_back(Rectangle({(float)x + 2, (float)y + 2, 4, 4}));
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

  player.Update(map);
}

void DRAW() {
  ClearBackground(BLACK);

  map.Draw();
  player.Draw();

  for (auto coin : coins) {
    DrawRectangleRec(coin, YELLOW);
  }
  for (auto bouncer : bouncers) {
    DrawRectangleRec(bouncer, RED);
  }

  if (debug)
    DrawFPS(0, 0);
}

void EXIT() {}
