#pragma once

#include <X11/Xlib.h>

namespace Browser::UI {

class AddressBar {
public:
  AddressBar();

  void Resize(int width);

  void Render(Display *display, ::Window window, int y);

  void MouseButtonDown(int x, int y);

  bool Contains(int x, int y) const;

private:
  int m_x;
  int m_y;
  int m_width;
  int m_height;

  bool m_focused;
};

} // namespace Browser::UI
