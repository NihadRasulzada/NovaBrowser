#include "ui/Components/Button.hpp"

#include <iostream>

namespace Nova::UI {

void ButtonNode::Render(Display *display, ::Window window) const {
  std::cout << "Button: "
            << "x=" << m_bounds.x << " y=" << m_bounds.y
            << " width=" << m_bounds.width << " height=" << m_bounds.height
            << '\n';
  GC gc = XCreateGC(display, window, 0, nullptr);
  const int screen = DefaultScreen(display);
  XSetForeground(display, gc, BlackPixel(display, screen));
  XDrawRectangle(display, window, gc, m_bounds.x, m_bounds.y, m_bounds.width,
                 m_bounds.height);
  XDrawString(display, window, gc, m_bounds.x + 12, m_bounds.y + 21,
              m_label.c_str(), static_cast<int>(m_label.size()));
  XFreeGC(display, gc);
}

bool ButtonNode::MouseButtonDown(int x, int y) {
  if (!m_bounds.Contains(x, y)) {
    return false;
  }
  if (m_on_click) {
    m_on_click();
  }
  return true;
}

} // namespace Nova::UI
