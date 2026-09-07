#pragma once
#include "ui/TextField.hpp"
#include "ui/View.hpp"
#include <X11/Xlib.h>
#include <memory>
#include <string>

namespace Browser {

class BrowserUI {
public:
  BrowserUI();

  void Resize(int width, int height);
  void Render(Display *display, ::Window window);
  void MouseButtonDown(int x, int y);
  void KeyDown(char character, bool is_return, bool is_backspace);

  void SetAddress(const std::string &url);

private:
  Nova::UI::View Build();

private:
  int m_width = 0;
  int m_height = 0;
  Nova::UI::View m_root{nullptr};
  std::shared_ptr<Nova::UI::TextFieldNode> m_address_field;
};

} // namespace Browser
