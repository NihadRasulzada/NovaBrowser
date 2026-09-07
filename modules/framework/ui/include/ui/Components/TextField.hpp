#pragma once

#include "ui/Core/Node.hpp"
#include "ui/Core/View.hpp"

#include <functional>
#include <string>

namespace Nova::UI {

struct TextFieldProps {
  std::string value;
  std::function<void(const std::string &)> onSubmit;
  Style style;
};

class TextFieldNode : public Node {
public:
  TextFieldNode(std::string placeholder, TextFieldProps props)
      : Node(std::move(props.style)), m_placeholder(std::move(placeholder)),
        m_value(std::move(props.value)),
        m_on_submit(std::move(props.onSubmit)) {}

  void Layout(const Rect &bounds) override { m_bounds = bounds; }
  void Render(Display *display, ::Window window) const override;
  bool MouseButtonDown(int x, int y) override;

  void SetValue(std::string value) { m_value = std::move(value); }
  const std::string &GetValue() const { return m_value; }
  bool IsFocused() const { return m_focused; }
  void KeyDown(char character, bool is_return, bool is_backspace);

private:
  std::string m_placeholder;
  std::string m_value;
  std::function<void(const std::string &)> m_on_submit;
  bool m_focused = false;
};

inline View TextField(std::string placeholder, TextFieldProps props = {}) {
  return View(std::make_shared<TextFieldNode>(std::move(placeholder),
                                              std::move(props)));
}

} // namespace Nova::UI
