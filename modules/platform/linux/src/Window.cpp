#include "linux/Window.hpp"

#include <X11/Xatom.h>
#include <algorithm>

namespace Browser::Platform::Linux {

namespace {
constexpr long WindowEventMask =
    ExposureMask | StructureNotifyMask | KeyPressMask | KeyReleaseMask |
    ButtonPressMask | ButtonReleaseMask | PointerMotionMask;
}

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

  Atom wm_delete_window = XInternAtom(m_display, "WM_DELETE_WINDOW", False);

  XSetWMProtocols(m_display, m_handle, &wm_delete_window, 1);
}

void Window::RegisterEvents() {
  XSelectInput(m_display, m_handle, WindowEventMask);
}

void Window::Show() {
  XMapWindow(m_display, m_handle);

  XFlush(m_display);
}

::Window Window::Handle() const { return m_handle; }

void Window::SetEventHandler(EventHandler handler) {
  m_event_handler = std::move(handler);
}

void Window::SetPaintHandler(PaintHandler handler) {
  m_paint_handler = std::move(handler);
}

} // namespace Browser::Platform::Linux
