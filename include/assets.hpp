#pragma once

#include <map>
#include <raylib.h>
#include <string>

class Assets {
public:
  static Assets &get() {
    static Assets inst;
    return inst;
  }

  Assets(Assets const &) = delete;
  void operator=(Assets const &) = delete;

  Texture2D &GetTexture(std::string name) { return m_textures[name]; }
  void AddTexture(std::string name, std::string path);

private:
  Assets();
  ~Assets();

  std::map<std::string, Texture2D> m_textures;
  std::map<std::string, Font> m_fonts;
};
