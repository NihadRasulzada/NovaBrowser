#include "linux/Application.hpp"

#include <X11/Xlib.h>
#include <stdexcept>

namespace Browser::Platform::Linux {
Application::Application() : m_display(XOpenDisplay(nullptr)) {
  if (m_display == nullptr) {
    throw std::runtime_error("Failed to open X11 display.");
  }
}
} // namespace Browser::Platform::Linux
