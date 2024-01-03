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

void Map::SaveToFile(std::string path) {
  std::fstream fs;
  fs.open(path, std::fstream::out | std::fstream::trunc);

  int spriteIdx[30 * 17];
  bool solids[30 * 17];

  for (int idx = 0; idx < 30 * 17; idx++) {
    Tile &t = GetTile((idx / 30) * 8, (idx % 30) * 8);
    spriteIdx[idx] = t.index;
    solids[idx] = t.isSolid;
  }

  nlohmann::json map_data;

  map_data["sprites"] = spriteIdx;
  map_data["solids"] = solids;

  fs << std::setw(4) << map_data;
  TraceLog(LOG_INFO, TextFormat("Savig map to file :'%s'", path.c_str()));
  fs.close();
}

void Map::LoadFromFile(std::string path) {
  std::fstream fs;
  fs.open(path);
  if (!fs.is_open()) {
    printf("ERROR: Failed to load file!\n");
    return;
  }
  printf("File opened!\n");

  nlohmann::json map_data = nlohmann::json::parse(fs);
  printf("File parsed!\n");
  fs.close();
}

Map::Map() {
  for (int y = 0; y < 17; y++) {
    for (int x = 0; x < 30; x++) {
      if (x == 0 || x == 29 || y == 0 || y == 16)
        SetTile(x, y, 0, true);
      else
        SetTile(x, y, 2, false);
    }
  }
  SetTile(1, 2, 0, true);
}

Map::~Map() {}

Tile &Map::GetTile(int x, int y) { return (m_data[(y / 8) * 30 + (x / 8)]); }

void Map::SetTile(int x, int y, int id, bool isSolid) {
  m_data[y * 30 + x] = Tile({id, isSolid});
}

void Map::Draw() {
  for (int y = 0; y < 17; y++) {
    for (int x = 0; x < 30; x++) {
      // Draw sprites
      DrawTextureRec(Assets::get().GetTexture("tiles"),
                     Rectangle({(float)m_data[y * 30 + x].index * 8, 0, 8, 8}),
                     Vector2({(float)x * 8, (float)y * 8}), WHITE);

      if (debug) {
        if (GetTile(x * 8, y * 8).isSolid)
          DrawRectangleLines(x * 8, y * 8, 8, 8, RED);
      }
    }
  }
}
