#pragma once
#include "ui/Core/View.hpp"
#include <X11/Xlib.h>
#include <memory>

namespace Browser {

class BrowserUI {
public:
  BrowserUI();

  void Resize(int width, int height);
  void Render(Display *display, ::Window window);

private:
  Nova::UI::View Build();

private:
  int m_width = 0;
  int m_height = 0;
  Nova::UI::View m_root{nullptr};
};

} // namespace Browser
