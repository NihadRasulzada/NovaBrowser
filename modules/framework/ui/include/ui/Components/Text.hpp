#pragma once

#include "ui/Core/Node.hpp"
#include "ui/Core/View.hpp"

#include <string>
#include <utility>

namespace Nova::UI {

struct TextProps {
  Style style;
};

class TextNode : public Node {
public:
  TextNode(std::string text, TextProps props = {})
      : Node(std::move(props.style)), m_text(std::move(text)) {}

  void Layout(const Rect &bounds) override { m_bounds = bounds; }

  void Render(Display *display, ::Window window) const override;

private:
  std::string m_text;
};

inline View Text(std::string text, TextProps props = {}) {
  return View(std::make_shared<TextNode>(std::move(text), std::move(props)));
}

} // namespace Nova::UI
