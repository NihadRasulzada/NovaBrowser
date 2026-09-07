#pragma once

#include "Window.hpp"

#include <X11/Xlib.h>

namespace Browser::Platform {
class Application {
public:
  Application();
  ~Application();
  int Run(Window::EventHandler event_handler,
          Window::PaintHandler paint_handler);

private:
  Display *m_display;
};

} // namespace Browser::Platform
