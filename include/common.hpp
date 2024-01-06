#pragma once

#include <raylib.h>

static const int WIDTH = 240;
static const int HEIGHT = 136;

extern bool debug;

void ResetLevel();
void CreatePlayer(int x, int y);
void CreateCoin(int x, int y);
void CreateBouncer(int x, int y, Vector2 vel);
