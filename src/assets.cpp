#include "assets.hpp"
#include <raylib.h>
#include <string>

Assets::Assets() {}
Assets::~Assets() {}

void Assets::AddTexture(std::string name, std::string path) {
  Texture2D tex = LoadTexture(path.c_str());
  m_textures[name] = tex;
}
