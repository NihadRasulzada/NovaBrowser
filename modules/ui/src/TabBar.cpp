#include "ui/TabBar.hpp"
#include <X11/X.h>
#include <X11/Xlib.h>

namespace Browser::UI {
void TabBar::Resize(int width) { m_width = width; }

void TabBar::Render(Display *display, ::Window window, int y) {
  const int screen = DefaultScreen(display);

  GC gc = XCreateGC(display, window, 0, nullptr);

  XSetForeground(display, gc, WhitePixel(display, screen));

  XFillRectangle(display, window, gc, 8, y + 4, 212, 28);

  XSetForeground(display, gc, BlackPixel(display, screen));

  const char *title = "New Tab";

  XDrawString(display, window, gc, 20, y + 22, title, 7);

  XFreeGC(display, gc);
}

void TabBar::MouseButtonDown(int x, int y) {}
} // namespace Browser::UI
