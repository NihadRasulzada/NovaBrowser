#include "ui/AddressBar.hpp"

namespace Browser::UI {

AddressBar::AddressBar()
    : m_x(140), m_y(10), m_width(300), m_height(32), m_focused(false) {}

void AddressBar::Resize(int width) { m_width = width - m_x - 20; }

void AddressBar::Render(Display *display, ::Window window, int y) {

  GC gc = XCreateGC(display, window, 0, nullptr);

  const int screen = DefaultScreen(display);

  XSetForeground(display, gc, BlackPixel(display, screen));

  XDrawRectangle(display, window, gc, m_x, y + m_y, m_width, m_height);

  const char *text = "Search or enter address";

  XDrawString(display, window, gc, m_x + 12, y + m_y + 21, text, 23);

  XFreeGC(display, gc);
}

void AddressBar::MouseButtonDown(int x, int y) { m_focused = Contains(x, y); }

bool AddressBar::Contains(int x, int y) const {
  return x >= m_x && x <= m_x + m_width && y >= m_y && y <= m_y + m_height;
}

} // namespace Browser::UI
