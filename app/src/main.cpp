#include "desktop/Application.hpp"
#include "ui/BrowserUI.hpp"

int main() {
  Browser::BrowserUI browser_ui;
  Browser::Platform::Application application;
  return application.Run(
      [&](const Browser::Platform::WindowEvent &event) {
        switch (event.type) {
        case Browser::Platform::WindowEventType::Resize:
          browser_ui.Resize(event.width, event.height);
          break;
        case Browser::Platform::WindowEventType::MouseButtonDown:
          browser_ui.MouseButtonDown(event.x, event.y);
          break;
        case Browser::Platform::WindowEventType::KeyDown:
          browser_ui.KeyDown(event.text, event.is_return, event.is_backspace);
          break;
        default:
          break;
        }
      },
      [&](Display *display, ::Window window) {
        browser_ui.Render(display, window);
      });
}
