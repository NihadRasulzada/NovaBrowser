#include "ui/Components/Icon.hpp"

#include <X11/Xlib.h>

namespace Nova::UI {

void IconNode::Render(Display *display, ::Window window) const {
  switch (m_type) {
  case IconType::Back:
    RenderBack(display, window);
    break;

  case IconType::Forward:
    RenderForward(display, window);
    break;

  case IconType::Reload:
    RenderReload(display, window);
    break;
  }
}

void IconNode::RenderBack(Display *display, ::Window window) const {
  GC gc = XCreateGC(display, window, 0, nullptr);

  const int screen = DefaultScreen(display);

  XSetForeground(display, gc, BlackPixel(display, screen));

  const int center_y = m_bounds.y + m_bounds.height / 2;

  const int left = m_bounds.x + m_bounds.width / 4;

  const int right = m_bounds.x + (m_bounds.width * 3) / 4;

  XDrawLine(display, window, gc, left, center_y, right, center_y);

  XDrawLine(display, window, gc, left, center_y, left + 7, center_y - 7);

  XDrawLine(display, window, gc, left, center_y, left + 7, center_y + 7);

  XFreeGC(display, gc);
}

void IconNode::RenderForward(Display *display, ::Window window) const {
  GC gc = XCreateGC(display, window, 0, nullptr);

  const int screen = DefaultScreen(display);

  XSetForeground(display, gc, BlackPixel(display, screen));

  const int center_y = m_bounds.y + m_bounds.height / 2;

  const int left = m_bounds.x + m_bounds.width / 4;

  const int right = m_bounds.x + (m_bounds.width * 3) / 4;

  XDrawLine(display, window, gc, left, center_y, right, center_y);

  XDrawLine(display, window, gc, right, center_y, right - 7, center_y - 7);

  XDrawLine(display, window, gc, right, center_y, right - 7, center_y + 7);

  XFreeGC(display, gc);
}

void IconNode::RenderReload(Display *display, ::Window window) const {
  GC gc = XCreateGC(display, window, 0, nullptr);

  const int screen = DefaultScreen(display);

  XSetForeground(display, gc, BlackPixel(display, screen));

  const int center_x = m_bounds.x + m_bounds.width / 2;

  const int center_y = m_bounds.y + m_bounds.height / 2;

  const int radius =
      (m_bounds.width < m_bounds.height ? m_bounds.width : m_bounds.height) / 3;

  XDrawArc(display, window, gc, center_x - radius, center_y - radius,
           radius * 2, radius * 2, 45 * 64, 270 * 64);

  XPoint points[3];

  points[0] = {static_cast<short>(center_x + radius),
               static_cast<short>(center_y - 4)};

  points[1] = {static_cast<short>(center_x + radius + 7),
               static_cast<short>(center_y - 4)};

  points[2] = {static_cast<short>(center_x + radius),
               static_cast<short>(center_y + 4)};

  XFillPolygon(display, window, gc, points, 3, Convex, CoordModeOrigin);

  XFreeGC(display, gc);
}

} // namespace Nova::UI
