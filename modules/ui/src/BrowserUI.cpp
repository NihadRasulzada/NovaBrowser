#include "ui/BrowserUI.hpp"
#include "ui/BrowserView.hpp"
#include "ui/Button.hpp"
#include "ui/Column.hpp"
#include "ui/Row.hpp"
#include "ui/TabBar.hpp"

using namespace Nova::UI;

namespace Browser {

BrowserUI::BrowserUI() { m_root = Build(); }

View BrowserUI::Build() {
  auto address_field = std::make_shared<TextFieldNode>(
      "Search or enter address", TextFieldProps{
                                     .value = "",
                                     .onSubmit =
                                         [](const std::string &value) {
                                           // TODO: browser.Navigate(value);
                                         },
                                     .style = {.height = 32, .flex = 1},
                                 });
  m_address_field = address_field;

  return Column({
      TabBar(Style{.height = 36}),
      Row(
          {
              Button("<", ButtonProps{.style = {.width = 36, .height = 32}}),
              Button(">", ButtonProps{.style = {.width = 36, .height = 32}}),
              Button("R", ButtonProps{.style = {.width = 36, .height = 32}}),
              View(address_field),
          },
          Style{.height = 52, .spacing = 8}),
      BrowserView(Style{.flex = 1}),
  });
}

void BrowserUI::Resize(int width, int height) {
  m_width = width;
  m_height = height;
  m_root->Layout(Rect{0, 0, width, height});
}

void BrowserUI::Render(Display *display, ::Window window) {
  m_root->Render(display, window);
}

void BrowserUI::MouseButtonDown(int x, int y) { m_root->MouseButtonDown(x, y); }

void BrowserUI::KeyDown(char character, bool is_return, bool is_backspace) {
  if (m_address_field) {
    m_address_field->KeyDown(character, is_return, is_backspace);
  }
}

void BrowserUI::SetAddress(const std::string &url) {
  if (m_address_field)
    m_address_field->SetValue(url);
}

} // namespace Browser
