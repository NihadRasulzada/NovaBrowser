#pragma once

#include "WindowEvents.hpp"
#include <X11/Xlib.h>
#include <functional>

namespace Browser::Platform::Linux {
class Window {
public:
  using EventHandler = std::function<void(const WindowEvent &)>;
  using PaintHandler = std::function<void(Display *, ::Window)>;

public:
  Window(Display *display, const char *title, int width, int height);
  ~Window();

  void Show();
  ::Window Handle() const;

  void SetEventHandler(EventHandler handler);
  void SetPaintHandler(PaintHandler handler);

  bool HandleEvent(const XEvent &event);

private:
  void Create();

  void RegisterEvents();

private:
  Display *m_display;
  int m_screen;

  ::Window m_handle;

  const char *m_title;

  int m_width;
  int m_height;

  EventHandler m_event_handler;
  PaintHandler m_paint_handler;
};
} // namespace Browser::Platform::Linux
