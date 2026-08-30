#include "linux/Application.hpp"
#include "linux/Window.hpp"

#include <X11/X.h>
#include <X11/Xlib.h>
#include <stdexcept>

namespace Browser::Platform::Linux {
Application::Application() : m_display(XOpenDisplay(nullptr)) {
  if (m_display == nullptr) {
    throw std::runtime_error("Failed to open X11 display.");
  }
}

Application::~Application() {
  if (m_display != nullptr) {
    XCloseDisplay(m_display);
  }
}

int Application::Run() {
  Window window(m_display, "NovaBrowser", 1280, 800);

  window.Show();

  XEvent event{};

  while (true) {
    XNextEvent(m_display, &event);

    if (window.HandleEvent(event)) {
      break;
    }
  }

  return 0;
}

} // namespace Browser::Platform::Linux
