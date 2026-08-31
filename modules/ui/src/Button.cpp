#include "ui/Button.hpp"

namespace Browser::UI {

Button::Button(int x, int y, int width, int height, const char *label)
    : m_x(x), m_y(y), m_width(width), m_height(height), m_label(label) {}

void Button::Render(Display *display, ::Window window, int y) {

  GC gc = XCreateGC(display, window, 0, nullptr);

  const int screen = DefaultScreen(display);

  XSetForeground(display, gc, BlackPixel(display, screen));

  XDrawRectangle(display, window, gc, m_x, y + m_y, m_width, m_height);

  XDrawString(display, window, gc, m_x + 15, y + m_y + 21, m_label, 1);

  XFreeGC(display, gc);
}

bool Button::Contains(int x, int y) const {

  return x >= m_x && x <= m_x + m_width && y >= m_y && y <= m_y + m_height;
}

} // namespace Browser::UI
