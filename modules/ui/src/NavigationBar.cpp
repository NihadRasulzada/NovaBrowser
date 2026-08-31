#include "ui/NavigationBar.hpp"

namespace Browser::UI {

namespace {

constexpr int NavigationBarHeight = 52;

}

NavigationBar::NavigationBar()
    : m_back_button(10, 10, 36, 32, "<"),

      m_forward_button(50, 10, 36, 32, ">"),

      m_reload_button(90, 10, 36, 32, "R") {}

void NavigationBar::Resize(int width) { m_address_bar.Resize(width); }

void NavigationBar::Render(Display *display, ::Window window, int y) {

  m_back_button.Render(display, window, y);

  m_forward_button.Render(display, window, y);

  m_reload_button.Render(display, window, y);

  m_address_bar.Render(display, window, y);
}

void NavigationBar::MouseButtonDown(int x, int y) {

  if (m_back_button.Contains(x, y)) {
    return;
  }

  if (m_forward_button.Contains(x, y)) {
    return;
  }

  if (m_reload_button.Contains(x, y)) {
    return;
  }

  if (m_address_bar.Contains(x, y)) {
    m_address_bar.MouseButtonDown(x, y);
  }
}

} // namespace Browser::UI
