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
        default:
          break;
        }
      },
      [&](Display *display, ::Window window, GC gc) {
        browser_ui.Render(display, window, gc);
      });
}
