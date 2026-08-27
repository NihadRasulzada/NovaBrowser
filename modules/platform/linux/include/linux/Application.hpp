#pragma once

#include <X11/Xlib.h>

namespace Browser::Platform::Linux {
class Application {
public:
  Application();
  ~Application();
  int Run();

private:
  Display *m_display;
};

} // namespace Browser::Platform::Linux
