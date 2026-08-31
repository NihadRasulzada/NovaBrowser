#include "ui/BrowserUI.hpp"

namespace Browser::UI {

namespace {

constexpr int TabBarHeight = 36;
constexpr int NavigationBarHeight = 52;

} // namespace

void BrowserUI::Resize(int width, int height) {
  m_width = width;
  m_height = height;

  m_tab_bar.Resize(width);
  m_navigation_bar.Resize(width);
}

void BrowserUI::Render(Display *display, ::Window window) {
  m_tab_bar.Render(display, window);

  m_navigation_bar.Render(display, window);
}

void BrowserUI::MouseMove(int x, int y) {}

void BrowserUI::MouseButtonDown(int x, int y) {
  if (y < TabBarHeight) {
    m_tab_bar.MouseButtonDown(x, y);

    return;
  }

  if (y < TabBarHeight + NavigationBarHeight) {
    m_navigation_bar.MouseButtonDown(x, y - TabBarHeight);
  }
}

} // namespace Browser::UI
