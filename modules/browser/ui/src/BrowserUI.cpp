#include "ui/BrowserUI.hpp"
#include "ui/Components/Button.hpp"
#include "ui/Layout/Row.hpp"

using namespace Nova::UI;

namespace Browser {

BrowserUI::BrowserUI() { m_root = Build(); }

View BrowserUI::Build() {
  return Row(
      {
          Button("<", ButtonProps{.style = {.width = 36, .height = 32}}),
          Button(">", ButtonProps{.style = {.width = 36, .height = 32}}),
          Button("R", ButtonProps{.style = {.width = 36, .height = 32}}),
      },
      Style{.height = 52, .spacing = 8});
}
void BrowserUI::Resize(int width, int height) {
  m_width = width;
  m_height = height;
  m_root->Layout(Rect{0, 0, width, height});
}

void BrowserUI::Render(Display *display, ::Window window) {
  m_root->Render(display, window);
}

} // namespace Browser
