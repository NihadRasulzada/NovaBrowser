#pragma once

#include <X11/Xlib.h>

#include "NavigationBar.hpp"
#include "TabBar.hpp"

namespace Browser::UI {

class BrowserUI {
public:
  void Resize(int width, int height);

  void Render(Display *display, ::Window window);

  void MouseMove(int x, int y);

  void MouseButtonDown(int x, int y);

private:
  int m_width = 0;
  int m_height = 0;

  TabBar m_tab_bar;
  NavigationBar m_navigation_bar;
};

} // namespace Browser::UI
