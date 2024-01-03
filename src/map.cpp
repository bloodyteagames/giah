#include "map.hpp"
#include "assets.hpp"
#include "common.hpp"
#include "raylib.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

// TODO:
// - Load map from file
// - Create simple editor

// BUG:
// - Map save file accessing memory outside of array(??)
// - Segfault when loading files, possibly due to save file corrution

Map::Map() {
  m_sprites.reserve(30 * 17);
  m_solids.reserve(30 * 17);

  for (int y = 0; y < 17; y++) {
    for (int x = 0; x < 30; x++) {
      if (x == 0 || x == 29 || y == 0 || y == 16)
        SetTile(x, y, 0, true);
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

void Map::SaveToFile(std::string path) {
  std::fstream fs;
  fs.open("res/data/" + path + ".json",
          std::fstream::out | std::fstream::trunc);
  nlohmann::json map_data;

  for (int i = 0; i < (30 * 17); i++) {
    map_data["sprites"][i] = m_sprites[i];
    map_data["solids"][i] = m_solids[i];
  }

  fs << std::setw(4) << map_data;
  TraceLog(LOG_DEBUG, TextFormat("Saving map to file :'%s'", path.c_str()));
  fs.close();
}

void Map::LoadFromFile(std::string path) {
  std::fstream fs;
  fs.open("res/data/" + path + ".json");
  if (!fs.is_open()) {
    TraceLog(LOG_ERROR, TextFormat("Failed to load file '%s'",
                                   ("res/data/" + path + ".json").c_str()));
    return;
  }

  nlohmann::json map_data = nlohmann::json::parse(fs);
  fs.close();

  for (int i = 0; i < (30 * 17); i++) {
    m_sprites[i] = map_data["sprites"][i];
    m_solids[i] = map_data["solids"][i];
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
