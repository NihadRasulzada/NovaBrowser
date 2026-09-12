#include "ui/Components/Button.hpp"

#include <X11/Xlib.h>

namespace Nova::UI {

void ButtonNode::Layout(const Rect &bounds) {
  m_bounds = bounds;

  if (m_child.GetNode()) {
    m_child->Layout(bounds);
  }
}

void ButtonNode::Render(Display *display, ::Window window, GC gc) const {
  const int screen = DefaultScreen(display);

  XSetForeground(display, gc, BlackPixel(display, screen));

  XDrawRectangle(display, window, gc, m_bounds.x, m_bounds.y, m_bounds.width,
                 m_bounds.height);

  XFreeGC(display, gc);

  if (m_child.GetNode()) {
    m_child->Render(display, window, gc);
  }
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
