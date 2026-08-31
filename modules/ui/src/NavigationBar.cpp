#include "ui/NavigationBar.hpp"
#include <X11/X.h>
#include <X11/Xlib.h>

namespace Browser::UI {
namespace {
void DrawButton(Display *display, ::Window window, GC gc, int left,
                const char *text) {
  XDrawRectangle(display, window, gc, left, 10, 36, 32);

  XDrawString(display, window, gc, left + 15, 31, text, 1);
}
} // namespace
void NavigationBar::Resize(int width) { m_width = width; }

void NavigationBar::Render(Display *display, ::Window window) {
  GC gc = XCreateGC(display, window, 0, nullptr);

  const int screen = DefaultScreen(display);

  XSetForeground(display, gc, BlackPixel(display, screen));

  DrawButton(display, window, gc, 10, "<");
  DrawButton(display, window, gc, 50, ">");
  DrawButton(display, window, gc, 90, "R");

  XDrawRectangle(display, window, gc, 140, 10, m_width - 160, 32);

  const char *placeholder = "Search or enter address";

  XDrawString(display, window, gc, 152, 31, placeholder, 23);

  XFreeGC(display, gc);
}

void NavigationBar::MouseButtonDown(int x, int y) {}
} // namespace Browser::UI
