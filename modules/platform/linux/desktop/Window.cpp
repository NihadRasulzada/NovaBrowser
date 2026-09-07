#include "linux/Window.hpp"

#include <X11/X.h>
#include <X11/Xatom.h>

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
  // TODO: Bura oyrenilecek. WM nedir deye.
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

bool Window::HandleEvent(const XEvent &event) {
  if (event.type == Expose) {
    if (m_paint_handler) {
      m_paint_handler(m_display, m_handle);
    }
    return false;
  }
  if (!m_event_handler) {
    return false;
  }

  WindowEvent window_event{};

  switch (event.type) {
  // Qiraqdan gelen mesajlar. window manager misal.
  case ClientMessage: {
    Atom wm_delete_window = XInternAtom(m_display, "WM_DELETE_WINDOW", False);

    if (static_cast<Atom>(event.xclient.data.l[0]) == wm_delete_window) {
      WindowEvent window_event{};

      window_event.type = WindowEventType::Close;

      if (m_event_handler) {
        m_event_handler(window_event);
      }

      return true;
    }
    break;
  }
  // Olcu size deyisiklikleri. window un sizesinin deyismeyi.
  case ConfigureNotify: {
    window_event.type = WindowEventType::Resize;
    window_event.width = event.xconfigure.width;
    window_event.height = event.xconfigure.height;
    m_width = event.xconfigure.width;
    m_height = event.xconfigure.height;
    return false;
    break;
  }
  // Mouse hereket edende tetiklenir
  case MotionNotify: {
    window_event.type = WindowEventType::MouseMove;

    window_event.x = event.xmotion.x;

    window_event.y = event.xmotion.y;
    return false;
  }

  case ButtonPress: {
    window_event.type = WindowEventType::MouseButtonDown;

    window_event.x = event.xbutton.x;

    window_event.y = event.xbutton.y;

    window_event.button = event.xbutton.button;
    return false;
  }

  case ButtonRelease: {
    window_event.type = WindowEventType::MouseButtonUp;

    window_event.x = event.xbutton.x;

    window_event.y = event.xbutton.y;

    window_event.button = event.xbutton.button;
    return false;
  }

  case KeyPress: {
    window_event.type = WindowEventType::KeyDown;

    window_event.key = event.xkey.keycode;
    return false;
  }

  case KeyRelease: {
    window_event.type = WindowEventType::KeyUp;

    window_event.key = event.xkey.keycode;
    return false;
  }

  default:
    return false;
  }
  m_event_handler(window_event);
  return false;
}

} // namespace Browser::Platform::Linux
