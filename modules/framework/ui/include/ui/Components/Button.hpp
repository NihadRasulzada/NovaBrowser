#pragma once

#include "ui/Core/Node.hpp"
#include "ui/Core/View.hpp"

#include <functional>
#include <string>

namespace Nova::UI {

struct ButtonProps {
  std::function<void()> onClick;
  Style style;
};

class ButtonNode : public Node {
public:
  ButtonNode(std::string label, ButtonProps props)
      : Node(std::move(props.style)), m_label(std::move(label)),
        m_on_click(std::move(props.onClick)) {}

  void Layout(const Rect &bounds) override { m_bounds = ResolveBounds(bounds); }
  void Render(Display *display, ::Window window) const override;
  bool MouseButtonDown(int x, int y) override;

private:
  std::string m_label;
  std::function<void()> m_on_click;
};

inline View Button(std::string label, ButtonProps props = {}) {
  return View(std::make_shared<ButtonNode>(std::move(label), std::move(props)));
}

} // namespace Nova::UI
