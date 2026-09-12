#pragma once

#include "ui/Core/Node.hpp"
#include "ui/Core/View.hpp"

#include <functional>
#include <memory>

namespace Nova::UI {

struct ButtonProps {
  std::function<void()> onClick;
  Style style;
  View child{nullptr};
};

class ButtonNode : public Node {
public:
  explicit ButtonNode(ButtonProps props)
      : Node(std::move(props.style)), m_child(std::move(props.child)),
        m_on_click(std::move(props.onClick)) {}

  void Layout(const Rect &bounds) override;

  void Render(Display *display, ::Window window, GC gc) const override;

  bool MouseButtonDown(int x, int y) override;

private:
  View m_child;
  std::function<void()> m_on_click;
};

inline View Button(View child, ButtonProps props = {}) {
  props.child = std::move(child);

  return View(std::make_shared<ButtonNode>(std::move(props)));
}

} // namespace Nova::UI
