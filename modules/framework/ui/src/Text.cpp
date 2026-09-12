#include "ui/Components/Text.hpp"
#include <iostream>

#include <X11/Xlib.h>

namespace Nova::UI {

void TextNode::Render(Display *display, ::Window window, GC gc) const {
  std::cout << "Text: "
            << "x=" << m_bounds.x << " y=" << m_bounds.y
            << " width=" << m_bounds.width << " height=" << m_bounds.height
            << '\n';

  const int screen = DefaultScreen(display);

  XSetForeground(display, gc, BlackPixel(display, screen));

  XDrawString(display, window, gc, m_bounds.x, m_bounds.y + 16, m_text.c_str(),
              static_cast<int>(m_text.size()));

  XFreeGC(display, gc);
}

} // namespace Nova::UI
