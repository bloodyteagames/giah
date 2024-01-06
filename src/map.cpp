#include "map.hpp"
#include "assets.hpp"
#include "common.hpp"
#include "raylib.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

Map::Map() {
  m_sprites.reserve(30 * 17);
  m_solids.reserve(30 * 17);

  for (int y = 0; y < 17; y++) {
    for (int x = 0; x < 30; x++) {
      if (x == 0 || x == 29 || y == 0 || y == 16)
        SetTile(x, y, 1, true);
      else
        SetTile(x, y, 2, false);
    }
  }
}

Map::~Map() {}

void Map::SetSprite(int x, int y, int index) { m_sprites[y * 30 + x] = index; }
void Map::SetSolid(int x, int y, bool solid) { m_solids[y * 30 + x] = solid; }
void Map::SetTile(int x, int y, int index, bool solid) {
  SetSprite(x, y, index);
  SetSolid(x, y, solid);
}

void Map::LoadFromFile(std::string path) {
  std::fstream fs;
  fs.open("res/data/levels/" + path + ".json");
  if (!fs.is_open()) {
    TraceLog(LOG_ERROR,
             TextFormat("Failed to load file '%s'",
                        ("res/data/levels/" + path + ".json").c_str()));
    return;
  }

  nlohmann::json map_data = nlohmann::json::parse(fs);
  fs.close();

  ResetLevel();

  for (int idx = 0; idx < 30 * 17; idx++) {
    m_solids[idx] = map_data["layers"][2]["data"][idx];
    m_sprites[idx] = map_data["layers"][1]["data"][idx];

    auto &ent = map_data["layers"][0]["entities"][idx];

    if (ent["name"] == "Player")
      CreatePlayer(ent["x"], ent["y"]);
    if (ent["name"] == "Coin")
      CreateCoin(ent["x"], ent["y"]);
    if (ent["name"] == "Bouncer")
      CreateBouncer(
          ent["id"], ent["x"], ent["y"],
          Vector2({ent["values"]["hSpeed"], ent["values"]["vSpeed"]}));
  }
}

void Map::Draw() {
  for (int y = 0; y < 17; y++) {
    for (int x = 0; x < 30; x++) {
      // Draw sprites
      DrawTextureRec(Assets::get().GetTexture("tiles"),
                     Rectangle({(float)GetSprite(x, y) * 8, 0, 8, 8}),
                     Vector2({(float)x * 8, (float)y * 8}), WHITE);

      if (debug) {
        if (GetSolid(x, y))
          DrawRectangleLines(x * 8, y * 8, 8, 8, RED);
      }
    }
  }
}
