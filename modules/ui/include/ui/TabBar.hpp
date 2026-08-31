#pragma once

#include <X11/Xlib.h>

namespace Browser::UI {

class TabBar {
public:
  void Resize(int width);

  void Render(Display *display, ::Window window);

  void MouseButtonDown(int x, int y);

private:
  int m_width = 0;
};

} // namespace Browser::UI
