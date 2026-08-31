#include <linux/Application.hpp>
#include <ui/BrowserUI.hpp>

int main() {
  Browser::UI::BrowserUI browser_ui;

  Browser::Platform::Linux::Application application;

  return application.Run(
      [&](const Browser::Platform::Linux::WindowEvent &event) {
        switch (event.type) {
        case Browser::Platform::Linux::WindowEventType::Resize:
          browser_ui.Resize(event.width, event.height);
          break;

        case Browser::Platform::Linux::WindowEventType::MouseMove:
          browser_ui.MouseMove(event.x, event.y);
          break;

        case Browser::Platform::Linux::WindowEventType::MouseButtonDown:
          browser_ui.MouseButtonDown(event.x, event.y);
          break;

        default:
          break;
        }
      },

      [&](Display *display, ::Window window) {
        browser_ui.Render(display, window);
      });
}
