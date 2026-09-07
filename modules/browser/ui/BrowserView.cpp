// BrowserView.cpp
#include "ui/BrowserView.hpp"

namespace Nova::UI {
void BrowserViewNode::Render(Display *display, ::Window window) const {
  const int screen = DefaultScreen(display);
  GC gc = XCreateGC(display, window, 0, nullptr);
  XSetForeground(display, gc, WhitePixel(display, screen));
  XFillRectangle(display, window, gc, m_bounds.x, m_bounds.y, m_bounds.width,
                 m_bounds.height);
  XFreeGC(display, gc);
  // TODO: rendering::Renderer / PaintContext buraya bağlanacaq.
}
} // namespace Nova::UI
