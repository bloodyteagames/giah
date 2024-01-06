#pragma once
#include <string>
#include <vector>

class Map {
public:
  Map();
  ~Map();

  int GetSprite(int x, int y) { return m_sprites[y * 30 + x]; }
  bool GetSolid(int x, int y) { return m_solids[y * 30 + x]; }

  void SetSprite(int x, int y, int index);
  void SetSolid(int x, int y, bool solid);
  void SetTile(int x, int y, int index, bool solid);

  void LoadFromFile(std::string path);

  void Draw();

private:
  enum TILES { WALL, WALL_V, FLOOR, FLOOR_V };
  std::vector<int> m_sprites;
  std::vector<int> m_solids;
};
