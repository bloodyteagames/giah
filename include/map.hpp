#pragma once
#include <string>

struct Tile {
  int index;
  bool isSolid;
};

class Map {
public:
  Map();
  ~Map();

  Tile &GetTile(int x, int y);
  void SetTile(int x, int y, int id, bool isSolid);

  void SaveToFile(std::string path);
  void LoadFromFile(std::string path);

  void Draw();

private:
  enum TILES { WALL, WALL_V, FLOOR, FLOOR_V };
  Tile m_data[30 * 17];
};
