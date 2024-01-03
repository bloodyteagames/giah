#pragma once
#include <raylib.h>

struct ButtonStyle {
  Color base = WHITE;
  Color hover = RED;
  Color click = GREEN;
};

void BeginGui();
void EndGui();

bool Button(int id, Rectangle rect, ButtonStyle style);
