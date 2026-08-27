#include "linux/Window.hpp"

#include <X11/X.h>
#include <X11/Xlib.h>

namespace Browser::Platform::Linux {

Window::Window(Display *display, const char *title, int width, int height)
    : m_display(display), m_screen(DefaultScreen(display)), m_handle(0),
      m_title(title), m_width(width), m_height(height) {
  Create();
  RegisterEvents();
}

Window::~Window() {
  if (m_handle != 0) {
    XDestroyWindow(m_display, m_handle);
  }
}

void Window::Create() {
  const ::Window root = RootWindow(m_display, m_screen);

  m_handle = XCreateSimpleWindow(
      m_display, root, 0, 0, static_cast<unsigned int>(m_width),
      static_cast<unsigned int>(m_height), 0, BlackPixel(m_display, m_screen),
      WhitePixel(m_display, m_screen));

  XStoreName(m_display, m_handle, m_title);
}

} // namespace Browser::Platform::Linux
