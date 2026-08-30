#pragma once

#include <X11/Xlib.h>

namespace Browser::Platform::Linux {
enum class WindowEventType {
  Close,
  Resize,
  MouseMove,
  MouseButtonDown,
  MouseButtonUp,
  KeyDown,
  KeyUp
};

struct WindowEvent {
  WindowEventType type;

  int x = 0;
  int y = 0;

  int width = 0;
  int height = 0;

  unsigned int button = 0;
  unsigned int key = 0;
};
} // namespace Browser::Platform::Linux
