#include "ui/TextField.hpp"

namespace Nova::UI {

void TextFieldNode::Render(Display *display, ::Window window) const {
  GC gc = XCreateGC(display, window, 0, nullptr);
  const int screen = DefaultScreen(display);
  XSetForeground(display, gc, BlackPixel(display, screen));
  XDrawRectangle(display, window, gc, m_bounds.x, m_bounds.y, m_bounds.width,
                 m_bounds.height);
  const std::string &text = m_value.empty() ? m_placeholder : m_value;
  XDrawString(display, window, gc, m_bounds.x + 12, m_bounds.y + 21,
              text.c_str(), static_cast<int>(text.size()));
  XFreeGC(display, gc);
}

bool TextFieldNode::MouseButtonDown(int x, int y) {
  m_focused = m_bounds.Contains(x, y);
  return m_focused;
}

void TextFieldNode::KeyDown(char character, bool is_return, bool is_backspace) {
  if (!m_focused)
    return;
  if (is_return) {
    if (m_on_submit)
      m_on_submit(m_value);
    return;
  }
  if (is_backspace) {
    if (!m_value.empty())
      m_value.pop_back();
    return;
  }
  if (character != '\0') {
    m_value.push_back(character);
  }
}

} // namespace Nova::UI
