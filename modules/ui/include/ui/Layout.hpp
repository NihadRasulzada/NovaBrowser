#pragma once

namespace Nova::UI {
struct Rect {
  int x = 0;
  int y = 0;
  int width = 0;
  int height = 0;

  bool Contains(int px, int py) const {
    return px >= x && px <= x + width && py >= y && py <= y + height;
  }
};
} // namespace Nova::UI
