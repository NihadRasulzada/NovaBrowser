#pragma once

#include <X11/Xlib.h>

namespace Browser::Platform::Linux {
class Window {
public:
  Window(Display *display, const char *title, int width, int height);
  ~Window();

  void Show();
  ::Window Handle() const;
  bool ProcessEvent(const XEvent &event);

private:
  void Create();

  void RegisterEvents();

  Display *m_display;
  int m_screen;

  ::Window m_handle;

  const char *m_title;

  int m_width;
  int m_height;
};
} // namespace Browser::Platform::Linux
