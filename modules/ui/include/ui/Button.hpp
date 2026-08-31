#pragma once

#include <X11/Xlib.h>

namespace Browser::UI {

class Button {
public:
  Button(int x, int y, int width, int height, const char *label);

  void Render(Display *display, ::Window window, int y);

  bool Contains(int x, int y) const;

private:
  int m_x;
  int m_y;
  int m_width;
  int m_height;

  const char *m_label;
};

} // namespace Browser::UI
