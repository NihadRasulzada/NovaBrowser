#include "ui/TabBar.hpp"

namespace Nova::UI {
void TabBarNode::Render(Display *display, ::Window window) const {
  const int screen = DefaultScreen(display);
  GC gc = XCreateGC(display, window, 0, nullptr);
  XSetForeground(display, gc, WhitePixel(display, screen));
  XFillRectangle(display, window, gc, m_bounds.x + 8, m_bounds.y + 4, 212, 28);
  XSetForeground(display, gc, BlackPixel(display, screen));
  const char *title = "New Tab";
  XDrawString(display, window, gc, m_bounds.x + 20, m_bounds.y + 22, title, 7);
  XFreeGC(display, gc);
}
} // namespace Nova::UI
